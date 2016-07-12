import QtQuick 2.0

Item {
    id: root
    property real value : 0

    width: 480; height: 480

    Image {
        id: speedometer
        source: "speedometer.png"
        anchors.centerIn: parent
    }

    Image {
        id: needle
        source: "needle.png"
        x: (parent.width - needle.width)/2;
        y: parent.height/2 - needle.height;
        antialiasing: true

        transform:
            Rotation {
            id: needleRotation
            origin.x: needle.width/2;
            origin.y: needle.height;
            angle: Math.min( Math.max(-135, root.value*1.35 - 135), 135)

            Behavior on angle {
                NumberAnimation {
                    easing.type: Easing.Linear
                    duration: 50
                }
            }
        }
    }

    Image {
        id: overlay
        source: "Overlay.png"
        anchors.centerIn: root
    }

    Text {
        id: kmh
        text: "km/h"
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 1.78
        color: "#FAFAFA";
        font.pointSize: 13
    }

    Text {
        id: speedText
        objectName: "speedText"
        text: "0"
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 2.2
        color: "#FAFAFA";
        font.pointSize: 35
    }

}
