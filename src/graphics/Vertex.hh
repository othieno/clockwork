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
#ifndef CLOCKWORK_VERTEX_HH
#define CLOCKWORK_VERTEX_HH

#include "Point4.hh"
#include "ColorARGB.hh"


namespace clockwork {
/**
 *
 */
struct Vertex : public Point4 {
	/**
	 * Instantiates a Vertex object at the specified position.
	 */
	Vertex(const double x = 0, const double y = 0, const double z = 0, const double w = 1.0);
	/**
	 * Instantiates a Vertex object at the specified homogeneous position.
	 * @param position the vertex's initial position.
	 */
	explicit Vertex(const Point4& position);
	/**
	 * Returns true if the vertex specified vertex is strictly smaller than this vertex.
	 * A vertex V is considered smaller than a vertex U if V.y < U.y. If V.y is
	 * equivalent to U.y, V is smaller than U if V.x < U.x. If both of the aforementioned
	 * pairs are equivalent, V is smaller than U if V.z < U.z.
	 * @param that the vertex to compare.
	 */
	bool operator<(const Vertex& that) const;
	/**
	 * Estimates the value of a vertex between two specified fragments.
	 */
	static Vertex estimate(const Vertex& from, const Vertex& to, const double interpolant);
	/**
	 * The vertex's normal vector.
	 */
	Vector3 normal;
	/**
	 * The vertex's texture-space horizontal mapping coordinate.
	 */
	double u;
	/**
	 * The vertex's texture-space vertical mapping coordinate.
	 */
	double v;
	/**
	 * The vertex's color.
	 */
	ColorARGB color;
};
/**
 * A collection of vertices.
 */
using VertexArray = QList<Vertex>;
} // namespace clockwork

#endif // CLOCKWORK_VERTEX_HH
