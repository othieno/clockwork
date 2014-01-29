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
#include "vertex.hh"

using clockwork::graphics::Vertex;


Vertex::Vertex(const double& x, const double& y, const double& z, const double& w) :
Point4(x, y, z, w),
color(1.0, 1.0, 1.0)
{}


Vertex::Vertex(const clockwork::Point4& p) :
Vertex(p.x, p.y, p.z, p.w)
{}


Vertex
Vertex::interpolate(const Vertex& start, const Vertex& end, const double& p)
{
   const double pp = 1.0 - p;
   Vertex output;

   output.x = (pp * start.x) + (p * end.x);
   output.y = (pp * start.y) + (p * end.y);
   output.z = (pp * start.z) + (p * end.z);

   output.normal.i = (pp * start.normal.i) + (p * end.normal.i);
   output.normal.j = (pp * start.normal.j) + (p * end.normal.j);
   output.normal.k = (pp * start.normal.k) + (p * end.normal.k);

   output.color.red   = (pp * start.color.red)   + (p * end.color.red);
   output.color.green = (pp * start.color.green) + (p * end.color.green);
   output.color.blue  = (pp * start.color.blue)  + (p * end.color.blue);
   output.color.alpha = (pp * start.color.alpha) + (p * end.color.alpha);

   output.uvmap.u = (pp * start.uvmap.u) + (p * end.uvmap.u);
   output.uvmap.v = (pp * start.uvmap.v) + (p * end.uvmap.v);

   return output;
}


bool
Vertex::operator<(const Vertex& V) const
{
   if (y < V.y)
      return true;
   else if (y > V.y)
      return false;
   else
   {
      if (x < V.x)
         return true;
      else if (x > V.x)
         return false;
      else
         return (z < V.z);
   }
};
