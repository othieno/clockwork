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
#include "matrix4.hh"


clockwork::Matrix4::Matrix4(const std::array<double, 16>& input) :
_data(input)
{}


clockwork::Matrix4::Matrix4() :
clockwork::Matrix4({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
{}


void
clockwork::Matrix4::fill(const double& value)
{
	_data.fill(value);
}


const std::array<double, 16>&
clockwork::Matrix4::data() const
{
	return _data;
}


double
clockwork::Matrix4::get(const unsigned int& i, const unsigned int& j) const
{
	// Since i and j are unsigned, they're guaranteed to be greater than or equal to zero.
	return (i < 4 && j < 4) ? _data[(i * 4) + j] : 0;
}


void
clockwork::Matrix4::set(const unsigned int& i, const unsigned int& j, const double& value)
{
	if (i < 4 && j < 4)
		_data[(i * 4) + j] = value;
}


clockwork::Matrix4
clockwork::Matrix4::operator*(const clockwork::Matrix4& that) const
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
clockwork::Matrix4::operator*(const clockwork::Point3& p) const
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
clockwork::Matrix4::operator*(const clockwork::Point4& p) const
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
clockwork::Matrix4::operator*(const clockwork::Vector3& v) const
{
	clockwork::Point3 p = *this * clockwork::Point3(v.i, v.j, v.k);
	return clockwork::Vector3
	(
		p.x,
		p.y,
		p.z
	);
}


clockwork::Matrix4
clockwork::Matrix4::zeros()
{
	return clockwork::Matrix4
	({
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	});
}


clockwork::Matrix4
clockwork::Matrix4::ones()
{
	return clockwork::Matrix4
	({
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1
	});
}


clockwork::Matrix4
clockwork::Matrix4::translate(const double& x, const double& y, const double& z)
{
	return clockwork::Matrix4
	({
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	});
}


clockwork::Matrix4
clockwork::Matrix4::scale(const double& x, const double& y, const double& z)
{
	return clockwork::Matrix4
	({
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	});
}


clockwork::Matrix4
clockwork::Matrix4::transpose(const clockwork::Matrix4& in)
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


clockwork::Matrix4
clockwork::Matrix4::inverse(const clockwork::Matrix4& in)
{
	//TODO This function can be optimised...
	const auto s0 = in.get(0, 0) * in.get(1, 1) - in.get(1, 0) * in.get(0, 1);
	const auto s1 = in.get(0, 0) * in.get(1, 2) - in.get(1, 0) * in.get(0, 2);
	const auto s2 = in.get(0, 0) * in.get(1, 3) - in.get(1, 0) * in.get(0, 3);
	const auto s3 = in.get(0, 1) * in.get(1, 2) - in.get(1, 1) * in.get(0, 2);
	const auto s4 = in.get(0, 1) * in.get(1, 3) - in.get(1, 1) * in.get(0, 3);
	const auto s5 = in.get(0, 2) * in.get(1, 3) - in.get(1, 2) * in.get(0, 3);

	const auto c5 = in.get(2, 2) * in.get(3, 3) - in.get(3, 2) * in.get(2, 3);
	const auto c4 = in.get(2, 1) * in.get(3, 3) - in.get(3, 1) * in.get(2, 3);
	const auto c3 = in.get(2, 1) * in.get(3, 2) - in.get(3, 1) * in.get(2, 2);
	const auto c2 = in.get(2, 0) * in.get(3, 3) - in.get(3, 0) * in.get(2, 3);
	const auto c1 = in.get(2, 0) * in.get(3, 2) - in.get(3, 0) * in.get(2, 2);
	const auto c0 = in.get(2, 0) * in.get(3, 1) - in.get(3, 0) * in.get(2, 1);

	// Calculate the inverse determinant.
	const auto idet = 1.0 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

	std::array<double, 16> newdata;

	newdata[0]  = ( in.get(1, 1) * c5 - in.get(1, 2) * c4 + in.get(1, 3) * c3) * idet;
	newdata[1]  = (-in.get(0, 1) * c5 + in.get(0, 2) * c4 - in.get(0, 3) * c3) * idet;
	newdata[2]  = ( in.get(3, 1) * s5 - in.get(3, 2) * s4 + in.get(3, 3) * s3) * idet;
	newdata[3]  = (-in.get(2, 1) * s5 + in.get(2, 2) * s4 - in.get(2, 3) * s3) * idet;

	newdata[4]  = (-in.get(1, 0) * c5 + in.get(1, 2) * c2 - in.get(1, 3) * c1) * idet;
	newdata[5]  = ( in.get(0, 0) * c5 - in.get(0, 2) * c2 + in.get(0, 3) * c1) * idet;
	newdata[6]  = (-in.get(3, 0) * s5 + in.get(3, 2) * s2 - in.get(3, 3) * s1) * idet;
	newdata[7]  = ( in.get(2, 0) * s5 - in.get(2, 2) * s2 + in.get(2, 3) * s1) * idet;

	newdata[8]  = ( in.get(1, 0) * c4 - in.get(1, 1) * c2 + in.get(1, 3) * c0) * idet;
	newdata[9]  = (-in.get(0, 0) * c4 + in.get(0, 1) * c2 - in.get(0, 3) * c0) * idet;
	newdata[10] = ( in.get(3, 0) * s4 - in.get(3, 1) * s2 + in.get(3, 3) * s0) * idet;
	newdata[11] = (-in.get(2, 0) * s4 + in.get(2, 1) * s2 - in.get(2, 3) * s0) * idet;

	newdata[12] = (-in.get(1, 0) * c3 + in.get(1, 1) * c1 - in.get(1, 2) * c0) * idet;
	newdata[13] = ( in.get(0, 0) * c3 - in.get(0, 1) * c1 + in.get(0, 2) * c0) * idet;
	newdata[14] = (-in.get(3, 0) * s3 + in.get(3, 1) * s1 - in.get(3, 2) * s0) * idet;
	newdata[15] = ( in.get(2, 0) * s3 - in.get(2, 1) * s1 + in.get(2, 2) * s0) * idet;

	return clockwork::Matrix4(newdata);
}


clockwork::Matrix4
clockwork::Matrix4::model(const Point3&, const Point3&, const Point3&)
{
	//FIXME The model matrix isn't the identity, obviously...
	return clockwork::Matrix4();
}
