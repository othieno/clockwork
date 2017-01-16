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
import QtQuick.Layouts 1.1
import Material 0.3
import Material.ListItems 0.1 as ListItem


ListItem.BaseListItem {
	id: control
	dividerInset: 0
	height: 48 * Units.dp
	implicitHeight: 48 * Units.dp
	implicitWidth: label_.implicitWidth + row.spacing

	property alias label: label_.text
	property var value

	RowLayout {
		id: row
		anchors.fill: parent

		anchors.leftMargin: control.margins
		anchors.rightMargin: control.margins

		spacing: 16 * Units.dp

		ColumnLayout {
			Layout.alignment: Qt.AlignVCenter
			Layout.preferredHeight: parent.height
			Label {
				Layout.alignment: Qt.AlignVCenter
				Layout.fillWidth: true

				id: label_
				elide: Text.ElideRight
				style: "subheading"
				color: control.selected ? Theme.primaryColor
						: darkBackground ? Theme.dark.textColor : Theme.light.textColor
			}
		}
	}
}
