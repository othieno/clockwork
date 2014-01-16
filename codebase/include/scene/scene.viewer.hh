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
#pragma once

#include "rigid.body.hh"
#include "render.parameters.hh"
#include "projection.hh"
#include "viewport.hh"
#include "frustum.hh"


namespace clockwork {
namespace scene {

class Viewer : public clockwork::physics::RigidBody
{
Q_OBJECT
public:
	/**
	 * Return the viewer's view transformation matrix.
	 */
	const clockwork::Matrix4& getViewMatrix() const;
	/**
	 * Return the viewer's projection transformation matrix.
	 */
	const clockwork::Matrix4& getProjectionMatrix() const;
	/**
	 * Return the viewer's view-projection transformation matrix.
	 */
	const clockwork::Matrix4& getViewProjectionMatrix() const;
	/**
	 * Return the viewer's renderer type.
	 */
	const clockwork::graphics::RenderParameters::Type& getRenderType() const;
	/**
	 * Set the viewer's renderer type.
	 * @param type the renderer type to set.
	 */
	void setRenderType(const clockwork::graphics::RenderParameters::Type& type);
	/**
	 * Return the viewer's projection type.
	 */
	const clockwork::graphics::Projection::Type& getProjectionType() const;
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
	void setViewport(clockwork::graphics::Viewport& viewport);
	/**
	 * Return the viewer's view frustum.
	 */
	clockwork::graphics::Frustum& getFrustum();
	/**
	 * Set the viewer's view frustum.
	 * @param frustum the view frustum to set.
	 */
	void setFrustum(clockwork::graphics::Frustum& frustum);
protected:
	/**
	 * Instantiate a named viewer.
	 * @param name the viewer's name.
	 */
	Viewer(const std::string& name);
	/**
	 * The view transformation matrix.
	 */
	clockwork::Matrix4 _viewMatrix;
	/**
	 * The projection transformation matrix.
	 */
	clockwork::Matrix4 _projectionMatrix;
	/**
	 * The view-projection transformation matrix.
	 */
	clockwork::Matrix4 _viewProjectionMatrix;
private:
	/**
	 * The viewer's renderer type.
	 */
	clockwork::graphics::RenderParameters::Type _renderType;
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
private slots:
	/**
	 * Update the view transformation matrix.
	 */
	void updateViewMatrix();
	/**
	 * Update the projection transformation matrix.
	 */
	void updateProjectionMatrix();
};

} // namespace scene
} // namespace clockwork
