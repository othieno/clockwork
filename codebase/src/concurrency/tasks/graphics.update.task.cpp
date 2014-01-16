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
#include "graphics.update.task.hh"
#include "scene.viewer.hh"
#include "scene.hh"
#include "services.hh"


clockwork::concurrency::GraphicsUpdateTask::GraphicsUpdateTask() :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsUpdateTask))
{}


void
clockwork::concurrency::GraphicsUpdateTask::onRun()
{
   //auto& Graphics = clockwork::system::Services::Graphics;
   auto& scene = clockwork::scene::Scene::getUniqueInstance();
   auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();
   const auto& imageFilterType = clockwork::system::Services::Graphics.getImageFilterType();

   // Clear the framebuffer before rendering a new frame.
   framebuffer.clear();

   // Render the scene based on the current viewer's context.
   auto* const viewer = scene.getViewer();
   if (viewer != nullptr)
   {
      auto& rootNodes = scene.getRootNodes();
      if (!rootNodes.empty())
      {
         // Update scene geometry.
         const auto CMTM = clockwork::Matrix4::translate(clockwork::Point3::negative(viewer->getPosition()));
         for (auto* const node : rootNodes)
            node->updateGeometry(CMTM);

         // Render the scene.
         for (auto* const node : rootNodes)
            node->render(*viewer);


         // Apply the post-processing filter to the framebuffer.
         auto* const task = new clockwork::concurrency::PostProcessingTask(framebuffer, imageFilterType);
         if (task != nullptr)
         {
            // Connect the task's 'taskComplete' signal to this subsystem's 'updateComplete',
            // since post-processing is the last operation in the graphics update phase.
            connect
            (
               task, SIGNAL(taskComplete()),
               &clockwork::system::Services::Graphics, SIGNAL(updateComplete())
            );

            // Submit the task.
            clockwork::system::Services::Concurrency.submitTask(task);
         }
      }
   }
   else
      clockwork::system::Services::Graphics.signalUpdateComplete();
}


clockwork::concurrency::GeometryUpdateTask::GeometryUpdateTask
(
   clockwork::scene::Object& object,
   const clockwork::Matrix4& CMTM
) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsGeometryUpdateTask)),
_object(object),
_CMTM(CMTM)
{}


void
clockwork::concurrency::GeometryUpdateTask::onRun()
{
   const auto& position = _object.getPosition();
   const auto& rotation = _object.getRotation();
   const auto& scale = _object.getScalingVector();

   const auto& objectModelMatrix = _CMTM * clockwork::Matrix4::model(position, rotation, scale);

   // Update the object's model matrix, then update the subgraph's geometry.
   _object.setModelMatrix(objectModelMatrix);

   // Update the subgraph's geometry.
   for (auto* const node : _object.getChildren())
      node->updateGeometry(objectModelMatrix);
}


clockwork::concurrency::PostProcessingTask::PostProcessingTask
(
   clockwork::graphics::Framebuffer& framebuffer,
   const clockwork::graphics::ImageFilter::Type& type
) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsPostProcessingTask)),
_framebuffer(framebuffer),
_imageFilter(clockwork::graphics::ImageFilterFactory::getUniqueInstance().get(type))
{}


void
clockwork::concurrency::PostProcessingTask::onRun()
{
   // TODO
}
