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
import Clockwork 0.1


Page {
	/**
	 *
	 */
	FramebufferView {
		anchors.fill: parent
		/**
		 *
		 */
		MouseArea {
			id: framebufferViewMouseArea
			anchors.fill: parent
			/**
			 * The mouse's position when the MouseArea is clicked for the first time.
			 */
			property var mouseOrigin: Qt.point(0, 0)
			/**
			 * The mouse's acceleration along the X axis.
			 */
			property var mouseAccelerationX: 0
			/**
			 * The mouse's acceleration along the Y axis.
			 */
			property var mouseAccelerationY: 0
			/**
			 *
			 */
			property var mouseSpeed: 0.05

			acceptedButtons: Qt.AllButtons
			onPressed: function(e) {
				if (e.button == Qt.MiddleButton) {
					// TODO Implement reset functionality here.
				} else {
					mouseOrigin.x = e.x;
					mouseOrigin.y = e.y;
					mouseAccelerationX = 0;
					mouseAccelerationY = 0;

					framebufferViewTimer.start();
				}
			}
			onReleased: {
				if (framebufferViewTimer.running) {
					framebufferViewTimer.stop();
				}
			}
			onPositionChanged: function(e) {
				var deadzone = 10;
				var step = 0.0025;
				var dx = e.x - mouseOrigin.x;
				if (Math.abs(dx) < deadzone) {
					mouseAccelerationX = 0;
				} else {
					mouseAccelerationX = Math.max(-1.0, Math.min(dx * step, 1.0));
				}
/*
				var dy = e.y - mouseOrigin.y;
				if (Math.abs(dy) < deadzone) {
					mouseAccelerationY = 0;
				} else {
					mouseAccelerationY = Math.max(-1.0, Math.min(dy * step, 1.0));
				}
*/
			}
		}
		Timer {
			id: framebufferViewTimer
			interval: 16
			repeat: true
			onTriggered: {
				var speed = framebufferViewMouseArea.mouseSpeed;
				var distance = {
					x: framebufferViewMouseArea.mouseAccelerationX * speed,
					y: framebufferViewMouseArea.mouseAccelerationY * speed
				};
				var position = scene.viewer.position;
				if (position) {
					position.x += distance.x;
					position.y += distance.y;
				}
				var center = scene.viewer.center;
				if (center) {
					center.x += distance.x;
					center.y += distance.y;
				}
			}
		}
		/**
		 *
		 */
		Component.onCompleted: function() {
			application.frameRendered.connect(this.update);
		}
		/**
		 *
		 */
		Component.onDestruction: function() {
			application.frameRendered.disconnect(this.update);
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
