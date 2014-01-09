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
#include "fragment.hh"


clockwork::graphics::Fragment::Fragment(const double& inu, const double& inv) :
x(0), y(0), z(0), w(1),
i(0), j(0), k(0),
u(inu), v(inv),
color(1, 1, 1, 1),
stencil(0)
{}


clockwork::graphics::Fragment
clockwork::graphics::Fragment::interpolate
(
	const clockwork::graphics::Fragment& start,
	const clockwork::graphics::Fragment& end,
	const double& p
)
{
	const double pp = 1 - p;
	clockwork::graphics::Fragment output;

	output.x = (p * start.x) + (pp * end.x);
	output.y = (p * start.y) + (pp * end.y);
	output.z = (p * start.z) + (pp * end.z);

	output.u = (p * start.u) + (pp * end.u);
	output.v = (p * start.v) + (pp * end.v);

	output.i = (p * start.i) + (pp * end.i);
	output.j = (p * start.j) + (pp * end.j);
	output.k = (p * start.k) + (pp * end.k);

	output.color.alpha = (p * start.color.alpha) + (pp * end.color.alpha);
	output.color.red = (p * start.color.red) + (pp * end.color.red);
	output.color.green = (p * start.color.green) + (pp * end.color.green);
	output.color.blue = (p * start.color.blue) + (pp * end.color.blue);

	output.stencil = (p * start.stencil) + (pp * end.stencil);

	return output;
}


std::string
clockwork::graphics::Fragment::toString(const clockwork::graphics::Fragment&)
{
	return "Implement clockwork::graphics::Fragment::toString";
}
