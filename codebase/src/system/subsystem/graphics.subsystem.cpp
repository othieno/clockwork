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
#include "scene.viewer.hh"
#include "services.hh"
#include "image.filter.hh"
#include "render.algorithm.hh"
#include "scene.hh"
#include <cassert>

using clockwork::system::GraphicsSubsystem;
using clockwork::graphics::Framebuffer;


GraphicsSubsystem::GraphicsSubsystem() :
_framebuffer(Framebuffer::Resolution::XGA)
{}


clockwork::Error
GraphicsSubsystem::initialise()
{
   return clockwork::Error::None;
}


clockwork::Error
GraphicsSubsystem::destroy()
{
   return clockwork::Error::None;
}


void
GraphicsSubsystem::renderObject(clockwork::scene::Object& object)
{
   using clockwork::scene::Property;

   if (object.isPruned())
      return;

   if (object.hasProperty(Property::Identifier::Appearance))
   {
      for (auto* const viewer : clockwork::scene::Scene::getInstance().getActiveViewers())
      {
         if (isObjectVisibleFromViewer(object, *viewer))
         {
            const auto* const renderer =
            clockwork::graphics::RenderAlgorithmFactory::getInstance().get(viewer->getRenderAlgorithm());
            assert(renderer != nullptr);

            renderer->apply(object, *viewer);
         }
      }
   }

   // Render the subgraph.
   for (auto* const child : object.getChildren())
      renderObject(*child);
}


bool
GraphicsSubsystem::isObjectVisibleFromViewer
(
   const clockwork::scene::Object&,
   const clockwork::scene::Viewer&
) const
{
   //TODO Implement me.
   return true;
}


void
GraphicsSubsystem::postProcess
(
   const clockwork::graphics::ImageFilter::Type&,
   const clockwork::graphics::Viewport&
)
{
   //TODO Implement me.
}


clockwork::graphics::Framebuffer&
GraphicsSubsystem::getFramebuffer()
{
   return _framebuffer;
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
GraphicsSubsystem::isStencilTestEnabled() const
{
   return false;
}


bool
GraphicsSubsystem::isDepthTestEnabled() const
{
   return true;
}
