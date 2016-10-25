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
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import Material 0.2


ApplicationWindow {
	id: applicationWindow
	visible: true
	visibility: Window.Maximized
	title: "%1%2".arg(pageStack.currentItem !== null ? pageStack.currentItem.title + " - " : "").arg(application.applicationName)
	theme {
		accentColor: Palette.colors["blueGrey"]["700"]
		primaryColor: Palette.colors["blue"]["700"]
		tabHighlightColor: "white"
	}
	/**
	 *
	 */
	Component.onCompleted: {
		if (settings.showBorderlessWindow) {
			flags = Qt.FramelessWindowHint
		}
		application.update()
	}
	/**
	 * The application's page content.
	 */
	initialPage: Page {
		/**
		 * The page's available sections.
		 */
		property var sections: [
			{
				viewId: "Output",
				title: qsTr("Output"),
			},
			{
				viewId: "PipelineConfiguration",
				title: qsTr("Pipeline Configuration"),
			},
			{
				viewId: "ScissorConfiguration",
				title: qsTr("Scissor Configuration"),
			},
			{
				viewId: "StencilConfiguration",
				title: qsTr("Stencil Configuration"),
			},
			{
				viewId: "Documentation",
				title: qsTr("Documentation"),
			},
		]
		/**
		 * The main page's current section.
		 */
		property var currentSection: sections[0]
		/**
		 * The main page's title.
		 */
		property var pageTitle: qsTr("Renderer")
		/**
		 * The main page's subtitle, which is the current section's title.
		 */
		property var pageSubtitle: currentSection.title

		id: page
		title: "%1 – %2".arg(pageSubtitle).arg(pageTitle)
		actionBar.title: "%1 – %2".arg(pageTitle).arg(pageSubtitle)
		backAction: Action {
			iconSource: navigation.expanded ? "qrc:/icon/navigation/close" : "qrc:/icon/navigation/menu"
			onTriggered: navigation.expanded = !navigation.expanded
		}
		actions: [
			Action {
				iconSource: "qrc:/icon/action/settings"
				onTriggered: pageStack.push("qrc:/view/Settings")
				hoverAnimation: true
			}
		]
		Sidebar {
			id: navigation
			expanded: true
			width: dp(55)
			ColumnLayout {
				Repeater {
					model: page.sections
					delegate: IconButton {
						Layout.alignment: Qt.AlignCenter
						Layout.preferredWidth: navigation.width
						Layout.preferredHeight: navigation.width
						iconSource: "qrc:/icon/action/show%1View".arg(modelData.viewId)
						enabled: page.currentSection.viewId != modelData.viewId
						onClicked: page.currentSection = page.sections[index]
						color: Theme.accentColor
					}
				}
			}
		}
		Loader {
			source: "qrc:/view/%1".arg(page.currentSection.viewId)
			visible: status == Loader.Ready
			asynchronous: true
			anchors.top: parent.top
			anchors.left: navigation.right
			anchors.right: parent.right
			anchors.bottom: parent.bottom
		}
	}
	/**
	 *
	 */
	//Component.onDestruction: {}
}
