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
#include "Color.hh"
#include <algorithm>
#include <cmath>
#include <random>

using clockwork::Color;


Color::Color() :
Color(0.0f, 0.0f, 0.0f, 1.0f) {}


Color::Color(const float r, const float g, const float b, const float a) :
red(r),
green(g),
blue(b),
alpha(a) {}


Color::Color(const std::uint32_t argb) {
	*this = Color::split(argb);
}


Color::operator std::uint32_t() const {
	return Color::merge(*this);
}


std::uint32_t
Color::merge(const Color& color) {
	std::uint32_t output = 0;

	// Convert the channels to integer values.
	const auto R = static_cast<std::uint32_t>(std::round(255.0f * std::max(0.0f, color.red)));
	const auto G = static_cast<std::uint32_t>(std::round(255.0f * std::max(0.0f, color.green)));
	const auto B = static_cast<std::uint32_t>(std::round(255.0f * std::max(0.0f, color.blue)));
	const auto A = static_cast<std::uint32_t>(std::round(255.0f * std::max(0.0f, color.alpha)));

	if (A > 0) {
		output  = std::min(255U, A) << 24;
	}
	if (R > 0) {
		output |= std::min(255U, R) << 16;
	}
	if (G > 0) {
		output |= std::min(255U, G) <<  8;
	}
	if (B > 0) {
		output |= std::min(255U, B);
	}

	return output;
}


Color
Color::split(const std::uint32_t& ARGB) {
	if (ARGB == 0) {
		return Color();
	} else {
		return Color (
			((ARGB >> 16) & 0xFF) * 0.00392156862, // 0.00392156862 == (1/255).
			((ARGB >>  8) & 0xFF) * 0.00392156862,
			(ARGB         & 0xFF) * 0.00392156862,
			((ARGB >> 24) & 0xFF) * 0.00392156862
		);
	}
}
