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
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1


Page {
	id: themeSettingsView
	title: qsTr("Theme Settings")
	Flickable {
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: parent.height
		boundsBehavior: Flickable.StopAtBounds
		Column {
			anchors.fill: parent
			ListItem.Subheader {
				text: qsTr("Accessibility")
			}
			ListItem.Subtitled {
				enabled: false
				text: qsTr("Show larger text")
				subText: qsTr("Increases the base font size.")
				secondaryItem: Switch {
					id: toggleLargerText
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: toggleLargerText.checked = !toggleLargerText.checked
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				enabled: false
				text: qsTr("Night mode")
				subText: qsTr("Reduces eyestrain in poorly-lit environments.")
				secondaryItem: Switch {
					id: toggleNightMode
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: toggleNightMode.checked = !toggleNightMode.checked
			}


			ListItem.Subheader {
				text: qsTr("Window")
			}
			ListItem.Subtitled {
				enabled: false
				text: qsTr("Show borderless window")
				subText: qsTr("Removes the borders around the application's window.")
				secondaryItem: Switch {
					id: toggleBorderlessWindow
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: {
					toggleBorderlessWindow.checked = !toggleBorderlessWindow.checked
					applicationWindow.flags = toggleBorderlessWindow.checked ? Qt.FramelessWindowHint : Qt.Window
				}
			}
		}
	}
	Component.onDestruction: {
		settings.enableLargerText = toggleLargerText.checked
		settings.enableNightMode = toggleNightMode.checked
		settings.enableBorderlessWindow = toggleBorderlessWindow.checked
	}
}
