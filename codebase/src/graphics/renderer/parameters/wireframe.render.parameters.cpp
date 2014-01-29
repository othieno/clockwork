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
#include "wireframe.render.parameters.hh"
#include "line.render.parameters.hh"
#include "render.parameters.factory.hh"
#include "numerical.hh"

using clockwork::graphics::WireframeRenderParameters;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;


WireframeRenderParameters::WireframeRenderParameters() :
PolygonRenderParameters(RenderParameters::Type::Wireframe)
{}


void
WireframeRenderParameters::rasterise(const RenderParameters::Uniforms& uniforms, const VertexArray& vertices) const
{
   // TODO Implement depth interpolation in Xiaolin Wu so it can be used instead of Bresenham
   static const auto drawline =
   std::bind
   (
      &LineRenderParameters::drawlineBresenham,
      static_cast<LineRenderParameters*>(RenderParametersFactory::getUniqueInstance().get(RenderParameters::Type::Line)),
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3
   );
   const auto& fop = std::bind(&WireframeRenderParameters::fragmentProgram, this, uniforms, std::placeholders::_1);
   for (auto it = vertices.begin(); it != vertices.end(); it += 3)
   {
      // Make sure we have at least 3 vertices.
      const auto& V0 = it[0];
      const auto& V1 = it[1];
      const auto& V2 = it[2];

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

      // Draw triangle outlines.
      drawline(uniforms, V0, V1);
      drawline(uniforms, V1, V2);
      drawline(uniforms, V2, V0);

      // Remember that the vertices are arranged in such a way that V0 has the smallest
      // y value and V2 has the largest.
      const auto ymin = static_cast<uint32_t>(V0.y);
      const auto ymax = static_cast<uint32_t>(V2.y);

      // Draw only the pixels inside the triangle primitive.
      for (auto y = ymin + 1; y < ymax; ++y)
      {
         // The scan-line's origin (vs) and endpoint (ve) vertices.
         auto vs = Vertex::interpolate(*A, *B, (y - A->y) / (B->y - A->y));
         vs.x    = std::round(vs.x);
         auto ve = Vertex::interpolate(*C, *B, (y - C->y) / (B->y - C->y));
         ve.x    = std::round(ve.x);

         // The color mask changes the vertex's color from its original value
         // to the background's color. This value is then applied to fragments
         // inside the triangle, leaving only the outlines visible.
         const double colorMask = 0.05;

         // Fill the scanline.
         const auto xmin = static_cast<uint32_t>(std::min(vs.x, ve.x));
         const auto xmax = static_cast<uint32_t>(std::max(vs.x, ve.x));
         const double dx = ve.x - vs.x;
         for (auto x = xmin + 1; x < xmax; ++x)
         {
            auto vi = Vertex::interpolate(vs, ve, (x - vs.x) / dx);
            vi.x = x;
            vi.y = y;
            vi.color.red   *= colorMask;
            vi.color.green *= colorMask;
            vi.color.blue  *= colorMask;
            plot(Fragment(vi), fop);
         }
      }
   }
}
