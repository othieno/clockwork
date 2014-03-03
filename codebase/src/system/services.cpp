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
#include "services.hh"
#include <thread>


clockwork::system::ExecutionContext clockwork::system::Services::Context;
clockwork::concurrency::ConcurrencySubsystem clockwork::system::Services::Concurrency;
clockwork::physics::PhysicsSubsystem clockwork::system::Services::Physics;
clockwork::graphics::GraphicsSubsystem clockwork::system::Services::Graphics;
clockwork::system::AssetManager clockwork::system::Services::Assets;


clockwork::Error
clockwork::system::Services::initialise(const int& argc, const char** const argv)
{
   buildExecutionContext(argc, argv);

   // Initialise the update chain.
   QObject::connect(&Physics, SIGNAL(updateComplete()), &Graphics, SLOT(update()));

   return Error::None;
}


void
clockwork::system::Services::update()
{
   // Make sure the previous update task is aborted before a new one is created.
   //static volatile bool hasPreviousTaskCompleted = true;
   //if (!hasPreviousTaskCompleted)
   //{
      //hasPreviousTaskCompleted = true;
//TODO      Concurrency::stopAllTasks();
   //}
   // All previous update tasks have been aborted, start new ones.
   Physics.update();
}


clockwork::Error
clockwork::system::Services::dispose(const clockwork::Error& applicationExitError)
{
   return clockwork::Error::None;
}


void
clockwork::system::Services::buildExecutionContext(const int& argc, const char** const argv)
{}


void
clockwork::system::Services::sleep(const int64_t& ms)
{
   std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
