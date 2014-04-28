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
#include "system.hh"
#include "scene.hh"
#include "task.update.hh"
#include <cassert>

using clockwork::System;
using clockwork::system::Services;


// Say NO to global variables. But they're convenient sometimes.
static QList<clockwork::system::Subsystem*> allSubsystems =
{&Services::Concurrency, /*&Services::Animation,*/ &Services::Physics, &Services::Graphics};


System::System(int& argc, char** argv) :
QApplication(argc, argv)
{
   Services::ExecutionContext =
   parseCommandLineArguments(const_cast<const int&>(argc), const_cast<const char**>(argv));

   connect(&_window, SIGNAL(stateChanged()), this, SLOT(update()));
}


System::~System()
{
   for (auto* const subsystem : allSubsystems)
      subsystem->destroy();
}


clockwork::Error
System::initialise()
{
   auto error = clockwork::Error::None;
   for (auto* const subsystem : allSubsystems)
   {
      error = subsystem->initialise();
      if (error != clockwork::Error::None)
         return error;
   }
   return _window.open(false);
}


void
System::update()
{
   static const int timeout = 100;

   // Coalesce update calls into a single one. The actual update is found in
   // the timerEvent member function, and is triggered when _coalescer expires.
   if (!_coalescer.isActive())
      _coalescer.start(timeout, this);
   else if (_coalescer.isActive())
   {
      _coalescer.stop();
      _coalescer.start(timeout, this);
   }
}


clockwork::system::ExecutionContext
System::parseCommandLineArguments(const int& argc, const char** argv)
{
   std::cerr << "Implement System::parseCommandLineArguments(const int& argc, const char** argv)" << std::endl;
   (void)argc;
   (void)argv;
   return clockwork::system::ExecutionContext();
}


void
System::timerEvent(QTimerEvent* const e)
{
   if (e->timerId() == _coalescer.timerId())
   {
      _coalescer.stop();

      // Remove all outdated tasks and start afresh.
      Services::Concurrency.purgeTasks();
      Services::Concurrency.submitTask(new clockwork::concurrency::UpdateTask);
   }
}
