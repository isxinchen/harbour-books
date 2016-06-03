import QtQuick 2.0

Item {
    id: root

    property bool running: false
    property bool isSun: false

    readonly property int maxLineHeight: 100
    readonly property int minLineHeight: -32

    signal changeState(bool state)

    Rectangle {
        id: line
        anchors.horizontalCenter: parent.horizontalCenter
        height: -32
        width: 3
        opacity: 0.5
        color: "#BBBBBB"
    }
    MouseArea {
        anchors.top: line.bottom
        anchors.horizontalCenter: line.horizontalCenter
        width: 65
        height: 65

        property int lastY: 0

        Image {
            anchors.centerIn: parent
            source: isSun ? "images/sun.png" : "images/moon.png"
        }

        onPressed: {
            console.log("onPressed y=" + mouseY)
            lastY = mouseY
        }

        onMouseYChanged: {
            console.log("y changed =" + mouseY)
            if(mouseY <= maxLineHeight && mouseY >= 0){
//                line.height += mouseY
            }
        }

        onReleased: {
            console.log("onReleased y=" + mouseY)
//            if(line.height == maxLineHeight){
//                animateHide.start()
//            }
            if(mouseY - lastY > 0){
                animateShow.start()
            }
        }
    }

    NumberAnimation {
             id: animateHide
             target: line
             properties: "height"
             from: 100
             to: -32
             duration: 300
//             loops: Animation.Infinite
//             easing {type: Easing.OutBack; overshoot: 500}
             onStopped: {
                 running = false
//                 isSun = !isSun
                 changeState(!isSun)
             }
    }

    NumberAnimation {
             id: animateShow
             target: line
             properties: "height"
             from: -32
             to: 100
             duration: 300
//             loops: Animation.Infinite
//             easing {type: Easing.OutBack; overshoot: 500}
             onStopped: {
                 running = false
                 animateHide.start()
             }
    }
}
