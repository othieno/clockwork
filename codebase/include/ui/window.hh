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

#include "ui.hh"
#include <QMovie>


namespace clockwork {
namespace ui {

class Window : public QMainWindow
{
Q_OBJECT
public:
   Window();
   Window(const Window&) = delete;
   Window& operator=(const Window&) = delete;
   /**
    * Build the user interface and show the window.
    * @param fullscreen open the window in full screen mode.
    */
   clockwork::Error open(const bool fullscreen = true);
private:
   /**
    * The user interface.
    */
   clockwork::ui::UserInterface* const _userInterface;
signals:
   /**
    * This signal is emitted when the window's state changes, which means that
    * the system (or underlying models wrt. the MVC pattern) need to be updated.
    */
   void stateChanged();
};

} // namespace ui
} // namespace clockwork
