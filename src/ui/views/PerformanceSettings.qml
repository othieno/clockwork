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
	id: performanceSettingsView
	title: qsTr("Performance Settings")
	Flickable {
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: parent.height
		boundsBehavior: Flickable.StopAtBounds
		Column {
			anchors.fill: parent
			ListItem.SimpleMenu {
				enabled: false
				text: qsTr("Framebuffer resolution")
				model: settings.availableFramebufferResolutions
			}
			ListItem.Divider {}
			ListItem.Subtitled {
				enabled: false
				text: qsTr("Show frames per second")
				subText: qsTr("Displays the number of frames rendered per second.")
				secondaryItem: Switch {
					id: toggleFramesPerSecond
					checked: settings.showFramesPerSecond
					anchors.verticalCenter: parent.verticalCenter
				}
				onClicked: toggleFramesPerSecond.checked = !toggleFramesPerSecond.checked
			}
		}
	}
	Component.onDestruction: {
		settings.showFramesPerSecond = toggleFramesPerSecond.checked
	}
}
