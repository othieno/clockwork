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
#pragma once

#include "point3.hh"
#include "point4.hh"
#include <array>


namespace clockwork {

class Matrix4
{
public:
	/**
	 * Instantiate a 4x4 matrix from a set of data.
	 * @param data the matrix's initial data.
	 */
	explicit Matrix4(const std::array<double, 16>& data);
	/**
	 * Instantiate a 4x4 identity matrix.
	 */
	Matrix4();
	/**
	 * Fill the matrix with a given value.
	 * @param value the value used to fill the matrix.
	 */
	void fill(const double& value);
	/**
	 * Return the matrix's raw data.
	 */
	const std::array<double, 16>& data() const;
	/**
	 * Return the element at the given coordinate.
	 * @param i the matrix's ith row.
	 * @param j the matrix's jth column.
	 */
	double get(const unsigned int& i, const unsigned int& j) const;
	/**
	 * Set the element at the given coordinate.
	 * @param i the matrix's ith row.
	 * @param j the matrix's jth column.
	 * @param value the value to set.
	 */
	void set(const unsigned int& i, const unsigned int& j, const double& value);
	/**
	 * The multiplication operator.
	 * @param rhs the right-hand side operand.
	 */
	Matrix4 operator*(const Matrix4& rhs) const;
	/**
	 * Multiply this matrix with a 3D affine point.
	 * @param p the point to multiply this matrix by.
	 */
	clockwork::Point3 operator*(const clockwork::Point3& p) const;
	/**
	 * Multiply this matrix with a 3D homogeneous point.
	 * @param p the point to multiply this matrix by.
	 */
	clockwork::Point4 operator*(const clockwork::Point4& p) const;
	/**
	 * Multiply this matrix with a 3D vector.
	 * @param v the vector to multiply this matrix by.
	 */
	clockwork::Vector3 operator*(const clockwork::Vector3& v) const;
	/**
	 * Return a 4x4 matrix filled with zeros.
	 */
	static Matrix4 zeros();
	/**
	 * Return a 4x4 matrix filled with ones.
	 */
	static Matrix4 ones();
	/**
	 * Return the translation matrix.
	 * @param Tx the translation factor on the X plane.
	 * @param Ty the translation factor on the Y plane.
	 * @param Tz the translation factor on the Z plane.
	 */
	static Matrix4 translate(const double& Tx, const double& Ty, const double& Tz);
	/**
	 * Return the translation matrix.
	 * @param T a 3D point containing translation factors for the X, Y and Z planes.
	 */
	inline static Matrix4 translate(const clockwork::Point3& t)
	{
		return Matrix4::translate(t.x, t.y, t.z);
	}
	/**
	 * Return the scaling matrix.
	 * @param Sx the scaling factor on the X plane.
	 * @param Sy the scaling factor on the Y plane.
	 * @param Sz the scaling factor on the Z plane.
	 */
	static Matrix4 scale(const double& Sx, const double& Sy, const double& Sz);
	/**
	 * Return the scaling matrix.
	 * @param S a scaling vector.
	 */
	inline static Matrix4 scale(const clockwork::Vector3& s)
	{
		return Matrix4::scale(s.i, s.j, s.k);
	}
	/**
	 * Return the transpose of a given matrix.
	 * @param matrix the matrix to transpose.
	 */
	static Matrix4 transpose(const Matrix4& matrix);
	/**
	 * Return the inverse of a given matrix.
	 * @param matrix the matrix to invert.
	 */
	static Matrix4 inverse(const Matrix4& matrix);
	/**
	 * Return the model transformation matrix of a scene object.
	 * @param position the object's position in the scene.
	 * @param rotation the object's rotation in the scene.
	 * @param scaling the object's scaling factor.
	 */
	static Matrix4 model(const Point3& position, const Point3& rotation, const Vector3& scale);
private:
	/**
	 * The raw matrix data.
	 */
	std::array<double, 16> _data;
};

} // namespace clockwork
