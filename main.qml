import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
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

        Behavior on opacity {PropertyAnimation {}}
    }

    Image {
        id: odo_audi
        source: "content/odo_audi.png"
        anchors.centerIn: parent

        Behavior on opacity {PropertyAnimation {}}

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
            id: turnsRow
            spacing: 250
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height / 3.5

            TurnIndicator {
                id: leftIndicator
                objectName: "leftIndicator"
                width: height
                height: root.height * 0.09
                antialiasing: true
                direction: Qt.LeftArrow
                on: true
            }

            /*Image {
                source: "content/EngineWarningIcon.png"
            }

            Image {
                source: "content/FogLampIcon.png"
            }*/

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


    Row {
        id: dialsRow
        spacing: 350
        anchors.centerIn: parent
        Behavior on spacing {PropertyAnimation { duration: 400; easing.type: Easing.OutQuad}}


        Speedometer {
            id: speedometer
            objectName: "dial"

            Behavior on scale {PropertyAnimation {}}
        }

        Taho {
            id: tahometer

            Behavior on scale {PropertyAnimation {}}

        }

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

    Button
    {
        id: firstbutton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.margins: 50
        Text {
            text: "Hide dashboard"
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 20
        }
        onClicked:
        {
            speedometer.scale = 0.85;
            tahometer.scale = 0.85;
            dialsRow.spacing = 450;
            odo_audi.opacity = 0;
            background.opacity = 0;

            rightIndicator.on = false;
            leftIndicator.on = false;
        }
        style:  buttonStyle
    }

    Component {
        id: buttonStyle
        ButtonStyle {
            background: Rectangle {
                implicitHeight: 35
                implicitWidth: 224
                radius: 4
                color: control.pressed ? "#BDBDBD" : "#404040"
                Behavior on color {ColorAnimation {}}
            }
        }
    }


}
