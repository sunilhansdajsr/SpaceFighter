import QtQuick

Rectangle {

        property var ePng: [
                "qrc:/enemy/GEnemy 1.png",
                "qrc:/enemy/GEnemy 2.png",
                "qrc:/enemy/GEnemy 3.png",
               "qrc:/enemy/GEnemy 4.png"
                ]

        property int eIndex: 0

        id: enemy1
        width: 50
        height: 50
        x: model.x
        y: model.y
        color: "transparent"

        Image {
                id:enemies
                anchors.fill: parent
               source: ePng[model.mIndex]
        }
}
