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
#include "Fragment.hh"
#include <cmath>

using clockwork::Fragment;


Fragment::Fragment() :
x(0),
y(0),
z(0.0),
normal(),
u(0.0),
v(0.0),
color(1.0, 1.0, 1.0),
stencil(0) {}


Fragment
Fragment::estimate(const Fragment& from, const Fragment& to, const double p) {
	const double pp = 1.0 - p;
	Fragment output;

	output.x = static_cast<std::uint32_t>(std::round((pp * from.x) + (p * to.x)));
	output.y = static_cast<std::uint32_t>(std::round((pp * from.y) + (p * to.y)));
	output.z = (pp * from.z) + (p * to.z);
	output.u = (pp * from.u) + (p * to.u);
	output.v = (pp * from.v) + (p * to.v);
	output.normal.i = (pp * from.normal.i) + (p * to.normal.i);
	output.normal.j = (pp * from.normal.j) + (p * to.normal.j);
	output.normal.k = (pp * from.normal.k) + (p * to.normal.k);
	output.color.alpha = (pp * from.color.alpha) + (p * to.color.alpha);
	output.color.red = (pp * from.color.red) + (p * to.color.red);
	output.color.green = (pp * from.color.green) + (p * to.color.green);
	output.color.blue = (pp * from.color.blue) + (p * to.color.blue);
	output.stencil = (pp * from.stencil) + (p * to.stencil);

	return output;
}
