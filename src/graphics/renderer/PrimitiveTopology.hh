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
#ifndef CLOCKWORK_PRIMITIVE_TOPOLOGY_HH
#define CLOCKWORK_PRIMITIVE_TOPOLOGY_HH

#include "enumeration.hh"


namespace clockwork {
/**
 * An enumeration of available primitive topologies that determine how a set of
 * vertices gets organized into a collection of geometric primitives.
 */
enum class PrimitiveTopology {
	Point,
	Line,
	LineStrip,
	LineLoop,
	Triangle,
	TriangleStrip,
	TriangleFan
};
/**
 * Returns a list of all available primitive topologies.
 */
template<> constexpr std::initializer_list<PrimitiveTopology>
enumeration<PrimitiveTopology>::enumerators() {
	return {
		PrimitiveTopology::Point,
		PrimitiveTopology::Line,
		PrimitiveTopology::LineStrip,
		PrimitiveTopology::LineLoop,
		PrimitiveTopology::Triangle,
		PrimitiveTopology::TriangleStrip,
		PrimitiveTopology::TriangleFan
	};
}
/**
 * Returns the human-readable name of the specified system error.
 * @param error the system error to query.
 */
template<> template<class String> String
enumeration<PrimitiveTopology>::name(const PrimitiveTopology topology) {
	switch (topology) {
		case PrimitiveTopology::Point:
			return "Points";
		case PrimitiveTopology::Line:
			return "Lines";
		case PrimitiveTopology::LineStrip:
			return "Line strips";
		case PrimitiveTopology::LineLoop:
			return "Line loops";
		case PrimitiveTopology::Triangle:
			return "Triangles";
		case PrimitiveTopology::TriangleStrip:
			return "Triangle strips";
		case PrimitiveTopology::TriangleFan:
			return "Triangle fans";
		default:
			return "???";
	}
}
} // namespace clockwork

#endif // CLOCKWORK_PRIMITIVE_TOPOLOGY_HH
