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
#include "scene.viewer.hh"
#include "projection.factory.hh"
#include "render.algorithm.hh"
#include "image.filter.hh"
#include "texture.filter.hh"

using clockwork::scene::Viewer;


Viewer::Viewer(const QString& name) :
Object(name),
_doViewTransformUpdate(true),
_doProjectionTransformUpdate(true),
_doViewProjectionTransformUpdate(true),
_renderAlgorithmIdentifier(clockwork::graphics::RenderAlgorithmFactory::getInstance().getDefaultKey()),
_projectionType(clockwork::graphics::ProjectionFactory::getInstance().getDefaultKey()),
_imageFilterType(clockwork::graphics::ImageFilterFactory::getInstance().getDefaultKey()),
_textureFilterType(clockwork::graphics::TextureFilterFactory::getInstance().getDefaultKey()),
_lineAlgorithm(clockwork::graphics::LineAlgorithmFactory::getInstance().getDefaultKey()),
_primitiveMode(clockwork::graphics::PrimitiveModeFactory::getInstance().getDefaultKey())
{}


const clockwork::graphics::RenderAlgorithm::Identifier&
Viewer::getRenderAlgorithm() const
{
   return _renderAlgorithmIdentifier;
}


void
Viewer::setRenderAlgorithm(const clockwork::graphics::RenderAlgorithm::Identifier& identifier)
{
   _renderAlgorithmIdentifier = identifier;
}


const clockwork::graphics::Projection::Type&
Viewer::getProjection() const
{
   return _projectionType;
}


void
Viewer::setProjection(const clockwork::graphics::Projection::Type& type)
{
   _projectionType = type;
}


const clockwork::Matrix4&
Viewer::getViewTransform()
{
   if (_doViewTransformUpdate)
   {
      //TODO Calculate view transform.
      _doViewProjectionTransformUpdate = true;
      _doViewTransformUpdate = false;
   }
   return _viewTransform;
}


const clockwork::Matrix4&
Viewer::getProjectionTransform()
{
   if (_doProjectionTransformUpdate)
   {
      //TODO Calculate projection transform.
      _doViewProjectionTransformUpdate = true;
      _doProjectionTransformUpdate = false;
   }
   return _projectionTransform;
}


const clockwork::Matrix4&
Viewer::getViewProjectionTransform()
{
   if (_doViewProjectionTransformUpdate)
   {
      _viewProjectionTransform = _projectionTransform * _viewTransform;
      _doViewProjectionTransformUpdate = false;
   }
   return _viewProjectionTransform;
}


const clockwork::graphics::Viewport&
Viewer::getViewport() const
{
   return _viewport;
}


void
Viewer::setViewport(const clockwork::graphics::Viewport& viewport)
{
   _viewport = viewport;
}


void
Viewer::setViewport(const float& x, const float& y, const float& w, const float& h, const float& n, const float& f)
{
   _viewport.x = x;
   _viewport.y = y;
   _viewport.width = w;
   _viewport.height = h;
   _viewport.near = n;
   _viewport.far = f;
}


const clockwork::graphics::Frustum&
Viewer::getFrustum() const
{
   return _frustum;
}


void
Viewer::setFrustum(const clockwork::graphics::Frustum& frustum)
{
   _frustum = frustum;
   _doProjectionTransformUpdate = true;
}


const clockwork::graphics::ImageFilter::Type&
Viewer::getImageFilter() const
{
   return _imageFilterType;
}


void
Viewer::setImageFilter(const clockwork::graphics::ImageFilter::Type& type)
{
   _imageFilterType = type;
}


const clockwork::graphics::TextureFilter::Type&
Viewer::getTextureFilter() const
{
   return _textureFilterType;
}


void
Viewer::setTextureFilter(const clockwork::graphics::TextureFilter::Type& type)
{
   _textureFilterType = type;
}


const clockwork::graphics::LineAlgorithm::Identifier&
Viewer::getLineAlgorithm() const
{
   return _lineAlgorithm;
}


void
Viewer::setLineAlgorithm(const clockwork::graphics::LineAlgorithm::Identifier& identifier)
{
   _lineAlgorithm = identifier;
}


const clockwork::graphics::PrimitiveMode::Identifier&
Viewer::getPrimitiveMode() const
{
   return _primitiveMode;
}


void
Viewer::setPrimitiveMode(const clockwork::graphics::PrimitiveMode::Identifier& identifier)
{
   _primitiveMode = identifier;
}
