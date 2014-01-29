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
#include "services.hh"

using clockwork::graphics::RenderTask;


RenderTask::RenderTask
(
   const RenderParameters& parameters,
   const clockwork::scene::Viewer& viewer,
   const clockwork::physics::RigidBody& body
) :
_parameters(parameters),
_body(body),
_viewer(viewer)
{}


void
RenderTask::onRun()
{
   const auto* model3d = _body.getModel3D();
   if (model3d != nullptr && !model3d->isEmpty())
   {
      VertexArray vertices;
      const RenderParameters::Uniforms uniforms(_body, _viewer);

      // Apply the vertex program to each position, normal and mapping coordinate attribute,
      // then store the resulting vertex.
      const auto& positions = model3d->getVertexPositions();
      for (const auto& face : model3d->getFaces())
      {
         const auto& indices = face.getIndices();
         const auto& normals = face.getNormals();
         const auto& uvmaps  = face.getTextureMappingCoordinates();

         for (unsigned int i = 0; i < 3; ++i)
         {
            const auto& index = indices[i];
            const auto& position = positions[index];
            const auto& normal = normals[i];
            const auto& uvmap = uvmaps[i];

            vertices.push_back(_parameters.vertexProgram(uniforms, position, normal, uvmap));
         }
      }

      // Create primitives and apply the geometry program to the said primitives. If there is
      // more than one vertex, continue down the pipeline.
      if (!_parameters.geometryProgram(uniforms, _parameters.primitiveAssembly(vertices)).empty())
      {
         // Remove hidden surfaces.
         _parameters.backfaceCulling(vertices);
         _parameters.occlusionCulling(vertices);

         // Clip vertices that are not visible on the screen.
         _parameters.clip(vertices);

         // Perform perspective-divide on the visible vertices. This will convert vertex
         // positions from clipping coordinate space to normalised device coordinate space.
         for (auto& v : vertices)
         {
            v.x /= v.w;
            v.y /= v.w;
            v.z /= v.w;
            v.w  = 1.0;
         }

         // Perform the viewport transform. This will convert vertex positions from normalised
         // device coordinate space to window space.
         const auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();

         const auto& viewport = _viewer.getViewport();
         const auto& vpw = 0.5 * viewport.width * framebuffer.getWidth();
         const auto& vph = 0.5 * viewport.height * framebuffer.getHeight();

         for (auto& v : vertices)
         {
            v.x = std::round((vpw * v.x) + viewport.x + vpw);
            v.y = std::round((vph * v.y) + viewport.y + vph);
            v.z = (((viewport.far - viewport.near) * v.z) + viewport.far + viewport.near) * 0.5;
         }

         // Draw the primitives.
         _parameters.rasterise(uniforms, vertices);
      }
   }
}
