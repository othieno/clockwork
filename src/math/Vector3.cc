/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#include "Vector3.hh"
#include <cmath>


clockwork::Vector3::Vector3(const double& ini, const double& inj, const double& ink) :
i(ini),
j(inj),
k(ink)
{}


double
clockwork::Vector3::getMagnitude() const
{
   return std::sqrt((i * i) + (j * j) + (k * k));
}


clockwork::Vector3
clockwork::Vector3::normalise(const clockwork::Vector3& v)
{
   clockwork::Vector3 output(v);

   double magnitude = v.getMagnitude();
   if (magnitude != 0)
   {
      magnitude = 1/magnitude;
      output.i *= magnitude;
      output.j *= magnitude;
      output.k *= magnitude;
   }
   return output;
}


clockwork::Vector3
clockwork::Vector3::cross(const clockwork::Vector3& v1, const clockwork::Vector3& v2)
{
   return Vector3
   (
      (v1.j * v2.k) - (v1.k * v2.j),
      (v1.k * v2.i) - (v1.i * v2.k),
      (v1.i * v2.j) - (v1.j * v2.i)
   );
}
