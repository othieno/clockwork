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

#include <string>


namespace clockwork {
namespace graphics {

/**
 * A fragment is the result of a renderer's per-vertex operation applied to a vertex.
 * Primarily, a fragment should contain a vertex's 2D normalised device coordinates (or
 * viewport coordinates), its depth value, its surface normal and a base color that will all
 * be used to determine a color that will be written to the framebuffer.
 */
struct Fragment
{
public:
	/**
	 * The fragment's position in window coordinates, as well as its depth value.
	 */
	double x, y, z;
	/**
	 * The fragment's texture mapping coordinates.
	 */
	double u, v;
	/**
	 * The fragment's normal vector components.
	 */
	double i, j, k;
	/**
	 * The fragment's normalised color channels.
	 */
	double a, r, g, b;
	/**
	 * The fragment's stencil value.
	 */
	uint8_t stencil;
	/**
	 * The default constructor.
	 */
	Fragment();
	/**
	 * Convert the fragment data into string format.
	 * @param fragment the fragment to convert.
	 */
	static std::string toString(const Fragment& fragment);
};

} // namespace graphics
} // namespace clockwork
