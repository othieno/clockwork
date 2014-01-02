/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
 *
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
#include "ui.display.hh"
#include "ui.hh"
#include "debug.hh"
#include "services.hh"
#include <QPainter>
#include <QPaintEvent>


clockwork::ui::GUIDisplay::GUIDisplay(clockwork::ui::UserInterface& ui) :
_qPainter(),
_qPen(Qt::yellow),
_framebuffer(clockwork::system::Services::Graphics.getFramebuffer())
{
	// Match the display resolution with the framebuffer's resolution.
//	const auto& framebufferResolution = _framebuffer.size();
//	setMinimumSize(framebufferResolution);
//	setMaximumSize(framebufferResolution);

	// Connect the GraphicsSubsystem::updateComplete signal to this widget's update
	// slot so that the display is updated when the framebuffer contains a complete frame.
	connect(&clockwork::system::Services::Graphics, SIGNAL(updateComplete()), this, SLOT(update()));
}


void
clockwork::ui::GUIDisplay::paintEvent(QPaintEvent* const event)
{
	// Begin painting this device.
	_qPainter.begin(this);

	// Draw the framebuffer.
	auto& rect = event->rect();
	_qPainter.drawImage(rect, _framebuffer);

	// Turn on text anti-aliasing and print debug information.
/*
	if (clockwork::system::Debug::printToDisplay)
	{
		const auto& debugInfo = QObject::tr(clockwork::system::Debug::toString().c_str());

		_qPainter.setRenderHint(QPainter::TextAntialiasing);
		_qPainter.setPen(_qPen);
		_qPainter.drawText(rect.adjusted(5, 5, 0, 0), debugInfo);
	}
*/
	// End painting.
	_qPainter.end();
}
