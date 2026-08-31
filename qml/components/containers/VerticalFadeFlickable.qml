import Astra.Stowaway
import QtQuick
import QtQuick.Effects
import "../"
import "../effects"

Flickable {
    id: root

    property real fadeAmount: 0.08

    property real topFadeOpacity: fadeShouldBeActive(true) ? 0 : 1
    property real bottomFadeOpacity: fadeShouldBeActive(false) ? 0 : 1
    flickDeceleration: 5000
    maximumFlickVelocity: 5000
    boundsBehavior: Flickable.DragAndOvershootBounds

    function fadeShouldBeActive(isStart) {
        if (contentHeight + topMargin + bottomMargin < height)
            return false;

        if (isStart)
            return visibleArea.yPosition > 0.005;
        return visibleArea.yPosition + visibleArea.heightRatio < 0.995;
    }

    layer.enabled: true
    layer.effect: Mask {
        maskSource: mask

        Rectangle {
            id: mask
            anchors.fill: parent
            visible: false
            layer.enabled: true

            gradient: Gradient {
                orientation: Gradient.Vertical

                GradientStop {
                    position: 0
                    color: Qt.rgba(0, 0, 0, root.topFadeOpacity)
                }
                GradientStop {
                    position: root.fadeAmount
                    color: Qt.rgba(0, 0, 0, 1)
                }
                GradientStop {
                    position: 1 - root.fadeAmount
                    color: Qt.rgba(0, 0, 0, 1)
                }
                GradientStop {
                    position: 1
                    color: Qt.rgba(0, 0, 0, root.bottomFadeOpacity)
                }
            }
        }
    }

    Behavior on topFadeOpacity {
        Anim { type: Anim.FastEffects }
    }

    Behavior on bottomFadeOpacity {
        Anim { type: Anim.FastEffects }
    }
}
