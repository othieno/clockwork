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
#include "Vector4.hh"


using clockwork::math::Vector4;


template<>
Vector4<int>::Vector4(const Vector3& v) :
i(std::round(v.i)),
j(std::round(v.j)),
k(std::round(v.k)),
l(0) {}


template<>
Vector4<unsigned>::Vector4(const Vector3& v) :
i(std::round(v.i)),
j(std::round(v.j)),
k(std::round(v.k)),
l(0) {}


template<> int
Vector4<int>::getMagnitude() const {
	return std::round(std::sqrt((i * i) + (j * j) + (k * k) + (l * l)));
};


template<> unsigned
Vector4<unsigned>::getMagnitude() const {
	return std::round(std::sqrt((i * i) + (j * j) + (k * k) + (l * l)));
};


template<> Vector4<int>
Vector4<int>::normalize(const Vector4<int>& v) {
	Vector4<int> result(v);
	const int magnitude = v.getMagnitude();
	if (magnitude != 0) {
		const double d = double(magnitude);
		result.i = std::round(result.i / d);
		result.j = std::round(result.j / d);
		result.k = std::round(result.k / d);
		result.l = std::round(result.l / d);
	}
	return result;
};


template<> Vector4<unsigned>
Vector4<unsigned>::normalize(const Vector4<unsigned>& v) {
	Vector4<unsigned> result(v);
	const unsigned magnitude = v.getMagnitude();
	if (magnitude != 0) {
		const double d = double(magnitude);
		result.i = std::round(result.i / d);
		result.j = std::round(result.j / d);
		result.k = std::round(result.k / d);
		result.l = std::round(result.l / d);
	}
	return result;
};
