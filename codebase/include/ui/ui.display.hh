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
#pragma once

#include "framebuffer.hh"
#include <QWidget>
#include <QPainter>
#include <QPen>


namespace clockwork {
namespace ui {
/**
 * @see ui.hh.
 */
class UserInterface;

/**
 * The display device. This will be the final destination of pixels stored in the framebuffer.
 */
class GUIDisplayDevice : public QWidget
{
Q_OBJECT
public:
   /**
    * Instantiate a GUIDisplayDevice.
    * @param ui the user interface that this component is attached to.
    */
   GUIDisplayDevice(UserInterface& ui);
private:
   /**
    * The custom paint event loads data from a framebuffer and displays it.
    */
   virtual void paintEvent(QPaintEvent* event) override final;
   /**
    * The painter.
    */
   QPainter _painter;
   /**
    * The pen used to write text to the display.
    */
   QPen _pen;
   /**
    * A reference to the framebuffer containing the rendered scene.
    */
   const clockwork::graphics::Framebuffer& _framebuffer;
   /**
    * A buffer that stores a copy of the framebuffer's pixels.
    */
   QImage _outputBuffer;
private slots:
   /**
    * This slot must be called when a complete frame is available for drawing.
    * It will upload the framebuffer's current pixel buffer into this display
    * device's output buffer, a buffer which will then be used for future
    * paint events until it gets updated.
    */
   void onFrameReady();
};

} // namespace ui
} // namespace clockwork
