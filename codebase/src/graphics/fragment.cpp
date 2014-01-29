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
#include "fragment.hh"
#include <cmath>

using clockwork::graphics::Fragment;


Fragment::Fragment() :
x(0), y(0), z(0.0),
normal(),
u(0.0), v(0.0),
color(1.0, 1.0, 1.0),
stencil(0)
{}


Fragment::Fragment(const Vertex& vertex) :
x(static_cast<uint32_t>(vertex.x)),
y(static_cast<uint32_t>(vertex.y)),
z(vertex.z),
normal(vertex.normal),
u(vertex.uvmap.u),
v(vertex.uvmap.v),
color(vertex.color),
stencil(0)
{}


Fragment
Fragment::interpolate(const Fragment& start, const Fragment& end, const double& p)
{
   const auto pp = 1.0 - p;
   Fragment output;

   output.x = static_cast<uint32_t>(std::round((pp * start.x) + (p * end.x)));
   output.y = static_cast<uint32_t>(std::round((pp * start.y) + (p * end.y)));
   output.z = (pp * start.z) + (p * end.z);

   output.u = (pp * start.u) + (p * end.u);
   output.v = (pp * start.v) + (p * end.v);

   output.normal.i = (pp * start.normal.i) + (p * end.normal.i);
   output.normal.j = (pp * start.normal.j) + (p * end.normal.j);
   output.normal.k = (pp * start.normal.k) + (p * end.normal.k);

   output.color.alpha = (pp * start.color.alpha) + (p * end.color.alpha);
   output.color.red = (pp * start.color.red) + (p * end.color.red);
   output.color.green = (pp * start.color.green) + (p * end.color.green);
   output.color.blue = (pp * start.color.blue) + (p * end.color.blue);

   output.stencil = (pp * start.stencil) + (p * end.stencil);

   return output;
}
