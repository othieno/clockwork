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
#include <memory>
#include "graphics.subsystem.hh"
#include "scene.hh"
#include "scene.viewer.hh"
#include "services.hh"
#include "image.filter.factory.hh"
#include "post.process.task.hh"

using clockwork::graphics::GraphicsSubsystem;


GraphicsSubsystem::GraphicsSubsystem() :
_framebuffer(Framebuffer::Resolution::XGA),
_imageFilterType(clockwork::graphics::ImageFilterFactory::getUniqueInstance().getDefaultKey())
{}


GraphicsSubsystem::UpdateTask::UpdateTask
(
   scene::Scene& scene,
   Framebuffer& framebuffer,
   const ImageFilter::Type& type
) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsUpdateTask)),
_scene(scene),
_framebuffer(framebuffer),
_imageFilterType(type)
{}


void
GraphicsSubsystem::update()
{
   system::Services::Concurrency.submitTask(new UpdateTask(scene::Scene::getUniqueInstance(), _framebuffer, _imageFilterType));
}


void
GraphicsSubsystem::UpdateTask::onRun()
{
   _framebuffer.clear();

   // Render the scene based on the current viewer's context, then apply the post-processing filter.
   auto* const viewer = _scene.getViewer();
   if (viewer != nullptr)
   {
      for (auto* const node : _scene.getRootNodes())
         node->render(*viewer);

      auto* const postProcessTask = new PostProcessTask(_framebuffer, _imageFilterType);
      if (postProcessTask != nullptr)
      {
         // Connect the post-process task's 'taskComplete' signal to this subsystem's 'updateComplete' signal
         // since post-processing is the last operation in the graphics update phase. Note that when this is done,
         // there's no need to submit an 'UpdateCompleteTask'.
         connect(postProcessTask, SIGNAL(taskComplete()), &clockwork::system::Services::Graphics, SIGNAL(updateComplete()));
         clockwork::system::Services::Concurrency.submitTask(postProcessTask);
         return;
      }
   }
   clockwork::system::Services::Graphics.submitUpdateCompleteTask();
}


clockwork::graphics::Framebuffer&
GraphicsSubsystem::getFramebuffer()
{
   return _framebuffer;
}


const clockwork::graphics::ImageFilter::Type&
GraphicsSubsystem::getImageFilterType() const
{
   return _imageFilterType;
}


void
GraphicsSubsystem::setImageFilter(const clockwork::graphics::ImageFilter::Type& type)
{
   _imageFilterType = type;
}


bool
GraphicsSubsystem::isScissorTestEnabled() const
{
   return false;
}


bool
GraphicsSubsystem::isAlphaTestEnabled() const
{
   return false;
}


bool
clockwork::graphics::GraphicsSubsystem::isStencilTestEnabled() const
{
   return false;
}


bool
clockwork::graphics::GraphicsSubsystem::isDepthTestEnabled() const
{
   return true;
}
