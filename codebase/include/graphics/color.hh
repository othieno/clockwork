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

#include <cstdint>


namespace clockwork {
namespace graphics {

/**
 * Merge normalised alpha, red, green and blue color channels into one 32-bit integer.
 * @param alpha the color's alpha channel.
 * @param red the color's red channel.
 * @param green the color's green channel.
 * @param blue the color's blue channel.
 */
uint32_t mergeColorChannels(const double& alpha, const double& red, const double& green, const double& blue);

struct ColorRGB
{
	/**
	 * The color's normalised red channel.
	 */
	double red;
	/**
	 * The color's normalised green channel.
	 */
	double green;
	/**
	 * The color's normalised blue channel.
	 */
	double blue;
	/**
	 * Instantiate an RGB color with normalised red,
	 * green and blue channels.
	 * @param red the red channel.
	 * @param green the green channel.
	 * @param blue the blue channel.
	 */
	ColorRGB(const double& red = 1, const double& green = 1, const double& blue = 1);
	/**
	 * Merge the red, green and blue channels into one 32-bit integer.
	 */
	inline uint32_t merge() const
	{
		return mergeColorChannels(1.0, red, green, blue);
	}
	/**
	 * Return a random RGB color.
	 */
	static ColorRGB getRandom();
};

struct ColorARGB
{
	/**
	 * The color's normalised alpha channel.
	 */
	double alpha;
	/**
	 * The color's normalised red channel.
	 */
	double red;
	/**
	 * The color's normalised green channel.
	 */
	double green;
	/**
	 * The color's normalised blue channel.
	 */
	double blue;
	/**
	 * Instantiate an ARGB color with normalised red,
	 * green and blue channels.
	 * @param alpha the alpha channel.
	 * @param red the red channel.
	 * @param green the green channel.
	 * @param blue the blue channel.
	 */
	ColorARGB(const double& alpha = 1, const double& red = 1, const double& green = 1, const double& blue = 1);
	/**
	 * Merge the alpha, red, green and blue channels into one 32-bit integer.
	 */
	inline uint32_t merge() const
	{
		return mergeColorChannels(alpha, red, green, blue);
	}
	/**
	 * Return a random ARGB color.
	 */
	static ColorARGB getRandom();
};

} // namespace graphics
} // namespace clockwork
