/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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
#include "point.render.algorithm.hh"
#include <algorithm>

using clockwork::graphics::PointRenderAlgorithm;


PointRenderAlgorithm::PointRenderAlgorithm() :
RenderAlgorithm(RenderAlgorithm::Identifier::Point)
{}


clockwork::graphics::VertexArray&
PointRenderAlgorithm::primitiveAssembly(const clockwork::graphics::PrimitiveMode&, VertexArray& input) const
{
   return input;
}


clockwork::graphics::VertexArray&
PointRenderAlgorithm::clip(VertexArray& vertices) const
{
   // Use a normalised 2D viewing volume: [-1, 1] x [-1, 1].
   const double xmax =  1.0;
   const double xmin = -xmax;
   const double ymax =  1.0;
   const double ymin = -ymax;

   const auto& begin = vertices.begin();
   const auto& end   = vertices.end();
   const auto& out   = [&xmin, &xmax, &ymin, &ymax](const clockwork::graphics::Vertex& v)
   {
      return v.x < xmin || v.x > xmax || v.y < ymin || v.y > ymax;
   };

   // Remove vertices that are out of the clipping window.
   vertices.erase(std::remove_if(begin, end, out), end);
   return vertices;
}


void
PointRenderAlgorithm::rasterise(const RenderAlgorithm::Parameters& parameters, const VertexArray& vertices) const
{
   const auto& fop = std::bind(&PointRenderAlgorithm::fragmentProgram, this, parameters, std::placeholders::_1);
   for (const auto& vertex : vertices)
   {
      // Create a fragment from the vertex.
      Fragment fragment(vertex);

      // Write the fragment to the framebuffer.
      plot(fragment, fop);
   }
}
