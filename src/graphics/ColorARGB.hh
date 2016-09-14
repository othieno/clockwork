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
#ifndef CLOCKWORK_COLOR_ARGB_HH
#define CLOCKWORK_COLOR_ARGB_HH

#include <cstdint>


namespace clockwork {
/**
 * A normalized ARGB color.
 */
struct ColorARGB {
	/**
	 * The color's normalised red channel.
	 */
	float red;
	/**
	 * The color's normalised green channel.
	 */
	float green;
	/**
	 * The color's normalised blue channel.
	 */
	float blue;
	/**
	 * The color's normalised alpha channel.
	 */
	float alpha;
	/**
	 * Instantiate an ARGB color with normalised alpha, red, green and blue channels.
	 * @param red the red channel.
	 * @param green the green channel.
	 * @param blue the blue channel.
	 * @param alpha the alpha channel.
	 */
	ColorARGB(const float red = 0.0f, const float green = 0.0f, const float blue = 0.0f, const float alpha = 1.0f);
	/**
	 * Returns the color's 32-bit integer representation.
	 */
	operator std::uint32_t() const;
public:
	/**
	 * Returns the specified ColorARGB's 32-bit integer representation.
	 * @param color the ColorARGB instance to merge.
	 */
	static std::uint32_t merge(const ColorARGB& color);
	/**
	 * Creates a ColorARGB object from the specified 32-bit integer.
	 * @param ARGB the 32-bit integer that represents an A8R8G8B8 color.
	 */
	static ColorARGB split(const std::uint32_t& ARGB);
	/**
	 * Returns a random color.
	 */
	static ColorARGB getRandom();
};
} // namespace clockwork

#endif // CLOCKWORK_COLOR_ARGB_HH
