#include "positioncontroller.hpp"
#include "hyprlandipc.hpp"
#include <algorithm>

namespace stowaway::core {

PositionController::PositionController(QObject* parent)
    : QObject(parent) {
    calculatePosition(390, 490);
}

PositionController* PositionController::instance() {
    static PositionController inst;
    return &inst;
}

void PositionController::calculatePosition(int popupWidth, int popupHeight) {
    QPoint cursor = HyprlandIPC::getCursorPos();
    QList<HyprlandMonitor> monitors = HyprlandIPC::getMonitors();

    HyprlandMonitor activeMon;
    bool found = false;

    for (const auto& mon : monitors) {
        QRect r(mon.x, mon.y, mon.effectiveWidth(), mon.effectiveHeight());
        if (r.contains(cursor)) {
            activeMon = mon;
            found = true;
            break;
        }
    }

    if (!found && !monitors.isEmpty()) {
        for (const auto& mon : monitors) {
            if (mon.focused) {
                activeMon = mon;
                found = true;
                break;
            }
        }
        if (!found) {
            activeMon = monitors.first();
        }
    }

    m_monitorX = activeMon.x;
    m_monitorY = activeMon.y;
    m_monitorWidth = activeMon.effectiveWidth();
    m_monitorHeight = activeMon.effectiveHeight();
    m_monitorName = activeMon.name;

    const int margin = 16;
    const int cursorOffset = 12;

    int x = cursor.x() + cursorOffset;
    int y = cursor.y() + cursorOffset;

    // Check right screen collision -> flip to left of cursor
    if (x + popupWidth > activeMon.x + activeMon.effectiveWidth() - margin) {
        x = cursor.x() - popupWidth - cursorOffset;
    }

    // Clamp horizontal bounds within monitor
    int minX = activeMon.x + margin;
    int maxX = std::max(minX, activeMon.x + activeMon.effectiveWidth() - popupWidth - margin);
    x = std::clamp(x, minX, maxX);

    // Check bottom screen collision -> flip to above cursor
    if (y + popupHeight > activeMon.y + activeMon.effectiveHeight() - margin) {
        y = cursor.y() - popupHeight - cursorOffset;
    }

    // Clamp vertical bounds within monitor
    int minY = activeMon.y + margin;
    int maxY = std::max(minY, activeMon.y + activeMon.effectiveHeight() - popupHeight - margin);
    y = std::clamp(y, minY, maxY);

    m_targetX = x;
    m_targetY = y;

    HyprlandIPC::positionWindow(m_targetX, m_targetY, popupWidth, popupHeight);

    emit positionChanged();
}

} // namespace stowaway::core
