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
#include "ui.busy.indicator.hh"
#include "scene.hh"
#include "scene.object.hh"


namespace clockwork {
namespace graphics {

class GraphicsSubsystem : public clockwork::system::Subsystem
{
Q_OBJECT
friend clockwork::system::Services;
public:
   /**
    * Return the framebuffer.
    */
   Framebuffer& getFramebuffer();
   /**
    * Set the image filter to apply to the framebuffer during post-processing.
    * @param type the type of the image filter to set.
    */
   void setImageFilter(const ImageFilter::Type& type);
   /**
    * Return the type of the current image filter.
    */
   const ImageFilter::Type& getImageFilterType() const;
   /**
    * @see Framebuffer::plot(2).
    */
   inline void plot(const Fragment& fragment, const std::function<uint32_t(const Fragment&)>& fop)
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
    * The framebuffer.
    */
   Framebuffer _framebuffer;
   /**
    * The image filter that is applied to the framebuffer during post-processing.
    */
   ImageFilter::Type _imageFilterType;
   /**
    * The Graphics subsystem's update task renders the scene's visible geometry.
    */
   class UpdateTask : public concurrency::Task
   {
   public:
      /**
       * Instantiate an UpdateTask that will draw all visible objects in a given
       * scene to a specified framebuffer.
       * @param scene the scene to render.
       * @param framebuffer the framebuffer that will contain the rendered scene.
       * @param imageFilterType the type of post-processing filter to apply to the framebuffer.
       */
      UpdateTask(scene::Scene& scene, Framebuffer& framebuffer, const ImageFilter::Type& imageFilterType);
      /**
       * @see clockwork::concurrency::Task::onRun.
       */
      virtual void onRun() override final;
   private:
      /**
       * A reference to the scene to render.
       */
      scene::Scene& _scene;
      /**
       * The framebuffer where the rendered scene's information will be stored.
       */
      Framebuffer& _framebuffer;
      /**
       * The type of image filter to apply during the post-processing phase.
       */
      const ImageFilter::Type _imageFilterType;
   };
private slots:
   /**
    * Update the subsystem.
    */
   void update();
};

} // namespace graphics
} // namespace clockwork
