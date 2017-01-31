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
import Material 0.2

Item {
	id: viewport
	anchors.fill: parent
	visible: scissorToggle.checked
	/**
	 *
	 */
	property var scissorBox: graphics.normalizedScissorBox
	/**
	 *
	 */
	property double sx: scissorBox.x
	/**
	 *
	 */
	property double sy: scissorBox.y
	/**
	 *
	 */
	property double sr: scissorBox.right
	/**
	 *
	 */
	property double sb: scissorBox.bottom
	/**
	 *
	 */
	readonly property int handleSize: 32
	/**
	 *
	 */
	readonly property color handleColor: Theme.accentColor
	/**
	 *
	 */
	Component.onCompleted: {
		// When the scissor toggle is unchecked and the scissor box is
		// therefore hidden, the scene can then be rendered. Note that the
		// scene is only rendered if the scissor box has actually changed.
		scissorToggle.onToggled.connect(function(checked){
			if (!checked) {
				graphics.normalizedScissorBox = Qt.rect(sx, sy, sr - sx, sb - sy)
			}
		})
	}
	/**
	 * The main scissor box.
	 */
	Rectangle {
		anchors {
			top: topLeftHandle.top
			left: topLeftHandle.left
			right: bottomRightHandle.right
			bottom: bottomRightHandle.bottom
		}
		color: "#3300AAFF"
		opacity: 0.5
		border {
			color: handleColor
			width: 2
		}
	}
	/**
	 * The top-left handle.
	 */
	Rectangle {
		id: topLeftHandle
		x: sx * parent.width
		y: sy * parent.height
		width: handleSize
		height: handleSize
		color: handleColor
		MouseArea {
			anchors.fill: parent
			cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor
			onReleased: {
				sx = parent.x / viewport.width
				sy = parent.y / viewport.height
			}
			drag {
				target: parent
				minimumX: viewport.x
				minimumY: viewport.y
				maximumX: bottomRightHandle.x
				maximumY: bottomRightHandle.y
			}
		}
	}
	/**
	 * The bottom-right handle.
	 */
	Rectangle {
		id: bottomRightHandle
		x: (sr * parent.width) - handleSize
		y: (sb * parent.height) - handleSize
		width: handleSize
		height: handleSize
		color: handleColor
		MouseArea {
			anchors.fill: parent
			cursorShape: pressed ? Qt.ClosedHandCursor : Qt.OpenHandCursor
			onReleased: {
				sr = (parent.x + handleSize) / viewport.width
				sb = (parent.y + handleSize) / viewport.height
			}
			drag {
				target: parent
				minimumX: topLeftHandle.x
				minimumY: topLeftHandle.y
				maximumX: viewport.width - handleSize
				maximumY: viewport.height - handleSize
			}
		}
	}
}
