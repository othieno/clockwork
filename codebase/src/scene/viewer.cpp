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
#include "scene.viewer.hh"
#include "projection.factory.hh"
#include "render.parameters.factory.hh"


clockwork::scene::Viewer::Viewer(const std::string& name) :
RigidBody(name),
_renderType(clockwork::graphics::RenderParametersFactory::getUniqueInstance().getDefaultKey()),
_projectionType(clockwork::graphics::ProjectionFactory::getUniqueInstance().getDefaultKey())
{}


const clockwork::graphics::RenderParameters::Type&
clockwork::scene::Viewer::getRenderType() const
{
   return _renderType;
}


void
clockwork::scene::Viewer::setRenderType(const clockwork::graphics::RenderParameters::Type& type)
{
   _renderType = type;
}


const clockwork::graphics::Projection::Type&
clockwork::scene::Viewer::getProjectionType() const
{
   return _projectionType;
}


void
clockwork::scene::Viewer::setProjection(const clockwork::graphics::Projection::Type& type)
{
   _projectionType = type;
}


const clockwork::Matrix4&
clockwork::scene::Viewer::getViewMatrix() const
{
   return _viewMatrix;
}


void
clockwork::scene::Viewer::updateViewMatrix()
{
   std::cerr << "Implement clockwork::scene::Viewer::updateViewMatrix" << std::endl;
}


const clockwork::Matrix4&
clockwork::scene::Viewer::getProjectionMatrix() const
{
   return _projectionMatrix;
}


void
clockwork::scene::Viewer::updateProjectionMatrix()
{
   std::cerr << "Implement clockwork::scene::Viewer::updateProjectionMatrix" << std::endl;
}


const clockwork::Matrix4&
clockwork::scene::Viewer::getViewProjectionMatrix() const
{
   return _viewProjectionMatrix;
}


const clockwork::graphics::Viewport&
clockwork::scene::Viewer::getViewport() const
{
   return _viewport;
}
