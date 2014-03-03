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

#include "subsystem.hh"
#include "task.hh"
#include "scene.hh"


namespace clockwork {
namespace physics {

class PhysicsSubsystem : public clockwork::system::Subsystem
{
Q_OBJECT
friend clockwork::system::Services;
private:
   /**
    * All subsystems are singletons. As such the default constructor is hidden,
    * and the copy operator and constructor are deleted from the implementation.
    */
   PhysicsSubsystem();
   PhysicsSubsystem(const PhysicsSubsystem&) = delete;
   PhysicsSubsystem& operator=(const PhysicsSubsystem&) = delete;
   /**
    * The Physics subsystem's update task updates scene geometry.
    */
   class UpdateTask : public concurrency::Task
   {
   public:
      /**
       * Instantiate an UpdateTask that will update geometry for objects in a given scene.
       * @param scene the scene containing the objects to update.
       */
      UpdateTask(scene::Scene& scene);
      /**
       * @see clockwork::concurrency::Task::onRun.
       */
      virtual void onRun() override final;
   private:
      /**
       * A reference to the scene to update.
       */
      scene::Scene& _scene;
   };
private slots:
   /**
    * Update the subsystem.
    */
   void update();
};

} // namespace physics
} // namespace clockwork
