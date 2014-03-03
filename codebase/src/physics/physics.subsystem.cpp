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
#include "physics.subsystem.hh"
#include "services.hh"
#include "scene.viewer.hh"

using clockwork::physics::PhysicsSubsystem;


PhysicsSubsystem::PhysicsSubsystem()
{}


PhysicsSubsystem::UpdateTask::UpdateTask(scene::Scene& scene) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::PhysicsUpdateTask)),
_scene(scene)
{}


void
PhysicsSubsystem::update()
{
   system::Services::Concurrency.submitTask(new UpdateTask(scene::Scene::getUniqueInstance()));
}


void
PhysicsSubsystem::UpdateTask::onRun()
{
   // Update the scene geometry.
   const auto* const viewer = _scene.getViewer();
   const auto CMTM = viewer != nullptr ?
   clockwork::Matrix4::translate(clockwork::Point3::negative(viewer->getPosition())) : clockwork::Matrix4();

   for (auto* const node : _scene.getRootNodes())
      node->updateGeometry(CMTM);

   clockwork::system::Services::Physics.submitUpdateCompleteTask();
}
