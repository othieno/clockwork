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
#include "normal.map.render.algorithm.hh"

using clockwork::graphics::NormalMapRenderAlgorithm;


NormalMapRenderAlgorithm::NormalMapRenderAlgorithm() :
PolygonRenderAlgorithm(RenderAlgorithm::Identifier::Normals)
{}


clockwork::graphics::Vertex
NormalMapRenderAlgorithm::vertexProgram
(
   const RenderAlgorithm::Parameters& parameters,
   const clockwork::Point3& position,
   const clockwork::Vector3& normal,
   const Texture::Coordinates& uvmap
) const
{
   Vertex output = RenderAlgorithm::vertexProgram(parameters, position, normal, uvmap);
   output.normal = clockwork::Vector3::normalise(parameters.NORMAL * normal);

   return output;
}


uint32_t
NormalMapRenderAlgorithm::fragmentProgram(const RenderAlgorithm::Parameters&, const Fragment& fragment) const
{
   return ColorRGBA
   (
      (fragment.normal.i + 1.0) * 0.5,
      (fragment.normal.j + 1.0) * 0.5,
      (fragment.normal.k + 1.0) * 0.5
   );
}
