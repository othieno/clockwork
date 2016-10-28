/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
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


Page {
	id: sceneRenderView
	Image {
		id: framebuffer
		/**
		 * A value used to force image requests from the image provider.
		 */
		property var frame: 0
		/**
		 * Disables image caching as the framebuffer changes frequently.
		 */
		cache: false
		/**
		 * Disables the smoothing filter as this alters the renderer's actual output.
		 */
		smooth: false
		/**
		 * Fills the viewport horizontally.
		 */
		width: parent.width
		/**
		 * Fills the viewport vertically.
		 */
		height: parent.height
		/**
		 * The image's source.
		 */
		source: "image://framebuffer/%1pixel".arg(frame)
		/**
		 * A handler that is called when an update is completed to refresh the
		 * framebuffer image.
		 */
		function onUpdateCompleted() {
			// As there's no proper way of explicitly updating the image, the
			// workaround is to update the frame number, which updates the image's
			// source attribute, which forces a request for a "new" image from
			// the image provider.
			framebuffer.frame = (framebuffer.frame + 1) % 10
		}
		/**
		 *
		 */
		Component.onCompleted: {
			application.updateCompleted.connect(onUpdateCompleted)
			application.update()
		}
		/**
		 *
		 */
		Component.onDestruction: {
			application.updateCompleted.disconnect(onUpdateCompleted)
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
