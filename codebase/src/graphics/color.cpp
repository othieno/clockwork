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
#include "color.hh"
#include <algorithm>

using clockwork::graphics::ColorRGBA;


ColorRGBA::ColorRGBA(const float& r, const float& g, const float& b, const float& a) :
red(r),
green(g),
blue(b),
alpha(a)
{}


uint32_t
ColorRGBA::merge() const
{
	uint32_t output = 0;

	// Convert the channels to integer values.
	const auto R = static_cast<uint32_t>(std::round(255.0f * std::max(0.0f, red)));
	const auto G = static_cast<uint32_t>(std::round(255.0f * std::max(0.0f, green)));
	const auto B = static_cast<uint32_t>(std::round(255.0f * std::max(0.0f, blue)));
	const auto A = static_cast<uint32_t>(std::round(255.0f * std::max(0.0f, alpha)));

	if (A > 0)
		output  = std::min(255U, A) << 24;
	if (R > 0)
		output |= std::min(255U, R) << 16;
	if (G > 0)
		output |= std::min(255U, G) <<  8;
	if (B > 0)
		output |= std::min(255U, B);

	return output;
}


ColorRGBA
ColorRGBA::getRandom()
{
	static std::random_device device;
	static std::mt19937 gen(device());
	static std::uniform_real_distribution<double> distribution(0, 1);

	return ColorRGBA(distribution(gen), distribution(gen), distribution(gen));
}


ColorRGBA
ColorRGBA::split(const uint32_t& ARGB)
{
	if (ARGB == 0)
		return ColorRGBA(0, 0, 0, 0);
	else
	{
		return ColorRGBA
		(
			((ARGB >> 16) & 0xff) * 0.00392156862, // 0.00392156862 == (1/255).
			((ARGB >>  8) & 0xff) * 0.00392156862,
			(ARGB         & 0xff) * 0.00392156862,
			((ARGB >> 24) & 0xff) * 0.00392156862
		);
	}
}
