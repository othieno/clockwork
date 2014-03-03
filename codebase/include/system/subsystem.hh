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

#include <QObject>
#include "task.hh"


namespace clockwork {
namespace system {

/**
 * @see services.hh
 */
class Services;

class Subsystem : public QObject
{
Q_OBJECT
public:
   /**
    * Submit a task that will emit a subsystem's 'updateComplete' signal.
    */
   void submitUpdateCompleteTask();
private:
   /**
    * The UpdateTaskCompleted is a task that emits a subsystem's 'updateComplete'
    * signal upon its completion, and nothing more.
    */
   class UpdateCompleteTask : public clockwork::concurrency::Task
   {
   public:
      /**
       * Instantiate an UpdateCompleteTask that will, upon completion, emit a given
       * subsystem's 'updateComplete' signal.
       * @param subsystem the subsystem for which we wish to emit an 'updateComplete' signal.
       */
      explicit UpdateCompleteTask(const Subsystem& subsystem);
      /**
       * @see clockwork::concurrency::Task::onRun.
       */
      virtual void onRun() override final;
   };
signals:
   /**
    * A signal that is emitted when the system update is complete.
    */
   void updateComplete();
};

} // namespace system
} // namespace clockwork
