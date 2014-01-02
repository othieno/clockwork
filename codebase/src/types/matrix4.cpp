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
clockwork::Matrix4::operator*(const clockwork::Matrix4& rhs) const
{
	std::array<double, 16> newdata;
	for (unsigned int i = 0; i < 4; ++i)
	{
		const auto offset = i * 4;
		for (int j = 0; j < 4; ++j)
		{
			newdata[offset] = 0;
			for (unsigned int k = 0; k < 4; ++k)
				newdata[offset] += get(i, k) * rhs.get(k, j);
		}
	}
	return Matrix4(newdata);
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
clockwork::Matrix4::model(const Point3&, const Point3&, const Point3&)
{
	//FIXME The model matrix isn't the identity, obviously...
	return clockwork::Matrix4();
}
