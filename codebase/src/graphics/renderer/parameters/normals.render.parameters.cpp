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
#include "normals.render.parameters.hh"

using clockwork::graphics::NormalsRenderParameters;


NormalsRenderParameters::NormalsRenderParameters() :
PolygonRenderParameters(RenderParameters::Type::Normals)
{}


clockwork::graphics::Vertex
NormalsRenderParameters::vertexProgram
(
   const RenderParameters::Uniforms& uniforms,
   const clockwork::Point3& position,
   const clockwork::Vector3& normal,
   const Texture::Coordinates& uvmap
) const
{
   Vertex output = RenderParameters::vertexProgram(uniforms, position, normal, uvmap);
   output.normal = clockwork::Vector3::normalise(uniforms.NORMAL * normal);

   return output;
}


uint32_t
NormalsRenderParameters::fragmentProgram(const RenderParameters::Uniforms&, const Fragment& fragment) const
{
   return ColorRGBA
   (
      (fragment.normal.i + 1.0) * 0.5,
      (fragment.normal.j + 1.0) * 0.5,
      (fragment.normal.k + 1.0) * 0.5
   );
}
