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

bool sendSocketCommand(const std::string& cmd, std::string* response = nullptr) {
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
    char buf[64];
    std::memset(buf, 0, sizeof(buf));
    ssize_t n = ::read(fd, buf, sizeof(buf) - 1);
    if (n > 0 && response) {
        *response = std::string(buf, n);
    }
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

bool setConfigDaemonSetting(bool enable) {
    const char* home = std::getenv("HOME");
    if (!home) return false;
    std::string h = home;
    std::string caelestiaDir = h + "/.config/caelestia";
    std::string cfgDir = caelestiaDir;
    std::string cfgPath = caelestiaDir + "/stowaway.json";

    struct stat st;
    if (::stat(caelestiaDir.c_str(), &st) != 0 || !S_ISDIR(st.st_mode)) {
        cfgDir = h + "/.config/stowaway";
        cfgPath = cfgDir + "/config.json";
    }

    std::string mkdirCmd = "mkdir -p \"" + cfgDir + "\"";
    ::system(mkdirCmd.c_str());

    std::string content;
    FILE* f = std::fopen(cfgPath.c_str(), "r");
    if (f) {
        char buf[512];
        while (size_t n = std::fread(buf, 1, sizeof(buf), f)) {
            content.append(buf, n);
        }
        std::fclose(f);
    }

    std::string targetKey = "\"daemon\"";
    size_t pos = content.find(targetKey);
    if (pos != std::string::npos) {
        size_t colon = content.find(':', pos);
        if (colon != std::string::npos) {
            size_t valStart = content.find_first_not_of(" \t\r\n", colon + 1);
            if (valStart != std::string::npos) {
                size_t valEnd = content.find_first_of(",}\r\n", valStart);
                if (valEnd != std::string::npos) {
                    content.replace(valStart, valEnd - valStart, enable ? "true" : "false");
                }
            }
        }
    } else {
        size_t lastBrace = content.rfind('}');
        if (lastBrace != std::string::npos) {
            std::string toInsert = ",\n  \"daemon\": " + std::string(enable ? "true" : "false") + "\n";
            size_t firstBrace = content.find('{');
            if (content.find_first_not_of(" \t\r\n", firstBrace + 1) >= lastBrace) {
                toInsert = "\n  \"daemon\": " + std::string(enable ? "true" : "false") + "\n";
            }
            content.insert(lastBrace, toInsert);
        } else {
            content = "{\n  \"daemon\": " + std::string(enable ? "true" : "false") + "\n}\n";
        }
    }

    FILE* out = std::fopen(cfgPath.c_str(), "w");
    if (!out) return false;
    std::fwrite(content.c_str(), 1, content.size(), out);
    std::fclose(out);
    return true;
}

} // namespace

