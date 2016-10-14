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
#include "lerp.hh"


double
clockwork::lerp(const double from, const double to, const double p) {
	return ((1.0 - p) * from) + (p * to);
}


clockwork::Point
clockwork::lerp(const Point& from, const Point& to, const double p) {
	const double pp = 1.0 - p;
	return Point(
		(pp * from.x) + (p * to.x),
		(pp * from.y) + (p * to.y)
	);
}


clockwork::Point3
clockwork::lerp(const Point3& from, const Point3& to, const double p) {
	const double pp = 1.0 - p;
	return Point3(
		(pp * from.x) + (p * to.x),
		(pp * from.y) + (p * to.y),
		(pp * from.z) + (p * to.z)
	);
}


clockwork::Point4
clockwork::lerp(const Point4& from, const Point4& to, const double p) {
	const double pp = 1.0 - p;
	return Point4(
		(pp * from.x) + (p * to.x),
		(pp * from.y) + (p * to.y),
		(pp * from.z) + (p * to.z),
		(pp * from.w) + (p * to.w)
	);
}


clockwork::Vector3
clockwork::lerp(const Vector3& from, const Vector3& to, const double p) {
	const double pp = 1.0 - p;
	return Vector3(
		(pp * from.i) + (p * to.i),
		(pp * from.j) + (p * to.j),
		(pp * from.k) + (p * to.k)
	);
}


clockwork::math::Vector4d
clockwork::lerp(const math::Vector4d& from, const math::Vector4d& to, const double p) {
	const double pp = 1.0 - p;
	return math::Vector4d(
		(pp * from.i) + (p * to.i),
		(pp * from.j) + (p * to.j),
		(pp * from.k) + (p * to.k),
		(pp * from.l) + (p * to.l)
	);
}


clockwork::Color
clockwork::lerp(const Color& from, const Color& to, const double p) {
	const double pp = 1.0 - p;
	return Color(
		(pp * from.red) + (p * to.red),
		(pp * from.green) + (p * to.green),
		(pp * from.blue) + (p * to.blue),
		(pp * from.alpha) + (p * to.alpha)
	);
}
