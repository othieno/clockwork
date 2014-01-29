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
#include "render.parameters.hh"
#include "scene.viewer.hh"
#include "rigid.body.hh"


namespace clockwork {
namespace graphics {

/**
 * A task to render a 3D model.
 */
class RenderTask : public clockwork::concurrency::Task
{
public:
   /**
    * Instantiate a render task with given parameters, the current scene viewer,
    * and a body containing a 3D model to render as well as transformation matrices.
    * @param parameters the parameters that will be passed to the render function.
    * @param viewer the current scene viewer.
    * @param body the rigid body containing the 3D model to render.
    */
   RenderTask
   (
      const RenderParameters& parameters,
      const clockwork::scene::Viewer& viewer,
      const clockwork::physics::RigidBody& body
   );
   /**
    * @see clockwork::concurrency::Task::onRun.
    */
   virtual void onRun() override final;
private:
   /**
    * The render function's parameters.
    */
   const RenderParameters& _parameters;
   /**
    * The rigid body containing the 3D model to render. It also contains
    * matrix transformations that will be applied to the 3D model's vertices.
    */
   const clockwork::physics::RigidBody& _body;
   /**
    * The scene viewer.
    */
   const clockwork::scene::Viewer& _viewer;
};

} // namespace graphics
} // namespace clockwork
