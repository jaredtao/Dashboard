import QtQuick 2.6
import Dashboard 1.0
Item {
    visible: true
    width: 800
    height: 480
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
