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
#include "random.render.parameters.hh"

using clockwork::graphics::RandomRenderParameters;


RandomRenderParameters::RandomRenderParameters() :
PolygonRenderParameters(RenderParameters::Type::Random)
{}


clockwork::graphics::VertexArray&
RandomRenderParameters::geometryProgram(const RenderParameters::Uniforms&, VertexArray& vertices) const
{
   for (auto it = vertices.begin(); it != vertices.end();)
   {
      auto& V0 = *it++;
      auto& V1 = *it++;
      auto& V2 = *it++;

      // Use the first vertex's address as an ARGB value. The memory address allows
      // us to obtain a sufficiently random number that can be split into a ColorRGBA.
      // Note that 0xff000000 is OR'd to make sure the alpha channel is equal to 1.0.
      // The 8-bit left-shift is irrelevant, but provides a color I like.
      const auto color = ColorRGBA::split(static_cast<uint32_t>(0xff000000 | ((uint32_t)((uintptr_t)&V0) << 8)));

      V0.color = color;
      V1.color = color;
      V2.color = color;
   }
   return vertices;
}
