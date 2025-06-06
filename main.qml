import QtQuick
import QtQuick.Layouts

Window {
    width: 1488
    height: 922
    visible: true
    title: qsTr("Hello World z")

    FontLoader
    {
        id: pMedium
        source: "qrc:/fonts/SpaceGames-K7zKD.otf "
    }

    Rectangle
    {
        id: gameArea
        anchors.fill: parent
        visible: true
        color: Gradient
        {
            GradientStop { position: 0.0; color: "#132330" }
            GradientStop { position: 1.0; color: "black" }
        }

        Rectangle
        {
            id: gameOverOverlay
            anchors.fill: parent
            visible: false
            color: "Black"
            opacity: 0.8
            z: 1001

            ColumnLayout
            {
                anchors.centerIn: parent
                spacing: 20
                Text {
                    id: gameOver
                    text: qsTr("  Game Over\n " + control.showScore())
                    font.family: pMedium.font.family
                    font.weight: pMedium.font.weight
                    font.styleName: webFont.font.styleName
                    font.pixelSize: 50
                    Layout.alignment: Qt.AlignHCenter
                    color: "White"
                    anchors.centerIn: parent
                    Connections
                    {
                        target: control
                        function onScoreChanged()
                        {
                            gameOver.text = qsTr("  Game Over\n  " +   control.showScore());
                        }
                    }

                }

                RowLayout
                {
                    spacing: 20
                    Rectangle
                    {
                        id: closeBtn
                        width: 250
                        height: 45
                        color: "grey"
                        radius: 20
                        Text {

                            text: qsTr("Close")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: webFont.font.styleName
                            font.pixelSize: 35
                            color: "white"
                            anchors.centerIn: parent
                        }

                        MouseArea
                        {
                            hoverEnabled: true
                            anchors.fill: parent;
                            onEntered:
                            {
                                closeBtn.color = "red"
                            }
                            onExited:
                            {
                                closeBtn.color = "grey"
                            }

                            onClicked:
                            {
                                Qt.quit();
                            }
                        }
                    }
                    Rectangle
                    {
                        id: restartBtn
                        width: 250
                        height: 45
                        color: "grey"
                        radius: 20
                        Text {

                            text: qsTr("Restart")
                            font.family: pMedium.font.family
                            font.weight: pMedium.font.weight
                            font.styleName: webFont.font.styleName
                            font.pixelSize: 35
                            color: "white"
                            anchors.centerIn: parent
                        }

                        MouseArea
                        {
                            hoverEnabled: true
                            anchors.fill: parent;
                            onEntered:
                            {
                                restartBtn.color = "green"
                            }

                            onExited:
                            {
                                restartBtn.color = "grey"
                            }

                            onClicked:
                            {
                                control.restartGame();
                                gameOverOverlay.visible = false;
                            }
                        }
                    }
                }
            }

        }

        Connections
        {
            target: control
            onGameOver:
            {
                gameOverOverlay.visible = true;
            }
        }

        Rectangle
        {
            id: move1
            width: 8
            height: 8
            color: "transparent"
            x: control.x
            y: control.y
            focus: true

            Image{
                id: rocket
                source: "qrc:/playr/player1.png"
                width: 95
                height: 95
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }

            AnimatedImage
            {
                id: thruster
                source: " qrc:/playr/png-transparent-flame-fire-drawing-flame-orange-fictional-character-combustion.png"
                width: 30
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rocket.bottom
                playing: true
            }

            Keys.onPressed:(event) =>
                           {
                                if(event.key === Qt.Key_Left )
                               {
                                    control.moveLeft()
                               }
                               if(event.key === Qt.Key_Right )
                              {
                                   control.moveRight()
                              }
                               if(event.key === Qt.Key_Up )
                              {
                                  control.applyThrust();
                              }
                             if(event.key ===Qt.Key_Space)
                               {
                                   control.fireBullet();
                               }
                               thruster.playing = true
                           }

            Keys.onReleased: (event) =>
                             {
                                 if(event.key === Qt.Key_Left || event.key === Qt.Key_Right)
                                 {
                                     control.stopMovement()
                                 }
                             }
        }

        Component.onCompleted:
        {
            move1.forceActiveFocus();
            thruster.playing = true;
        }

        Text
        {
            id: scoreBoard
            text: " SCORE : " + control.showScore()
            font.family: pMedium.font.family
            font.weight: pMedium.font.weight
            font.styleName: webFont.font.styleName
            font.pixelSize: 40
            color: "white"
            x: 50
            y: 50

            Connections
            {
                target: control
                function onScoreChanged()
                {
                    scoreBoard.text = " SCORE : " + control.showScore();
                }
            }
        }


        Repeater
        {
            model: control.bullets
            delegate: Bullet{}
        }

        Repeater
        {
            model: control.enemies
            delegate: Enemy{}

        }
    }

    }

