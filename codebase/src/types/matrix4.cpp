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
#include "matrix4.hh"
#include <cmath>

using clockwork::Matrix4;


Matrix4::Matrix4(const std::array<double, 16>& input) :
_data(input)
{}


Matrix4::Matrix4() :
clockwork::Matrix4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
{}


void
Matrix4::fill(const double& value)
{
   _data.fill(value);
}


const std::array<double, 16>&
Matrix4::getData() const
{
   return _data;
}


double
Matrix4::get(const unsigned int& i, const unsigned int& j) const
{
   // Since i and j are unsigned, they're guaranteed to be greater than or equal to zero.
   return (i < 4 && j < 4) ? _data[(i * 4) + j] : 0;
}


void
Matrix4::set(const unsigned int& i, const unsigned int& j, const double& value)
{
   if (i < 4 && j < 4)
      _data[(i * 4) + j] = value;
}


Matrix4
Matrix4::operator*(const Matrix4& that) const
{
   std::array<double, 16> newdata;
   for (unsigned int i = 0; i < 4; ++i)
   {
      unsigned int offset = i * 4;
      for (unsigned int j = 0; j < 4; ++j)
      {
         newdata[offset] = 0;
         for (unsigned int k = 0; k < 4; ++k)
            newdata[offset] += get(i, k) * that.get(k, j);

         ++offset;
      }
   }
   return Matrix4(newdata);
}


clockwork::Point3
Matrix4::operator*(const clockwork::Point3& p) const
{
   clockwork::Point4 hp = *this * clockwork::Point4(p.x, p.y, p.z, 1);
   return clockwork::Point3
   (
      hp.x / hp.w,
      hp.y / hp.w,
      hp.z / hp.w
   );
}


clockwork::Point4
Matrix4::operator*(const clockwork::Point4& p) const
{
   const std::array<double, 4> olddata = {p.x, p.y, p.z, p.w};
   std::array<double, 4> newdata = {0, 0, 0, 0};

   for (unsigned int i = 0; i < 4; ++i)
   {
      for (unsigned int j = 0; j < 4; ++j)
         newdata[i] += get(i, j) * olddata[j];
   }
   return clockwork::Point4(newdata[0], newdata[1], newdata[2], newdata[3]);
}


clockwork::Vector3
Matrix4::operator*(const clockwork::Vector3& v) const
{
   clockwork::Point3 p = (*this) * clockwork::Point3(v.i, v.j, v.k);
   return clockwork::Vector3(p.x, p.y, p.z);
}


