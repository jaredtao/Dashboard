import QtQuick 2.6
import Boards 1.0
Item {
    id: root
    visible: true
    width: 1200
    height: 800
    property int value: 0
    Behavior on value { SpringAnimation { spring: 5.0; damping: 0.5; epsilon: 0.8 } }
    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        NumberAnimation { target: root; property: "value"; duration: 3000; to: 300}
        PauseAnimation { duration: 200 }
        NumberAnimation { target: root; property: "value"; duration: 3000; to: 0}
        PauseAnimation { duration: 200 }
    }

    Dashboard {
        x: 0
        y: 0
        width: 400
        height: 400
        startAngle: 240
        spanAngle: -300
        divisor: 10
        precision: 5
        minValue: 0
        maxValue: 300
        value: root.value
    }
//    Rectangle {
//        x: 401
//        y: 0
//        width: 400
//        height: 400
//        color: "black"
//    }
    Ringboard {
        x: 401
        y: 0
        width: 400
        height: 400
        startAngle: 240
        spanAngle: -root.value
        radiusInner: 130
        radiusOuter: 180
        roundConer: true
    }
    Item {
        id: fpsItem
        property int fps: 0
        property int frameCount: 0
        NumberAnimation on rotation {
            from: 0
            to: 100
            loops: Animation.Infinite
            duration: 300
        }
        onRotationChanged: frameCount++
    }
    Text {
        x: 10
        y: 10
        text: "FPS: " + fpsItem.fps
        color: "green"
        font.pixelSize: 18
    }
    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            fpsItem.fps = fpsItem.frameCount;
            fpsItem.frameCount = 0;
            console.log("FPS:", fpsItem.fps)
        }
    }
}
