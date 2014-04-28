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
#include "framebuffer.hh"
#include "image.filter.hh"
#include "scene.viewer.hh"
#include "property.appearance.hh"


namespace clockwork {
namespace system {

/**
 * @see services.hh.
 */
class Services;


class GraphicsSubsystem : public clockwork::system::Subsystem
{
Q_OBJECT
friend class clockwork::system::Services;
public:
   /**
    * Render a scene object and its children.
    * @param object the scene object to render.
    */
   void renderObject(clockwork::scene::Object& object);
   /**
    * Returns true if a scene object is inside a viewer's view frustum. In other
    * words, this member function performs view frustum culling.
    * @param object the object to check.
    * @param viewer the viewer containing the frustum which the object will be checked against.
    */
   bool isObjectVisibleFromViewer(const clockwork::scene::Object& object, const clockwork::scene::Viewer& viewer) const;
   /**
    * Apply post-processing filters to a section of the framebuffer.
    * @param type the type of image filter to apply.
    * @param viewport the viewport of the framebuffer that the filter will be applied to.
    */
   void postProcess(const clockwork::graphics::ImageFilter::Type& type, const clockwork::graphics::Viewport& viewport);
   /**
    * Return the framebuffer.
    */
   clockwork::graphics::Framebuffer& getFramebuffer();
   /**
    * @see Framebuffer::plot(2).
    */
   inline void plot
   (
      const clockwork::graphics::Fragment& fragment,
      const std::function<uint32_t(const clockwork::graphics::Fragment&)>& fop
   )
   {
      _framebuffer.plot(fragment, fop);
   }
   /**
    * @see Framebuffer::plot(3).
    */
   inline void plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t& pixel)
   {
      _framebuffer.plot(x, y, z, pixel);
   }
   /**
    * Returns true if scissor testing is enabled, false otherwise.
    */
   bool isScissorTestEnabled() const;
   /**
    * Returns true if alpha testing is enabled, false otherwise.
    */
   bool isAlphaTestEnabled() const;
   /**
    * Returns true if stencil testing is enabled, false otherwise.
    */
   bool isStencilTestEnabled() const;
   /**
    * Returns true if depth testing is enabled, false otherwise.
    */
   bool isDepthTestEnabled() const;
private:
   /**
    * All subsystems are singletons. As such the default constructor is hidden,
    * and the copy operator and constructor are deleted from the implementation.
    */
   GraphicsSubsystem();
   GraphicsSubsystem(const GraphicsSubsystem&) = delete;
   GraphicsSubsystem& operator=(const GraphicsSubsystem&) = delete;
   /**
    * @see Subsystem::initialise.
    */
   clockwork::Error initialise() override final;
   /**
    * @see Subsystem::destroy.
    */
   clockwork::Error destroy() override final;
   /**
    * The framebuffer.
    */
   clockwork::graphics::Framebuffer _framebuffer;
};

} // namespace system
} // namespace clockwork
