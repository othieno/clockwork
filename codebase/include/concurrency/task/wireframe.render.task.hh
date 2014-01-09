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

#include "render.task.hh"


namespace clockwork {
namespace concurrency {

/**
 * A wireframe renderer's render task.
 */
class WireframeRenderTask : public clockwork::concurrency::RenderTask
{
public:
	/**
	 * Instantiate the task with a given rigid body and scene viewer, that uses
	 * a specified line drawing function when rendering lines between two fragments.
	 * @param body the rigid body containing the 3D model and transformation matrices.
	 * @param viewer the scene's point of view.
	 * @param drawline a function that draws a line between two fragments.
	 */
	WireframeRenderTask
	(
		const clockwork::physics::RigidBody& body,
		const clockwork::scene::Viewer& viewer,
		const std::function<void(const clockwork::graphics::Fragment&, const clockwork::graphics::Fragment&)> drawline
	);
	/**
	 * @see RenderTask::primitiveAssembly.
	 */
	virtual void primitiveAssembly(const std::array<clockwork::graphics::Fragment*, 3>& triangle) override final;
private:
	/**
	 * The line drawing function.
	 */
	const std::function<void(const clockwork::graphics::Fragment&, const clockwork::graphics::Fragment&)> _drawline;
};

} // namespace concurrency
} // namespace clockwork
