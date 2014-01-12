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
#include "vsd.hh"


void
clockwork::graphics::vsd::clip(std::vector<clockwork::graphics::Fragment>&)
{}


bool
clockwork::graphics::vsd::isBackface(std::array<const clockwork::graphics::Fragment*, 3>& triangle)
{
	const auto& f0 = *triangle[0];
	const auto& f1 = *triangle[1];
	const auto& f2 = *triangle[2];

	const auto& p0 = clockwork::Point3(f0.x, f0.y, f0.z);
	const auto& p1 = clockwork::Point3(f1.x, f1.y, f1.z);
	const auto& p2 = clockwork::Point3(f2.x, f2.y, f2.z);

	return clockwork::Vector3::cross(p1 - p0, p2 - p1).k > 0;
}
