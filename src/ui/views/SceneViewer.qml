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


Rectangle {
	id: sceneViewer
	color: Theme.backgroundColor
	Rectangle {
		/**
		 * The welcome panel.
		 */
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: footer.top
		color: Theme.backgroundColor
		visible: !framebuffer.visible
	}
	Rectangle {
		anchors.fill: parent
		color: Palette.colors["grey"]["900"]
		//visible: framebuffer.visible
		Image {
			/**
			 * The framebuffer's currently selected attachment.
			 */
			property var attachment: "pixel"

			id: framebuffer
			cache: false
			visible: true
			width: parent.width
			height: parent.height
			//fillMode: Image.PreserveAspectFit
			source: "image://framebuffer/%1".arg(attachment)
			Row {
				/**
				 * Framebuffer attachment toggles.
				 */
				anchors {
					top: parent.top
					right: parent.right
					topMargin: dp(8)
					rightMargin: dp(8)
				}
				spacing: dp(8)
				Repeater {
					model: [
						"pixel",
						"depth",
						"stencil",
					]
					delegate: IconButton {
						readonly property bool selected: framebuffer.attachment === modelData
						iconSource: "qrc:/icon/action/framebuffer/%1".arg(modelData)
						size: dp(32)
						color: selected ? Theme.accentColor : Theme.backgroundColor
						opacity: selected ? 1 : 0.1
						action: Action {
							iconName: "framebuffer-attachment-%1".arg(modelData)
							onTriggered: framebuffer.attachment = modelData
						}
					}
				}
			}
		}
	}
	/**
	 * The scene viewer's triptych footer.
	 */
	GridLayout {
		id: footer
		columns: 3
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: dp(10)
		RowLayout {
			anchors.left: parent.left
			RowLayout {
				/**
				 * Scene Graph view toggle.
				 */
				visible: false
				spacing: dp(8)
				Label {
					text: "Show Scene Graph"
					color: Theme.dark.textColor
				}
				Switch {
					id: toggleSceneGraphView
					checked: true
					darkBackground: true
				}
			}
		}
		RowLayout {
			anchors.centerIn: parent
			Repeater {
				model: [
					"X"
				]
				delegate: IconButton {
					IconButton {
						iconSource: "qrc:/icon/action/%1".arg(modelData)
						color: Theme.dark.iconColor
						action: Action {
							onTriggered: {
							}
						}
					}
				}
			}
		}
		RowLayout {
			anchors.right: parent.right
			RowLayout {
				/**
				 * Progress bar.
				 */
				spacing: dp(10)
				ProgressCircle {
					id: progressIndicator
					indeterminate: true
					visible: false
				}
			}
		}
	}
}
