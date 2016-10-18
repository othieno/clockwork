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
	title: qsTr("Software License")
	Flickable {
		property var padding: dp(20)
		id: flickable
		anchors.fill: parent
		contentHeight: Math.max(content.implicitHeight + (2 * flickable.padding), height)
		boundsBehavior: Flickable.StopAtBounds
		Column {
			id: content
			anchors.fill: parent
			anchors.margins: flickable.padding
			Text {
				width: parent.width
				font.family: "Roboto"
				font.pixelSize: dp(16)
				wrapMode: Text.WordWrap
				color: "#4A4A4A"
				textFormat: Text.RichText
				text:"\
				<h1>MIT License</h1>\
				<p>Copyright &copy; 2013-2016 Jeremy Othieno.</p>\
				<p>Permission is hereby granted, free of charge, to any person obtaining a copy\
				of this software and associated documentation files (the “Software”), to deal\
				in the Software without restriction, including without limitation the rights\
				to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\
				copies of the Software, and to permit persons to whom the Software is\
				furnished to do so, subject to the following conditions:</p>\
				<p>The above copyright notice and this permission notice shall be included in\
				all copies or substantial portions of the Software.</p>\
				<p>THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\
				IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\
				FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\
				AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\
				LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\
				OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\
				THE SOFTWARE.</p>"
			}
		}
	}
	Scrollbar {
		flickableItem: flickable
	}
}
