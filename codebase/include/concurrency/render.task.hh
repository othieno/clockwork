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

#include "task.hh"
#include "mesh.hh"
#include "material.hh"
#include "rigid.body.hh"
#include "viewport.hh"
#include "renderer.hh"
#include "scene.viewer.hh"
#include "fragment.hh"
#include "framebuffer.hh"


namespace clockwork {
namespace concurrency {

/**
 * A task to render a scene entity.
 */
class RenderTask : public clockwork::concurrency::Task
{
public:
	/**
	 * Instantiate a RenderTask that will apply a render function
	 * to a given rigid body, based on a scene viewer's position.
	 * @param renderer the renderer containing the render function.
	 * @param body the rigid body that will be rendered.
	 * @param viewer the scene viewer.
	 */
	RenderTask
	(
		const clockwork::graphics::Renderer& renderer,
		const clockwork::physics::RigidBody& body,
		const clockwork::scene::Viewer& viewer
	);
	/**
	 * @see clockwork::concurrency::Task::onRun.
	 */
	virtual void onRun() override final;
protected:
	/**
	 * The vertex program is responsible for transforming a single vertex from
	 * model space to a fragment in clip space, where it will be clipped and
	 * passed onto the rasteriser.
	 * @param input the vertex to transform.
	 * @param output the container where the output fragment will be stored.
	 */
	virtual void vertexProgram
	(
		const clockwork::graphics::Vertex& input,
		clockwork::graphics::Fragment& output
	);
	/**
	 * The rasterisation operation converts a triangular polygonal face into
	 * a raster image (a rectangular grid of pixels).
	 */
	virtual void rasterise(const std::array<clockwork::graphics::Fragment*, 3>& fragments);
	/**
	 * TODO Make pure virtual.
	 * The primitive assembly operation creates a point, line or polygon primitive from
	 * fragments. In the case of polygon primitives, missing fragments in the hollows of
	 * the polygon triangles are interpolated. These primitives are then passed to the
	 * fragment program which determines their color.
	 * @param fragments a set of 3 fragments that will create a primitive.
	 */
	virtual void primitiveAssembly(const std::array<clockwork::graphics::Fragment*, 3>& fragments);
	/**
	 * The fragment program calculates a color value from a given fragment's attributes.
	 * @param fragment the fragment from which to calculate a color value.
	 */
	virtual uint32_t fragmentProgram(const clockwork::graphics::Fragment& fragment);
private:
	/**
	 * The framebuffer.
	 */
	static clockwork::graphics::Framebuffer& FRAMEBUFFER;
	/**
	 * The renderer containing the render function that will be
	 * applied to the rigid body.
	 */
	const clockwork::graphics::Renderer& _renderer;
	/**
	 * The viewer's position. This is used for lighting calculations.
	 */
	const clockwork::Point3& _viewpoint;
	/**
	 * The viewport transformation.
	 */
	const double _VIEWPORTX, _VIEWPORTY;
	/**
	 * The scene object's model transformation matrix.
	 */
	const clockwork::Matrix4& _MODEL;
	/**
	 * The viewer's view transformation matrix.
	 */
	const clockwork::Matrix4& _VIEW;
	/**
	 * The model-view transformation matrix.
	 */
	clockwork::Matrix4 _MODELVIEW;
	/**
	 * The normals transformation matrix.
	 */
	clockwork::Matrix4 _NORMAL;
	/**
	 * The viewer's projection transformation matrix.
	 */
	const clockwork::Matrix4& _PROJECTION;
	/**
	 * The view-projection transformation matrix.
	 */
	clockwork::Matrix4 _VIEWPROJECTION;
	/**
	 * The model-view-projection transformation matrix.
	 */
	clockwork::Matrix4 _MODELVIEWPROJECTION;
	/**
	 * The rigid body's 3D model.
	 */
	const clockwork::graphics::Model3D* const _model3D;
};

} // namespace concurrency
} // namespace clockwork
