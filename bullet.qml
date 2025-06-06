import QtQuick

Rectangle {
        id: bullet1
        width: 8
        height: 25
        color: "black"
        x: model.x
        y: model.y


        Image {
                id:bullets
                anchors.fill: parent
               source: "qrc:/bullet/pngtree-electric-red-thunderbolt-with-fire-effects-png-image_15357957.png"

        }

}
