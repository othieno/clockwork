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
#include "Viewport.hh"
#include "Framebuffer.hh"
#include <algorithm>

using clockwork::Viewport;
using clockwork::ViewportTransform;


static constexpr double
clamp(const double d) {
	return std::max(0.0, std::min(d, 1.0));
}


Viewport::Viewport(const double X, const double Y, const double W, const double H, const double N, const double F) :
x(clamp(X)),
y(clamp(Y)),
width(clamp(W)),
height(clamp(H)),
near(clamp(N)),
far(clamp(F)) {}


ViewportTransform::ViewportTransform() :
scale(1.0, 1.0, 1.0),
translate(0.0, 0.0, 0.0) {}


ViewportTransform::ViewportTransform(const Viewport& viewport, const Framebuffer& framebuffer) {
	const auto& resolution = framebuffer.getResolutionSize();
	const auto fbw = resolution.width();
	const auto fbh = resolution.height();

	// The actual viewport size based on the normalized viewport's parameters
	// and the framebuffer's resolution.
	const double x = viewport.x * fbw;
	const double y = viewport.y * fbh;
	const double w = viewport.width * fbw;
	const double h = viewport.height * fbh;
	const double n = viewport.near;
	const double f = viewport.far;

	// The viewport transformation is defined as:
	// P'  = (scale                                 P)    + (translate)
	// x_w = (viewport_width / 2)                 * x_ndc + (viewport_x + (viewport_width / 2))
	// y_w = (viewport_height / 2)                * y_ndc + (viewport_y + (viewport_height / 2))
	// z_w = ((viewport_far - viewport_near) / 2) * z_ndc + ((viewport_near + viewport_far) / 2)
	// where the 3D point <x_ndc, y_ndc and z_ndc> is in the normalized device
	// coordinate (NDC) space.
	scale.x = 0.5 * w;
	scale.y = 0.5 * h;
	scale.z = 0.5 * (f - n);
	translate.x = x + scale.x;
	translate.y = y + scale.y;
	translate.z = 0.5 * (f + n);
}
