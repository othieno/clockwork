/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
#ifndef CLOCKWORK_POLYGON_MODE_HH
#define CLOCKWORK_POLYGON_MODE_HH

#include "enum_traits.hh"


namespace clockwork {
/**
 * An enumeration of available polygon modes.
 */
enum class PolygonMode {
	Point,
	Line,
	Fill
};
/**
 * Returns a list of all available polygon modes.
 */
template<> constexpr std::initializer_list<PolygonMode>
enum_traits<PolygonMode>::enumerators() {
	return {
		PolygonMode::Point,
		PolygonMode::Line,
		PolygonMode::Fill
	};
}
/**
 * Returns the human-readable name of the specified polygon mode.
 * @param mode the polygon mode to query.
 */
template<> template<class String> String
enum_traits<PolygonMode>::name(const PolygonMode mode) {
	switch (mode) {
		case PolygonMode::Point:
			return "Point";
		case PolygonMode::Line:
			return "Line";
		case PolygonMode::Fill:
			return "Fill";
		default:
			return "???";
	}
}
} // namespace clockwork

#endif // CLOCKWORK_POLYGON_MODE_HH
