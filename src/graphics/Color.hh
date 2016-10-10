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
#ifndef CLOCKWORK_COLOR_HH
#define CLOCKWORK_COLOR_HH

#include <cstdint>


namespace clockwork {
/**
 * A color representation that contains normalized values for a color's red,
 * green, blue and alpha channels.
 */
struct Color {
	/**
	 * Instantiates a Color object.
	 */
	Color();
	/**
	 * Instantiates a Color object with the specified channels.
	 */
	Color(const float red, const float green, const float blue, const float alpha = 1.0f);
	/**
	 * Instantiates a Color object from the specified 32-bit A8R8G8B8 integer representation.
	 * @param ARGB a 32-bit integer that represents an A8R8G8B8 color.
	 */
	explicit Color(const std::uint32_t ARGB);
	/**
	 * Returns the Color object's 32-bit A8R8G8B8 integer representation.
	 */
	operator std::uint32_t() const;
	/**
	 * Returns the specified color's 32-bit A8R8G8B8 integer representation.
	 * @param color the Color object to merge.
	 */
	static std::uint32_t merge(const Color& color);
	/**
	 * Creates a Color object from the specified 32-bit A8R8G8B8 integer representation.
	 * @param ARGB a 32-bit integer that represents an A8R8G8B8 color.
	 */
	static Color split(const std::uint32_t& ARGB);
	/**
	 * The color's normalized red channel.
	 */
	float red;
	/**
	 * The color's normalized green channel.
	 */
	float green;
	/**
	 * The color's normalized blue channel.
	 */
	float blue;
	/**
	 * The color's normalized alpha channel.
	 */
	float alpha;
};
} // namespace clockwork

#endif // CLOCKWORK_COLOR_HH
