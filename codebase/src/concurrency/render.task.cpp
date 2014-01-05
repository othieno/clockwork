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
#include "render.task.hh"
#include "renderer.factory.hh"


clockwork::concurrency::RenderTask::RenderTask
(
	const clockwork::graphics::Renderer& renderer,
	const clockwork::physics::RigidBody& body,
	const clockwork::scene::Viewer& viewer
) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::GraphicsRenderTask)),
_renderer(renderer),
_viewpoint(viewer.getPosition()),
_viewport(viewer.getViewport()),
_MODEL(body.getModelMatrix()),
_VIEW(viewer.getViewMatrix()),
_PROJECTION(viewer.getProjectionMatrix()),
_mesh(body.getMesh()),
_material(body.getMaterial())
{}


void
clockwork::concurrency::RenderTask::onRun()
{
	_MODELVIEW = _VIEW * _MODEL;
	_NORMAL = clockwork::Matrix4::transpose(clockwork::Matrix4::inverse(_MODELVIEW));
	_VIEWPROJECTION = _PROJECTION * _VIEW;
	_MODELVIEWPROJECTION = _VIEWPROJECTION * _MODEL;
}
