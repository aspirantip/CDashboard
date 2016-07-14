import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import "content"

ApplicationWindow {
    id:root
    visible: true
    color: "#545454"
    title: "Dashboard"

    width: Screen.width; height: Math.min(Screen.width, Screen.height)

    property int k : 0;

    Rectangle {
        width: root.width;
        height: root.height;
        color: "black"
    }

    Image {
        id: background
        source: "content/back_audi.png"
        anchors.centerIn: parent
    }

    Image {
        source: "content/odo_audi.png"
        anchors.centerIn: parent

        Text
        {
            id: time
            anchors.left:  parent.left
            anchors.margins: 30
            y: parent.height / 10
            color: "#FAFAFA";
            font.pointSize: 16
            text: Qt.formatTime(new Date(),"hh:mm")
        }

        Text {
            id: date
            anchors.right:  parent.right
            anchors.margins: 30
            y: parent.height / 10
            color: "#FAFAFA";
            font.pointSize: 16
            text: Qt.formatDateTime(new Date(), "dd.MM.yy");
        }

        Text
        {
            id: fuelValue
            y: parent.height / 1.17
            x: parent.width / 7.4
            color: "#FAFAFA";
            font.pointSize: 14
            text: "6 L"
        }

        Text {
            id: accumValue
            y: parent.height / 1.18
            x: parent.width / 2.05
            color: "#FAFAFA";
            font.pointSize: 14
            text: "13.7 V";
        }

        Text
        {
            id: temperatureValue
            y: parent.height / 1.17
            x: parent.width / 1.18
            color: "#FAFAFA";
            font.pointSize: 14
            text: "88 C"
        }

        Row {
            spacing: 1
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height / 4

            TurnIndicator {
                id: leftIndicator
                objectName: "leftIndicator"
                width: height
                height: root.height * 0.09
                antialiasing: true

                direction: Qt.LeftArrow
                on: true
            }

            Image {
                source: "content/EngineWarningIcon.png"
                scale: 1
            }

            Image {
                source: "content/FogLampIcon.png"
                scale: 1
            }


            TurnIndicator {
                id: rightIndicator
                objectName: "rightIndicator"
                width: height
                height: root.height * 0.09
                antialiasing: true

                direction: Qt.RightArrow
                on: true
            }

        }

    }

    Speedometer {
        id: dial
        objectName: "dial"
        anchors.left: background.left
        anchors.verticalCenter: background.verticalCenter
    }

    Taho {
        id: tahometer
        anchors.right: background.right
        anchors.verticalCenter: background.verticalCenter
    }

    ExitBtn {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
    }

    Timer
    {
        interval: 1000; running: true; repeat: true
        onTriggered: {
            time.text = Qt.formatTime(new Date(),"hh:mm");
            date.text = Qt.formatDateTime(new Date(), "dd.MM.yy");
        }
    }



}
