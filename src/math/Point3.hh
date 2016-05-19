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
#ifndef CLOCKWORK_POINT3_HH
#define CLOCKWORK_POINT3_HH

#include "Vector3.hh"


namespace clockwork {

struct Point3
{
   /**
    * The point's X, Y and Z coordinates.
    */
   double x, y, z;
   /**
    * Instantiate a point from a set of X, Y and Z coordinates.
    * @param x the point's X coordinate.
    * @param y the point's Y coordinate.
    * @param z the point's Z coordinate.
    */
   Point3(const double& x = 0, const double& y = 0, const double& z = 0);
   /**
    * Return the difference between this point and another.
    * @param p the point that's being substracted from this.
    */
   clockwork::Vector3 operator-(const Point3& p) const;
   /**
    * Multiply a 3D point by -1 (minus one) and return the result.
    * @param input the point to multiply.
    */
   static Point3 negative(const Point3& input);
};

QString toString(const Point3&);

} // namespace clockwork

#endif // CLOCKWORK_POINT3_HH
