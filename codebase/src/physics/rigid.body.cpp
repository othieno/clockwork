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
#include "rigid.body.hh"
#include "render.task.hh"
#include "services.hh"


clockwork::physics::RigidBody::RigidBody
(
	const std::string& name,
	const clockwork::graphics::Model3D* model3D
) :
Object(name),
_model3D(model3D)
{}


void
clockwork::physics::RigidBody::render
(
	const clockwork::graphics::Renderer& renderer,
	const clockwork::scene::Viewer& viewer
) const
{
	if (!isPruned() && _model3D != nullptr)
		clockwork::system::Services::Concurrency.submitTask(renderer.createRenderTask(*this, viewer));
}


const clockwork::graphics::Model3D*
clockwork::physics::RigidBody::getModel3D() const
{
	return _model3D;
}


void
clockwork::physics::RigidBody::setModel3D(const clockwork::graphics::Model3D* model3D)
{
	_model3D = model3D;
}


std::string
clockwork::physics::RigidBody::toString(const clockwork::physics::RigidBody&)
{
	return "Implement clockwork::physics::RigidBody::toString";
}
