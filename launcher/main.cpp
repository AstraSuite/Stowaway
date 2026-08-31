#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <limits.h>

#ifndef STOWAWAY_VERSION
#define STOWAWAY_VERSION "1.0.0"
#endif

namespace {

std::string getSocketPath() {
    const char* runtimeDir = std::getenv("XDG_RUNTIME_DIR");
    std::string dir = runtimeDir ? runtimeDir : "/tmp";
    return dir + "/stowaway.sock";
}

bool sendSocketCommand(const std::string& cmd) {
    std::string sockPath = getSocketPath();
    int fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) return false;

    struct sockaddr_un addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    std::strncpy(addr.sun_path, sockPath.c_str(), sizeof(addr.sun_path) - 1);

    if (::connect(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd);
        return false;
    }

    ::write(fd, cmd.c_str(), cmd.size());
    char buf[32];
    ::read(fd, buf, sizeof(buf) - 1);
    ::close(fd);
    return true;
}

bool isFile(const std::string& path) {
    struct stat st;
    return ::stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

std::string dirName(const std::string& path) {
    size_t pos = path.rfind('/');
    if (pos == std::string::npos) return ".";
    if (pos == 0) return "/";
    return path.substr(0, pos);
}

std::string findShellQml() {
    char exePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    std::vector<std::string> candidates;

    if (len > 0) {
        exePath[len] = '\0';
        std::string exeDir = dirName(exePath);
        candidates.push_back(exeDir + "/../shell.qml");
        candidates.push_back(exeDir + "/shell.qml");
        candidates.push_back(exeDir + "/../../shell.qml");
    }
    candidates.push_back("./shell.qml");
    candidates.push_back("/etc/xdg/quickshell/astra-stowaway/shell.qml");
    candidates.push_back("/usr/share/stowaway/shell.qml");

    for (const auto& path : candidates) {
        char resolved[PATH_MAX];
        if (::realpath(path.c_str(), resolved) != nullptr) {
            if (isFile(resolved)) return resolved;
        }
    }
    return "";
}

std::string findQmlImportDir() {
    char exePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len > 0) {
        exePath[len] = '\0';
        std::string exeDir = dirName(exePath);
        std::string buildQml = exeDir + "/qml";
        if (access(buildQml.c_str(), F_OK) == 0) return buildQml;
        buildQml = exeDir + "/../qml";
        if (access(buildQml.c_str(), F_OK) == 0) return buildQml;
    }
    return "/usr/lib/qt6/qml";
}

std::string findPluginLibDir() {
    char exePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len > 0) {
        exePath[len] = '\0';
        std::string exeDir = dirName(exePath);
        std::string buildLib = exeDir + "/../plugin";
        if (access(buildLib.c_str(), F_OK) == 0) return buildLib;
        buildLib = exeDir + "/plugin";
        if (access(buildLib.c_str(), F_OK) == 0) return buildLib;
    }
    return "/usr/lib/qt6/qml/Astra/Stowaway";
}

} // namespace

int main(int argc, char* argv[]) {
    int initialTab = 0;
    std::string command = "tab:0";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--toggle" || arg == "-t") { initialTab = 0; command = "tab:0"; }
        else if (arg == "--emoji" || arg == "-e") { initialTab = 1; command = "tab:1"; }
        else if (arg == "--kaomoji" || arg == "-k") { initialTab = 2; command = "tab:2"; }
        else if (arg == "--symbols" || arg == "-s") { initialTab = 3; command = "tab:3"; }
        else if (arg == "--hide" || arg == "--close") { command = "hide"; }
        else if (arg == "--clear") {
            ::system("cliphist wipe");
            return 0;
        } else if (arg == "--version" || arg == "-v") {
            std::printf("stowaway %s\n", STOWAWAY_VERSION);
            return 0;
        } else if (arg == "--help" || arg == "-h") {
            std::printf("Usage: stowaway [options]\n\n"
                        "Options:\n"
                        "  -t, --toggle     Open clipboard history overlay (default)\n"
                        "  -e, --emoji      Open straight to Emoji picker\n"
                        "  -k, --kaomoji    Open straight to Kaomoji picker\n"
                        "  -s, --symbols    Open straight to Symbols picker\n"
                        "  --clear          Clear clipboard history (cliphist wipe)\n"
                        "  -v, --version    Show version\n"
                        "  -h, --help       Show this help\n");
            return 0;
        }
    }

    // If an instance is already open, just switch tabs and exit immediately
    if (sendSocketCommand(command)) {
        return 0;
    }

    std::string shellPath = findShellQml();
    if (shellPath.empty()) {
        std::fprintf(stderr, "stowaway: error: cannot find shell.qml\n");
        return 1;
    }

    std::string importDir = findQmlImportDir();
    std::string libDir = findPluginLibDir();

    // Set initial tab env var
    ::setenv("STOWAWAY_INITIAL_TAB", std::to_string(initialTab).c_str(), 1);

    // Set QML and library paths for quickshell
    const char* existingQml = std::getenv("QML2_IMPORT_PATH");
    std::string newQml = importDir + (existingQml ? std::string(":") + existingQml : "");
    ::setenv("QML2_IMPORT_PATH", newQml.c_str(), 1);
    ::setenv("QML_IMPORT_PATH", newQml.c_str(), 1);

    const char* existingLd = std::getenv("LD_LIBRARY_PATH");
    std::string newLd = libDir + (existingLd ? std::string(":") + existingLd : "");
    ::setenv("LD_LIBRARY_PATH", newLd.c_str(), 1);

    // Disable Hyprland layer animations so custom QML spring animations run exclusively
    ::system("hyprctl keyword layerrule \"noanim, namespace:stowaway\" >/dev/null 2>&1 || true");

    // Run quickshell directly
    char* args[] = {
        const_cast<char*>("quickshell"),
        const_cast<char*>("-p"),
        const_cast<char*>(shellPath.c_str()),
        nullptr
    };
    ::execvp("quickshell", args);

    std::fprintf(stderr, "stowaway: failed to execute quickshell\n");
    return 1;
}
