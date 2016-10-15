/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
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

#include <cstdint>


namespace clockwork {
/**
 *
 */
struct Fragment {
	/**
	 * Instantiates a Fragment object.
	 */
	Fragment(
		const std::uint32_t x = 0,
		const std::uint32_t y = 0,
		const double z = 0,
		const std::uint8_t stencil = 0
	);
	/**
	 * The fragment's screen-space horizontal position.
	 */
	std::uint32_t x;
	/**
	 * The fragment's screen-space vertical position.
	 */
	std::uint32_t y;
	/**
	 * The fragment's depth value.
	 */
	double z;
	/**
	 * The fragment's stencil value.
	 */
	std::uint8_t stencil;
};
} // namespace clockwork

#endif // CLOCKWORK_FRAGMENT_HH
