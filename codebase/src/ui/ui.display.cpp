/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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

using clockwork::ui::GUIDisplayDevice;


GUIDisplayDevice::GUIDisplayDevice(clockwork::ui::UserInterface& ui) :
QWidget(&ui),
_painter(),
_pen(Qt::yellow),
_framebuffer(clockwork::system::Services::Graphics.getFramebuffer())
{
   connect(&_framebuffer, SIGNAL(frameReady()), this, SLOT(onFrameReady()));

   // Initialise the output buffer.
   onFrameReady();
}


void
GUIDisplayDevice::onFrameReady()
{
   setUpdatesEnabled(false);

   // Upload the framebuffer's pixel buffer into the output buffer.
   _outputBuffer = QImage
   (
      reinterpret_cast<const uchar*>(_framebuffer.getPixelBuffer()),
      _framebuffer.getWidth(),
      _framebuffer.getHeight(),
      QImage::Format_ARGB32
   );

   setUpdatesEnabled(true);
   update();
}


void
GUIDisplayDevice::paintEvent(QPaintEvent* const)
{
   // Begin painting this device.
   _painter.begin(this);

   //TODO Optimise this to draw only the part of the screen that doesn't change.
   // Draw the output buffer.
   _painter.drawImage(rect(), _outputBuffer);
//   auto& targetRect = event->rect();
//   _painter.drawImage(rect, _outputBuffer.copy(rect));
//   _painter.drawImage(targetRect, _outputBuffer, rect());

/*
 * TODO Implement me.
 *
   if (clockwork::system::Services::ExecutionContext.printDebugInformation)
   {
      const auto& debugInfo = QObject::tr(clockwork::system::Debug::toString().c_str());

      _painter.setRenderHint(QPainter::TextAntialiasing);
      _painter.setPen(_pen);
      _painter.drawText(rect.adjusted(5, 5, 0, 0), debugInfo);
   }
*/
   // End painting.
   _painter.end();
}
