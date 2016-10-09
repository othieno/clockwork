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
#ifndef CLOCKWORK_VARYING_HH
#define CLOCKWORK_VARYING_HH

#include "RenderingAlgorithm.hh"
#include "Color.hh"


namespace clockwork {
namespace detail {
/**
 * Varying variables are sets of data that are shared between the
 * vertex and fragment shaders.
 */
template<RenderingAlgorithm> struct Varying {};
/**
 * Varying variables for the random shading renderer.
 */
template<>
struct Varying<RenderingAlgorithm::RandomShading> {
	/**
	 * A random color shared by all vertices that belong to an identical face.
	 */
	Color faceColor;
};
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_VARYING_HH
