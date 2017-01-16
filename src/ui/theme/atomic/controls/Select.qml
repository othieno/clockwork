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
import Material 0.3
import Material.ListItems 0.1 as ListItem


ListItem.Subtitled {
	signal changed(int index, string label, var value)

	id: control
	subText: listView.currentItem.label
	onClicked: menu.open(control, 16 * Units.dp, 0)

	property alias title: control.text
	property alias subtitle: control.subText
	property alias model: listView.model
	property alias delegate: listView.delegate
	property alias selectedIndex: listView.currentIndex

	property int maxWidth_: 0

	Label {
		id: hiddenLabel
		style: "subheading"
		visible: false
		color: darkBackground ? Theme.dark.textColor : Theme.light.textColor
		onContentWidthChanged: {
			maxWidth_ = Math.max(contentWidth + 33 * Units.dp, maxWidth_)
		}
	}
	Dropdown {
		anchor: Item.TopLeft

		id: menu
		width: Math.max(56 * 2 * Units.dp, Math.min(control.width - 32 * Units.dp, maxWidth_))
		height: Math.min(10 * 48 * Units.dp + 16 * Units.dp, model.length * 48 * Units.dp + 16 * Units.dp)

		Rectangle {
			anchors.fill: parent
			radius: 2 * Units.dp
		}
		ListView {
			anchors {
				left: parent.left
				right: parent.right
				top: parent.top
				topMargin: 8 * Units.dp
			}
			id: listView
			height: count > 0 ? contentHeight : 0
			interactive: false
			onModelChanged: {
				// Resize the dropdown menu's width to fit the longest label.
				var labels = model.labels
				var longestLabelLength = 0
				for (var i = 0; i < labels.length; ++i) {
					var label = labels[i]
					if (longestLabelLength < label.length) {
						longestLabelLength = label.length
						hiddenLabel.text = label
					}
				}
			}
			delegate: Option {
				label: model.label
				value: model.value
				onClicked: {
					if (listView.currentIndex !== index) {
						listView.currentIndex = index
						control.changed(index, label, value)
					}
					menu.close()
				}
			}
		}
	}
}
