import QtQuick 2.6
import Dashboard 1.0
Item {
    id: root
    visible: true
    width: 800
    height: 480
    property int value: 0
    Behavior on value { SpringAnimation { spring: 5.0; damping: 0.5; epsilon: 0.8 } }
    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        NumberAnimation { target: root; property: "value"; duration: 3000; to: 220}
        PauseAnimation { duration: 200 }
        NumberAnimation { target: root; property: "value"; duration: 3000; to: 0}
        PauseAnimation { duration: 200 }
    }

    Dashboard {
        width: 400
        height: 400
        anchors.centerIn: parent
        startAngle: 240
        spanAngle: -300
        divisor: 11
        precision: 5
        minValue: 0
        maxValue: 220
        value: root.value
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
