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

#include "scene.object.hh"
#include "render.algorithm.hh"
#include "projection.hh"
#include "viewport.hh"
#include "frustum.hh"
#include "image.filter.hh"
#include "texture.filter.hh"
#include "line.algorithm.hh"
#include "primitive.mode.hh"


namespace clockwork {
namespace scene {

class Viewer : public Object
{
public:
   /**
    * Return the view transformation matrix.
    */
   const clockwork::Matrix4& getViewTransform();
   /**
    * Return the projection transformation matrix.
    */
   const clockwork::Matrix4& getProjectionTransform();
   /**
    * Return the view-projection transformation matrix.
    */
   const clockwork::Matrix4& getViewProjectionTransform();
   /**
    * Return the viewer's render algorithm identifier.
    */
   const clockwork::graphics::RenderAlgorithm::Identifier& getRenderAlgorithm() const;
   /**
    * Set the viewer's render algorithm.
    * @param identifier the identifier of the algorithm to set.
    */
   void setRenderAlgorithm(const clockwork::graphics::RenderAlgorithm::Identifier& identifier);
   /**
    * Return the viewer's projection type.
    */
   const clockwork::graphics::Projection::Type& getProjection() const;
   /**
    * Set the viewer's projection type.
    * @param type the projection type to set.
    */
   void setProjection(const clockwork::graphics::Projection::Type& type);
   /**
    * Return the viewer's viewport.
    */
   const clockwork::graphics::Viewport& getViewport() const;
   /**
    * Set the viewer's viewport.
    * @param viewport the viewport to set.
    */
   void setViewport(const clockwork::graphics::Viewport& viewport);
   /**
    * Set the viewer's viewport.
    * @param x the viewport's origin on the horizontal axis.
    * @param y the viewport's origin on the vertical axis.
    * @param width the viewport's width.
    * @param height the viewport's height.
    * @param near the linear mapping of the near clipping plane to the window coordinates.
    * @param far the linear mapping of the far clipping plane to the window coordinates.
    */
   void setViewport
   (
      const float& x,
      const float& y,
      const float& width,
      const float& height,
      const float& near = 0.0f,
      const float& far = 1.0f
   );
   /**
    * Return the viewer's view frustum.
    */
   const clockwork::graphics::Frustum& getFrustum() const;
   /**
    * Set the viewer's view frustum.
    * @param frustum the view frustum to set.
    */
   void setFrustum(const clockwork::graphics::Frustum& frustum);
   /**
    * Return the viewer's post-process image filter.
    */
   const clockwork::graphics::ImageFilter::Type& getImageFilter() const;
   /**
    * Set the viewer's post-process image filter.
    * @param type the type of image filter to set.
    */
   void setImageFilter(const clockwork::graphics::ImageFilter::Type& type);
   /**
    * Return the viewer's texture filter.
    */
   const clockwork::graphics::TextureFilter::Type& getTextureFilter() const;
   /**
    * Set the viewer's texture filter.
    * @param type the type of texture filter to set.
    */
   void setTextureFilter(const clockwork::graphics::TextureFilter::Type& type);
   /**
    * Return the viewer's line drawing algorithm.
    */
   const clockwork::graphics::LineAlgorithm::Identifier& getLineAlgorithm() const;
   /**
    * Set the viewer's line drawing algorithm.
    * @param identifier the algorithm's identifier.
    */
   void setLineAlgorithm(const clockwork::graphics::LineAlgorithm::Identifier& identifier);
   /**
    * Return the viewer's primitive mode.
    */
   const clockwork::graphics::PrimitiveMode::Identifier& getPrimitiveMode() const;
   /**
    * Set the viewer's primitive mode.
    * @param identifier the primitive mode's identifier.
    */
   void setPrimitiveMode(const clockwork::graphics::PrimitiveMode::Identifier& identifier);
protected:
   /**
    * Instantiate a named viewer.
    * @param name the viewer's name.
    */
   explicit Viewer(const QString& name);
private:
   /**
    * The view transformation matrix.
    */
   clockwork::Matrix4 _viewTransform;
   /**
    * When true, this signals that the view transformation matrix needs to be updated.
    */
   bool _doViewTransformUpdate;
   /**
    * The projection transformation matrix.
    */
   clockwork::Matrix4 _projectionTransform;
   /**
    * When true, this signals that the view transformation matrix needs to be updated.
    */
   bool _doProjectionTransformUpdate;
   /**
    * The view-projection transformation matrix.
    */
   clockwork::Matrix4 _viewProjectionTransform;
   /**
    * When true, this signals that the view-projection transformation matrix needs to be updated.
    */
   bool _doViewProjectionTransformUpdate;
   /**
    * The viewer's renderer type.
    */
   clockwork::graphics::RenderAlgorithm::Identifier _renderAlgorithmIdentifier;
   /**
    * The viewer's projection type.
    */
   clockwork::graphics::Projection::Type _projectionType;
   /**
    * The viewer's view viewport.
    */
   clockwork::graphics::Viewport _viewport;
   /**
    * The viewer's view frustum.
    */
   clockwork::graphics::Frustum _frustum;
   /**
    * The viewer's post-processing image filter type.
    */
   clockwork::graphics::ImageFilter::Type _imageFilterType;
   /**
    * The viewer's texture filter type.
    */
   clockwork::graphics::TextureFilter::Type _textureFilterType;
   /**
    * The viewer's line drawing algorithm.
    */
   clockwork::graphics::LineAlgorithm::Identifier _lineAlgorithm;
   /**
    * The viewer's primitive mode.
    */
   clockwork::graphics::PrimitiveMode::Identifier _primitiveMode;
};

} // namespace scene
} // namespace clockwork
