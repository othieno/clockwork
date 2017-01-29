/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
import QtQuick.Window 2.2
import Material 0.2


ApplicationWindow {
	id: applicationWindow
	visible: true
	visibility: Window.Maximized
	title: "%1%2".arg(pageStack.currentItem !== null ? pageStack.currentItem.title + " - " : "").arg(application.applicationName)
	theme {
		accentColor: Palette.colors["blueGrey"]["700"]
		primaryColor: Palette.colors["blue"]["700"]
	}
	/**
	 *
	 */
	Component.onCompleted: {
		if (settings.showBorderlessWindow) {
			flags |= Qt.FramelessWindowHint
			applicationWindow.clientSideDecorations = true
		}
		// TODO Remove this when there's a more user-friendly way of loading a scene.
		scene.load("/dummy/path/to/scene");
	}
	/**
	 *
	 */
	Component.onDestruction: {
	}
	/**
	 * The application's main page.
	 */
	initialPage: Page {
		title: qsTr("Renderer")
		actionBar {
			title: initialPage.title
			elevation: foreground.state == "maximized" ? 0 : 1
			actions: [
				Action {
					name: qsTr("Documentation")
					iconSource: "qrc:/icon/action/book"
					text: qsTr("Read the documentation")
					onTriggered: pageStack.push("qrc:/view/Documentation.qml")
					hasDividerAfter: true
				},
				Action {
					name: qsTr("Scissor rectangle")
					iconSource: "qrc:/icon/content/content_cut"
					text: qsTr("Configure the scissor rectangle")
					visible: graphics.enableScissorTest
					enabled: foreground.state == "maximized"
				},
				Action {
					name: qsTr("Stencil buffer")
					iconSource: "qrc:/icon/image/compare"
					text: qsTr("Configure the stencil buffer")
					visible: graphics.enableStencilTest
					enabled: foreground.state == "maximized"
				},
				Action {
					name: qsTr("Rendering context")
					iconSource: "qrc:/icon/av/tune"
					text: qsTr("Configure the rendering context")
					onTriggered: foreground.state = foreground.state == "maximized" ? "minimized" : "maximized"
					hasDividerAfter: true
				},
				Action {
					name: qsTr("Settings")
					iconSource: "qrc:/icon/action/settings"
					text: qsTr("Configure the application")
					onTriggered: pageStack.push("qrc:/view/Settings.qml")
					hoverAnimation: true
				}
			]
		}
		View {
			anchors {
				fill: parent
			}
			id: background
			visible: foreground.state == "minimized"
			RenderingContext {
				id: renderingContextView
			}
		}
		View {
			id: foreground
			state: "maximized"
			states: [
				State {
					name: "minimized"
					AnchorChanges {
						target: foreground
						anchors {
							top: parent.top
							right: parent.right
						}
					}
					PropertyChanges {
						target: foreground
						anchors.margins: dp(8)
						width: dp(Screen.width / 4)
						height: dp(Screen.height / 4)
						elevation: 1
					}
					PropertyChanges {
						target: rendererView
						anchors.margins: dp(1)
					}
				},
				State {
					name: "maximized"
					PropertyChanges {
						target: foreground
						anchors.fill: foreground.parent
					}
				}
			]
			Renderer {
				id: rendererView
			}
			MouseArea {
				anchors.fill: parent
				enabled: foreground.state == "minimized"
				hoverEnabled: true
				onDoubleClicked: foreground.state = "maximized"
				onWheel: {}
			}
		}
	}
}
