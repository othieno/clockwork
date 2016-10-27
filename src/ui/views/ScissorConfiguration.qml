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
import Material 0.2


Page {
	id: scissorConfigurationView
	/**
	 * The current scene viewer's scissor.
	 */
	property var scissor: scene.viewer.scissor
	/**
	 *
	 */
	readonly property var edgeSize: 30
	/**
	 * Updates the scissor's bounding box when the page is destroyed.
	 */
	Component.onDestruction: {
		if (scene !== null) {
			var sx = topLeftEdge.x / width
			var sy = topLeftEdge.y / height
			var sw = (bottomRightEdge.x + edgeSize) / width
			var sh = (bottomRightEdge.y + edgeSize) / height

			scissor.x = sx
			scissor.y = sy
			scissor.width = sw
			scissor.height = sh
		}
	}
	Image {
		cache: false
		smooth: false
		width: parent.width
		height: parent.height
		source: "image://framebuffer/0pixel"
	}
	Rectangle {
		anchors {
			top: topLeftEdge.top
			left: topLeftEdge.left
			right: bottomRightEdge.right
			bottom: bottomRightEdge.bottom
		}
		color: "#3300AAFF"
		border {
			color: Theme.primaryColor
			width: 2
		}
	}
	Rectangle {
		id: topLeftEdge
		x: scissor.x * parent.width
		y: scissor.y * parent.height
		width: edgeSize
		height: edgeSize
		color: Theme.primaryColor
		MouseArea {
			anchors.fill: parent
			cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor;
			drag {
				target: parent
				minimumX: parent.parent.x
				minimumY: parent.parent.y
				maximumX: bottomRightEdge.x
				maximumY: bottomRightEdge.y
			}
		}
	}
	Rectangle {
		id: bottomRightEdge
		x: ((scissor.right - scissor.x) * parent.width) - edgeSize
		y: ((scissor.bottom - scissor.y) * parent.height) - edgeSize
		width: edgeSize
		height: edgeSize
		color: Theme.primaryColor
		MouseArea {
			anchors.fill: parent
			cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor;
			drag {
				target: parent
				minimumX: topLeftEdge.x
				minimumY: topLeftEdge.y
				maximumX: parent.parent.width - parent.width
				maximumY: parent.parent.height - parent.height
			}
		}
	}
}
