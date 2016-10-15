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
	title: qsTr("Preferences")
	/**
	 * Set up the page when it's been completely loaded.
	 */
	Component.onCompleted: {
		applicationWindow.title = title + " - " + application.applicationName
	}
	/**
	 * The page's content.
	 */
	Flickable {
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: parent.height * 1.3
		boundsBehavior: Flickable.StopAtBounds
		Column {
			anchors.fill: parent
			ListItem.Standard {
				text: qsTr("About Clockwork")
				onClicked: pageStack.push("qrc:/view/AboutClockwork")
				action: Icon {
					anchors.centerIn: parent
					source: "qrc:/icon/action/info_outline"
					size: dp(32)
				}
			}
			ListItem.Divider {}
			ListItem.SimpleMenu {
				enabled: false
				text: qsTr("Language")
				model: preferences.availableLanguages
				action: Icon {
					anchors.centerIn: parent
					source: "qrc:/icon/action/translate"
					size: dp(32)
				}
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				text: qsTr("Performance")
				onClicked: pageStack.push("qrc:/view/PerformanceSettings")
				subText: qsTr("[Performance short description]")
				action: Icon {
					anchors.centerIn: parent
					source: "qrc:/icon/image/timer"
					size: dp(32)
				}
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				text: qsTr("Theme")
				onClicked: pageStack.push("qrc:/view/ThemeSettings")
				subText: qsTr("[Theme short description]")
				action: Icon {
					anchors.centerIn: parent
					source: "qrc:/icon/image/palette"
					size: dp(32)
				}
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				enabled: false
				text: qsTr("Configuration file location")
				subText: preferences.fileLocation
				action: Icon {
					anchors.centerIn: parent
					source: "qrc:/icon/file/folder_open"
					size: dp(32)
				}
			}
		}
	}
	Component.onDestruction: {
	}
}
