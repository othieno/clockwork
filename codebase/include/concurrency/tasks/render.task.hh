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
#include "model3d.hh"
#include "fragment.hh"


namespace clockwork {
namespace concurrency {

/**
 * A task to render a scene entity.
 */
class RenderTask : public Task
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
      const clockwork::graphics::RenderParameters& parameters,
      const clockwork::scene::Viewer& viewer,
      const clockwork::physics::RigidBody& body
   );
   /**
    * @see clockwork::concurrency::Task::onRun.
    */
   virtual void onRun() override final;
private:
   /**
    * The viewer's position (used for lighting calculations).
    */
   const clockwork::graphics::RenderParameters& _parameters;
   /**
    * The viewer's position (used for lighting calculations).
    */
   const clockwork::Point3& _viewpoint;
   /**
    * The rigid body's 3D model.
    */
   const clockwork::graphics::Model3D* const _model3D;
   /**
    * The viewer's viewport.
    */
   const clockwork::graphics::Viewport& _viewport;
   /**
    * The rigid body's model transformation matrix.
    */
   const clockwork::Matrix4& _MODEL;
   /**
    * The viewer's view transformation matrix.
    */
   const clockwork::Matrix4& _VIEW;
   /**
    * The viewer's projection transformation matrix.
    */
   const clockwork::Matrix4& _PROJECTION;
   /**
    * The view-projection transformation matrix.
    */
   const clockwork::Matrix4 _VIEWPROJECTION;
   /**
    * The normals transformation matrix.
    */
   const clockwork::Matrix4 _NORMAL;
   /**
    * The model-view transformation matrix.
    */
   const clockwork::Matrix4 _MODELVIEW;
   /**
    * The model-view-projection transformation matrix.
    */
   const clockwork::Matrix4 _MODELVIEWPROJECTION;
   /**
    * The viewport transformation.
    */
   const double _VIEWPORTX, _VIEWPORTY;
   /**
    * Perform polygon clipping on the fragments that make up a polygon.
    * @param fragments the fragments to clip.
    */
   void clip(std::vector<clockwork::graphics::Fragment>& fragments) const;
   /**
    * Return true if a polygon composed of the given fragments is facing the
    * viewer, false otherwise.
    * @param fragments the fragments that comprise the polygon to test.
    */
   bool isBackface(const std::array<const clockwork::graphics::Fragment*, 3>& fragments) const;
   /**
    * Return true if a polygon is occluded by another from the given viewpoint,
    * false otherwise.
    * @param fragments the fragments that comprise the polygon to test.
    */
   bool isOccluded(const std::array<const clockwork::graphics::Fragment*, 3>& fragments) const;
   /**
    * The vertex program is responsible for transforming a single vertex from
    * model space to a fragment in clip space, where it will be clipped and
    * passed onto the rasteriser.
    * @param input the vertex to transform.
    * @param output the container where the output fragment will be stored.
    */
   void vertexProgram(const clockwork::graphics::Vertex& input, clockwork::graphics::Fragment& output);
};

} // namespace concurrency
} // namespace clockwork
