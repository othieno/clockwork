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


ApplicationWindow {
	id: applicationWindow
	visible: true
	visibility: "Maximized"
	//flags: Qt.FramelessWindowHint
	initialPage: page
	theme {
		accentColor: Palette.colors["blueGrey"]["700"]
		primaryColor: Palette.colors["blue"]["700"]
		tabHighlightColor: "white"
	}
	/**
	 *
	 */
	//Component.onCompleted: {}
	/**
	 * The application's page content.
	 */
	TabbedPage {
		id: page
		title: application.applicationName
		actions: [
			Action {
				name: qsTr("Preferences")
				iconSource: "qrc:/icon/action/Preferences"
				onTriggered: pageStack.push("qrc:/view/Preferences")
				hoverAnimation: true
			}
		]
		Repeater {
			model: [
				"Scene",
				"Documentation",
			]
			delegate: Tab {
				title: qsTr(modelData)
				source: "qrc:view/%1Viewer".arg(modelData)
				onVisibleChanged: {
					if (visible) {
						applicationWindow.title = title + " - " + application.applicationName
					}
				}
			}
		}
	}
	/**
	 *
	 */
	//Component.onDestruction: {}
}
