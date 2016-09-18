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
import Material 0.2
import Material.ListItems 0.1 as ListItem
import Material.Extras 0.1


Page {
	title: qsTr("Preferences")
	Flickable {
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: parent.height * 1.25
		boundsBehavior: Flickable.StopAtBounds
		Column {
			anchors.fill: parent
			ListItem.Subheader {
				text: qsTr("Interface")
			}
			ListItem.SimpleMenu {
				text: qsTr("Language")
				model: interfaceLanguages
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				text: qsTr("Large text")
				subText: qsTr("Show larger text.")
				secondaryItem: Switch {
					id: toggleLargeText
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: toggleLargeText.checked = !toggleLargeText.checked
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				text: qsTr("Night mode")
				subText: qsTr("")
				secondaryItem: Switch {
					id: toggleNightMode
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: toggleNightMode.checked = !toggleNightMode.checked
			}
			ListItem.Subheader {
				text: qsTr("Perfomance")
			}
/*
			ListItem.Subtitled {
				text: qsTr("")
				subText: qsTr("")
				secondaryItem: Switch {
					anchors.verticalCenter: parent.verticalCenter
				}
			}
			ListItem.Divider {}
*/
			ListItem.SimpleMenu {
				text: qsTr("Framebuffer resolution")
				model: framebufferResolutions
			}
			ListItem.Subheader {
				text: qsTr("About")
			}
			ListItem.Subtitled {
				text: qsTr("Project repository")
				subText: "https://github.com/othieno/clockwork"
				onClicked: {
					Qt.openUrlExternally(subText)
				}
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				text: qsTr("Build version")
				subText: "0.0.0"
			}
			ListItem.Divider {}
			ListItem.Standard {
				text: qsTr("Licenses")
				onClicked: {
				}
			}
		}
	}
}
