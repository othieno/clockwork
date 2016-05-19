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
#ifndef CLOCKWORK_VECTOR3_HH
#define CLOCKWORK_VECTOR3_HH

#include <QString>


namespace clockwork {

struct Vector3
{
   /**
    * The point's I component.
    */
   double i;
   /**
    * The point's J component.
    */
   double j;
   /**
    * The point's K component.
    */
   double k;
   /**
    * Instantiate a vector from a set of I, J and K components.
    * @param i the point's I component.
    * @param j the point's J component.
    * @param k the point's K component.
    */
   Vector3(const double& i = 0, const double& j = 0, const double& k = 0);
   /**
    * Return the vector's magnitude.
    */
   double getMagnitude() const;
   /**
    * Normalise a vector.
    * @param v the vector to normalise.
    */
   static Vector3 normalise(const Vector3& v);
   /**
    * Return the cross product of two vectors.
    * @param v1 the first vector.
    * @param v2 the second vector.
    */
   static Vector3 cross(const Vector3& v1, const Vector3& v2);
};

QString toString(const Vector3&);

} // namespace clockwork

#endif // CLOCKWORK_VECTOR3_HH
