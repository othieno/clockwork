/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import Material 0.2


ApplicationWindow {
    id: application
    title: "Clockwork"
    visible: true
    visibility: "Maximized"
    initialPage: Page {
        id: sceneView
        title: "Scene"

        Image {
            anchors.centerIn: parent
            width: dp(800)
            height: dp(600)
            cache: false
            source: "qrc:/framebuffer"
/*
            source: "image://framebuffer/pixel"
            source: "image://framebuffer/depth"
            source: "image://framebuffer/stencil"
            source: "image://framebuffer/accumulation"
*/
        }
    }
    statusBar: StatusBar {
        anchors.fill: parent
        style: StatusBarStyle {
            padding {
                top: 10
                left: 10
                right: 10
                bottom: 10
            }
            background: Rectangle {
                color: Theme.backgroundColor
            }
        }
        RowLayout {
            anchors.fill: parent
            RowLayout {
                spacing: 8
                //visible: sceneView.visible // Maybe use pageStack.depth
                visible: false
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                Label {
                    text: "Show Scene Graph"
                    color: Theme.dark.textColor
                }
                Switch {
                    id: toggleSceneGraphView
                    checked: true
                    darkBackground: true
                    enabled: sceneView.visible
                }
            }
            RowLayout {
                spacing: 25
                anchors.centerIn: parent
                Repeater {
                    model: [
                        "Preferences"
                    ]
                    IconButton {
                        iconSource: "qrc:/icon/action/%1".arg(modelData)
                        color: Theme.dark.iconColor
                        action: Action {
                            onTriggered: pageStack.depth == 1 ? pageStack.push("qrc:/view/%1".arg(modelData)) : pageStack.pop()
                        }
                        hoverAnimation: true
                        enabled: pageStack.depth == 1 || pageStack.currentItem.title == modelData
                    }
                }
            }
            RowLayout {
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                spacing: 10
                ProgressBar {
                    id: progressBar
                    visible: false
                    width: dp(128)
                    height: dp(4)
                    color: Palette.colors["red"]["400"]
                    indeterminate: true
                }
            }
        }
    }
    theme {
        primaryColor: "blue"
        primaryDarkColor: "#FFF"
        backgroundColor: "#333"
        accentColor: "red"
        tabHighlightColor: "white"
    }
}
