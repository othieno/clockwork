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
#ifndef CLOCKWORK_FRAGMENT_HH
#define CLOCKWORK_FRAGMENT_HH

#include "RenderingAlgorithm.hh"
#include "Varying.hh"
#include "Vector3.hh"
#include "ColorARGB.hh"


namespace clockwork {
namespace detail {
/**
 *
 */
template<RenderingAlgorithm algorithm>
struct Fragment {
	/**
	 * The fragment's screen-space horizontal position.
	 */
	std::uint32_t x;
	/**
	 * The fragment's screen-space vertical position.
	 */
	std::uint32_t y;
	/**
	 * The fragment's depth.
	 */
	double depth;
	/**
	 * The fragment's stencil value.
	 */
	std::uint8_t stencil;
	/**
	 * The fragment's varying variables.
	 */
	Varying<algorithm> varying;
};
} // namespace detail
/**
 * A fragment is the result of a per-vertex operation (vertex shader) applied to
 * a vertex, which then gets passed to the per-fragment operation (fragment shader).
 * A fragment contains the vertex's 2D screen space coordinates, depth value,
 * surface normal and a base color that will all be used to determine values that
 * will be written to the framebuffer's attachments.
 */
struct Fragment {
	/**
	 * Instantiates a Fragment object.
	 */
	Fragment();
	/**
	 * Estimates the value of a fragment between two specified fragments.
	 */
	static Fragment estimate(const Fragment& from, const Fragment& to, const double interpolant);
	/**
	 * The fragment's screen-space horizontal position.
	 */
	std::uint32_t x;
	/**
	 * The fragment's screen-space vertical position.
	 */
	std::uint32_t y;
	/**
	 * The fragment's depth.
	 */
	double z;
	/**
	 * The fragment's normal vector.
	 */
	Vector3 normal;
	/**
	 * The fragment's texture-space horizontal mapping coordinate.
	 */
	double u;
	/**
	 * The fragment's texture-space vertical mapping coordinate.
	 */
	double v;
	/**
	 * The fragment's color.
	 */
	ColorARGB color;
	/**
	 * The fragment's stencil value.
	 */
	std::uint8_t stencil;
};
} // namespace clockwork

#endif // CLOCKWORK_FRAGMENT_HH