int main(int argc, char* argv[]) {
    int initialTab = 0;
    std::string command = "tab:0";
    int customWidth = 0;
    int customHeight = 0;
    double customScale = 0.0;
    bool resetSize = false;
    bool daemonMode = false;
    bool foreground = false;
    bool quitDaemon = false;
    bool checkStatus = false;
    bool noDaemon = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--toggle" || arg == "-t") { initialTab = 0; command = "tab:0"; }
        else if (arg == "--emoji" || arg == "-e") { initialTab = 1; command = "tab:1"; }
        else if (arg == "--kaomoji" || arg == "-k") { initialTab = 2; command = "tab:2"; }
        else if (arg == "--symbols" || arg == "-s") { initialTab = 3; command = "tab:3"; }
        else if (arg == "--hide" || arg == "--close") { command = "hide"; }
        else if (arg == "--daemon" || arg == "-d") { daemonMode = true; }
        else if (arg == "--foreground" || arg == "-f") { foreground = true; }
        else if (arg == "--no-daemon") { noDaemon = true; }
        else if (arg == "--enable-daemon") {
            setConfigDaemonSetting(true);
            std::printf("Stowaway daemon enabled in configuration.\n");
            return 0;
        } else if (arg == "--disable-daemon") {
            setConfigDaemonSetting(false);
            std::string res;
            sendSocketCommand("quit", &res);
            std::printf("Stowaway daemon disabled in configuration and stopped.\n");
            return 0;
        } else if (arg == "--quit" || arg == "--kill") { quitDaemon = true; }
        else if (arg == "--status") { checkStatus = true; }
        else if (arg == "--reset-size") {
            resetSize = true;
            command = "reset-size";
        } else if ((arg == "--width" || arg == "-W") && i + 1 < argc) {
            customWidth = std::atoi(argv[++i]);
        } else if ((arg == "--height" || arg == "-H") && i + 1 < argc) {
            customHeight = std::atoi(argv[++i]);
        } else if ((arg == "--size" || arg == "-S") && i + 1 < argc) {
            std::string sizeStr = argv[++i];
            size_t xPos = sizeStr.find('x');
            if (xPos == std::string::npos) xPos = sizeStr.find('X');
            if (xPos != std::string::npos) {
                customWidth = std::atoi(sizeStr.substr(0, xPos).c_str());
                customHeight = std::atoi(sizeStr.substr(xPos + 1).c_str());
            }
        } else if (arg == "--scale" && i + 1 < argc) {
            customScale = std::atof(argv[++i]);
        } else if (arg == "--clear") {
            ::system("cliphist wipe");
            return 0;
        } else if (arg == "--version" || arg == "-v") {
            std::printf("stowaway %s\n", STOWAWAY_VERSION);
            return 0;
        } else if (arg == "--help" || arg == "-h") {
            std::printf("Usage: stowaway [options]\n\n"
                        "Modes & Triggers:\n"
                        "  -t, --toggle           Open clipboard history overlay (default)\n"
                        "  -e, --emoji            Open straight to Emoji picker\n"
                        "  -k, --kaomoji          Open straight to Kaomoji picker\n"
                        "  -s, --symbols          Open straight to Symbols picker\n"
                        "      --hide, --close    Hide open clipboard overlay\n"
                        "      --clear            Clear clipboard history (cliphist wipe)\n\n"
                        "Daemon (Instant Open):\n"
                        "  -d, --daemon           Start background daemon for instant opening (<10ms)\n"
                        "  -f, --foreground       Run daemon in foreground (for systemd service)\n"
                        "      --no-daemon        Run standalone one-shot overlay without daemon\n"
                        "      --enable-daemon    Enable daemon mode in configuration file\n"
                        "      --disable-daemon   Disable daemon mode in configuration and stop daemon\n"
                        "      --status           Check if background daemon is running\n"
                        "      --quit, --kill     Terminate running daemon\n\n"
                        "Appearance & Sizing:\n"
                        "  -W, --width <pixels>   Set popup width in pixels\n"
                        "  -H, --height <pixels>  Set popup height in pixels\n"
                        "  -S, --size <WxH>       Set popup size (e.g. 480x620)\n"
                        "      --scale <factor>   Set UI scaling factor (e.g. 1.25, 1.5)\n"
                        "      --reset-size       Reset popup size to default (390x500)\n\n"
                        "General:\n"
                        "  -v, --version          Show version\n"
                        "  -h, --help             Show this help\n");
            return 0;
        }
    }

    if (quitDaemon) {
        std::string res;
        if (sendSocketCommand("quit", &res)) {
            std::printf("Stowaway daemon stopped.\n");
            return 0;
        } else {
            std::fprintf(stderr, "stowaway: no running instance or daemon found.\n");
            return 1;
        }
    }

    if (checkStatus) {
        std::string res;
        if (sendSocketCommand("status", &res)) {
            std::printf("Stowaway daemon is running.\n");
            return 0;
        } else {
            std::printf("Stowaway daemon is not running.\n");
            return 1;
        }
    }

    if (noDaemon) {
        ::setenv("STOWAWAY_DAEMON", "0", 1);
        ::setenv("STOWAWAY_NO_DAEMON", "1", 1);
    } else if (daemonMode) {
        std::string res;
        if (sendSocketCommand("status", &res)) {
            std::printf("Stowaway daemon is already running.\n");
            return 0;
        }
        initialTab = -1;
        ::setenv("STOWAWAY_DAEMON", "1", 1);
    }

    if (!resetSize && (customWidth > 0 || customHeight > 0 || customScale > 0.1)) {
        command = "tab:" + std::to_string(initialTab) + ":" +
                  std::to_string(customWidth) + ":" +
                  std::to_string(customHeight) + ":" +
                  (customScale > 0.1 ? std::to_string(customScale) : "");
    }

    // If an instance/daemon is already open, just switch tabs / apply size and exit immediately
    if (!noDaemon && !daemonMode && sendSocketCommand(command)) {
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

    if (customWidth > 0) {
        ::setenv("STOWAWAY_WIDTH", std::to_string(customWidth).c_str(), 1);
    }
    if (customHeight > 0) {
        ::setenv("STOWAWAY_HEIGHT", std::to_string(customHeight).c_str(), 1);
    }
    if (customScale > 0.1) {
        ::setenv("STOWAWAY_SCALE", std::to_string(customScale).c_str(), 1);
    }

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

    // Run quickshell
    std::vector<char*> args;
    args.push_back(const_cast<char*>("quickshell"));
    if (daemonMode && !foreground) {
        args.push_back(const_cast<char*>("-d"));
    }
    args.push_back(const_cast<char*>("-p"));
    args.push_back(const_cast<char*>(shellPath.c_str()));
    args.push_back(nullptr);

    ::execvp("quickshell", args.data());

    std::fprintf(stderr, "stowaway: failed to execute quickshell\n");
    return 1;
}
