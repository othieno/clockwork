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

#include <QApplication>
#include <QBasicTimer>
#include "error.hh"
#include "window.hh"
#include "services.hh"


namespace clockwork {

class System : public QApplication
{
Q_OBJECT
public:
   /**
    * Initialise the system.
    * @param argc the number of command line arguments.
    * @param argv the command line arguments.
    */
   System(int& argc, char** argv);
   /**
    * The destructor.
    */
   ~System();
   /**
    * The system is unique!
    */
   System(const System&) = delete;
   System& operator=(const System&) = delete;
   /**
    * Initialise the system.
    */
   clockwork::Error initialise();
public slots:
   /**
    * Update the system.
    */
   void update();
private:
    /**
     * Parse the command line arguments and return an execution context.
     * @param argc the number of command line arguments.
     * @param argv the command line arguments.
     */
    clockwork::system::ExecutionContext parseCommandLineArguments(const int& argc, const char** argv);
    /**
     * The window.
     */
    clockwork::ui::Window _window;
    /**
     * This timer is used to coalesce (group) multiple updates into one. When an
     * update is triggered, then this timer starts a countdown. If another update
     * is requested while the timer is counting down, then it is restarted. Once the
     * timer times out, then an update is made.
     */
    QBasicTimer _coalescer;
    /**
     * The timerEvent event handler contains the actual system update algorithm and is
     * called when _coalescer times out.
     */
    void timerEvent(QTimerEvent* const) override final;
signals:
    /**
     * This signal is emitted when the system update is complete.
     */
   void updated();
};

} // namespace clockwork
