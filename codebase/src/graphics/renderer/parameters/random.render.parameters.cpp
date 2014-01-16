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


void
RandomRenderParameters::postVertexProgram(const Face& face, const Vertex&, Fragment& fragment) const
{
   // Use the face's address as an ARGB value. This allows us to have a random color for
   // each face, and all 3 fragments that belong to the face share the same color.
   // Note that 0xff000000 is OR'd to make sure the alpha channel is equal to 1.0.
   // The 8-bit left-shift is not an important step but it provides a color I like.
   fragment.color = ColorRGBA::split(static_cast<uint32_t>(0xff000000 | ((uint32_t)((uintptr_t)&face) << 8)));
}
