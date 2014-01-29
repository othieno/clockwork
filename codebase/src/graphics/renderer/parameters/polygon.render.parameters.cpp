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
#include "polygon.render.parameters.hh"
#include "numerical.hh"

using clockwork::graphics::PolygonRenderParameters;


PolygonRenderParameters::PolygonRenderParameters(const RenderParameters::Type& type) :
RenderParameters(type)
{}


clockwork::graphics::VertexArray&
PolygonRenderParameters::primitiveAssembly(VertexArray& input) const
{
   // If the triangle primitive is not correctly formed for the scanline algorithm,
   // then tessellate two triangle primitives that fit our needs.
   for (auto it = input.begin(); it != input.end();)
   {
      // Sort the subarray of vertices (from top to bottom, left to right, and nearest
      // to farthest) that make up the primitive.
      // Remember, std::sort processes the range [first, last).
      const auto& subArrayBegin = it;
      const auto& nextSubArrayBegin = it + 3;
      std::sort(subArrayBegin, nextSubArrayBegin);

      // Tessellate the primitive, if need be.
      const auto& V0 = it[0];
      const auto& V1 = it[1];
      const auto& V2 = it[2];

      const auto shouldTessellate = !clockwork::fequal(V0.y, V1.y) && !clockwork::fequal(V1.y, V2.y);
      if (shouldTessellate)
      {
         // Interpolate a new vertex.
         auto Vi = Vertex::interpolate(V0, V2, (V1.y - V0.y) / (V2.y - V0.y));
         Vi.y = V1.y;

         // Create two new primitives from four vertices. The vertices {V0, V1, V2}
         // become {V0, V1, Vi, V1, Vi, V2} and since the list is considered a triangle
         // primitive, this means we have the triangles {V0, V1, Vi} and {V1, Vi, V2}.
         it = input.insert(it + 2, Vi);
         it = input.insert(it + 1, V1);
         it = input.insert(it + 1, Vi);
         it = std::next(it, 2);
      }
      else
         it = nextSubArrayBegin;
   }
   return input;
}


clockwork::graphics::VertexArray&
PolygonRenderParameters::backfaceCulling(VertexArray& vertices) const
{
/* FIXME
   for (auto it = vertices.begin(); it != vertices.end();)
   {
      const auto erase_from = it;
      const clockwork::Point3& P0 = *it++;
      const clockwork::Point3& P1 = *it++;
      const clockwork::Point3& P2 = *it++;
      const auto erase_to = it;

      // If the face is not facing the viewer, remove the vertices in the range
      // [erase_from, erase_to) from the list.
      if (clockwork::Vector3::cross(P1 - P0, P2 - P1).k > 0)
         it = vertices.erase(erase_from, erase_to);
   }
*/
   return vertices;
}


clockwork::graphics::VertexArray&
PolygonRenderParameters::clip(VertexArray& vertices) const
{
   //TODO Implement me.
   return vertices;
}


void
PolygonRenderParameters::rasterise(const RenderParameters::Uniforms& uniforms, const VertexArray& vertices) const
{
   const auto& fop = std::bind(&PolygonRenderParameters::fragmentProgram, this, uniforms, std::placeholders::_1);
   for (auto it = vertices.begin(); it != vertices.end();)
   {
      // Make sure we have at least 3 vertices.
      const auto& V0 = *it++;
      const auto& V1 = *it++;
      const auto& V2 = *it++;

      const Vertex *A, *B, *C;
      if (clockwork::fequal(V0.y, V1.y))
      {
         // Triangle type A:
         A = &V0;
         B = &V2;
         C = &V1;
      }
      else
      {
         // Triangle type B:
         A = &V1;
         B = &V0;
         C = &V2;
      }

      // Remember that the vertices are arranged in such a way that V0 has the smallest
      // y value and V2 has the largest.
      const auto ymin = static_cast<uint32_t>(V0.y);
      const auto ymax = static_cast<uint32_t>(V2.y);

      for (auto y = ymin; y <= ymax; ++y)
      {
         // The scan-line's origin (vs) and endpoint (ve) vertices.
         auto vs = Vertex::interpolate(*A, *B, (y - A->y) / (B->y - A->y));
         auto ve = Vertex::interpolate(*C, *B, (y - C->y) / (B->y - C->y));

         // Fill the scanline.
         const auto xmin = static_cast<uint32_t>(std::round(std::min(vs.x, ve.x)));
         const auto xmax = static_cast<uint32_t>(std::round(std::max(vs.x, ve.x)));
         for (auto x = xmin; x <= xmax; ++x)
         {
            auto vi = Vertex::interpolate(vs, ve, (x - vs.x) / (ve.x - vs.x));
            vi.x = x;
            vi.y = y;
            plot(Fragment(vi), fop);
         }
      }
   }
}