Matrix4
Matrix4::zeros()
{
   return Matrix4({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
}


Matrix4
Matrix4::ones()
{
   return Matrix4({1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0});
}


Matrix4
Matrix4::translate(const double& x, const double& y, const double& z)
{
   return Matrix4
   ({
      1, 0, 0, x,
      0, 1, 0, y,
      0, 0, 1, z,
      0, 0, 0, 1
   });
}


// TODO Use quaternions.
Matrix4
Matrix4::rotate(const double& x, const double& y, const double& z)
{
   const auto radians = [](const double degrees)
   {
      return degrees * 0.01745329251;
   };

   const double alpha = radians(x);
   const double gamma = radians(y);
   const double theta = radians(z);

   const double cx = cos(alpha);
   const double cy = cos(gamma);
   const double cz = cos(theta);
   const double sx = sin(alpha);
   const double sy = sin(gamma);
   const double sz = sin(theta);

   const auto Rx = Matrix4
   ({
      1.0, 0.0, 0.0, 0.0,
      0.0,  cx, -sx, 0.0,
      0.0,  sx,  cx, 0.0,
      0.0, 0.0, 0.0, 1.0
   });
   const auto Ry = Matrix4
   ({
       cy, 0.0,  sy, 0.0,
      0.0, 1.0, 0.0, 0.0,
      -sy, 0.0,  cy, 0.0,
      0.0, 0.0, 0.0, 1.0
   });
   const auto Rz = Matrix4
   ({
       cz, -sz, 0.0, 0.0,
       sz,  cz, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0
   });
   return Rx * Rz * Ry;
}


Matrix4
Matrix4::scale(const double& x, const double& y, const double& z)
{
   return Matrix4
   ({
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1
   });
}


Matrix4
Matrix4::transpose(const Matrix4& in)
{
   const auto& olddata = in._data;
   std::array<double, 16> newdata;

   for (unsigned int i = 0; i < 4; ++i)
   {
      for (unsigned int j = 0; j < 4; ++j)
      {
         const unsigned int offset = (i * 4) + j;
         const unsigned int oldOffset = (j * 4) + i;

         newdata[offset] = olddata[oldOffset];
      }
   }
   return Matrix4(newdata);
}


Matrix4
Matrix4::inverse(const Matrix4& m)
{
   const double
   &m00 = m.get(0, 0), &m01 = m.get(0, 1), &m02 = m.get(0, 2), &m03 = m.get(0, 3),
   &m10 = m.get(1, 0), &m11 = m.get(1, 1), &m12 = m.get(1, 2), &m13 = m.get(1, 3),
   &m20 = m.get(2, 0), &m21 = m.get(2, 1), &m22 = m.get(2, 2), &m23 = m.get(2, 3),
   &m30 = m.get(3, 0), &m31 = m.get(3, 1), &m32 = m.get(3, 2), &m33 = m.get(3, 3);

   // TODO Use SSE intrinsics.
   const auto s0 = m00 * m11 - m10 * m01;
   const auto s1 = m00 * m12 - m10 * m02;
   const auto s2 = m00 * m13 - m10 * m03;
   const auto s3 = m01 * m12 - m11 * m02;
   const auto s4 = m01 * m13 - m11 * m03;
   const auto s5 = m02 * m13 - m12 * m03;

   const auto c5 = m22 * m33 - m32 * m23;
   const auto c4 = m21 * m33 - m31 * m23;
   const auto c3 = m21 * m32 - m31 * m22;
   const auto c2 = m20 * m33 - m30 * m23;
   const auto c1 = m20 * m32 - m30 * m22;
   const auto c0 = m20 * m31 - m30 * m21;

   // Calculate the inverse determinant.
   const auto idet = 1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

   // ... and finally the inverse matrix.
   std::array<double, 16> newdata;

   newdata[0]  = ( m11 * c5 - m12 * c4 + m13 * c3) * idet;
   newdata[1]  = (-m01 * c5 + m02 * c4 - m03 * c3) * idet;
   newdata[2]  = ( m31 * s5 - m32 * s4 + m33 * s3) * idet;
   newdata[3]  = (-m21 * s5 + m22 * s4 - m23 * s3) * idet;

   newdata[4]  = (-m10 * c5 + m12 * c2 - m13 * c1) * idet;
   newdata[5]  = ( m00 * c5 - m02 * c2 + m03 * c1) * idet;
   newdata[6]  = (-m30 * s5 + m32 * s2 - m33 * s1) * idet;
   newdata[7]  = ( m20 * s5 - m22 * s2 + m23 * s1) * idet;

   newdata[8]  = ( m10 * c4 - m11 * c2 + m13 * c0) * idet;
   newdata[9]  = (-m00 * c4 + m01 * c2 - m03 * c0) * idet;
   newdata[10] = ( m30 * s4 - m31 * s2 + m33 * s0) * idet;
   newdata[11] = (-m20 * s4 + m21 * s2 - m23 * s0) * idet;

   newdata[12] = (-m10 * c3 + m11 * c1 - m12 * c0) * idet;
   newdata[13] = ( m00 * c3 - m01 * c1 + m02 * c0) * idet;
   newdata[14] = (-m30 * s3 + m31 * s1 - m32 * s0) * idet;
   newdata[15] = ( m20 * s3 - m21 * s1 + m22 * s0) * idet;

   return Matrix4(newdata);
}


Matrix4
Matrix4::model(const clockwork::Point3& t, const clockwork::Vector3& r, const clockwork::Vector3& s)
{
   return Matrix4::translate(t) * Matrix4::rotate(r) * Matrix4::scale(s);
}
