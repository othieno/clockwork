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
#pragma once

#include <QObject>
#include <QRunnable>


namespace clockwork {
namespace concurrency {

class Task : public QObject, public QRunnable
{
Q_OBJECT
public:
   /**
    * Instantiate a task with a given priority.
    */
   explicit Task(const int& priority = 0);
   /**
    * Return the task's priority.
    */
   const int& getPriority() const;
   /**
    * Return the task's priority.
    */
   virtual void run() override final;
   /**
    * The operation that is performed by this task.
    */
   virtual void onRun() = 0;
private:
   /**
    * The task's priority.
    */
   const int _priority;
signals:
   /**
    * A signal that is raised when the task completes.
    */
   void taskComplete();
};

/**
 * Task priorities.
 */
enum class TaskPriority : int
{
   GraphicsPostProcessingTask = 0,
   GraphicsGeometryUpdateTask = GraphicsPostProcessingTask + 1,
   GraphicsRenderTask = GraphicsGeometryUpdateTask + 1,
   GraphicsUpdateTask = GraphicsRenderTask + 1
};

} // namespace concurrency
} // namespace clockwork
