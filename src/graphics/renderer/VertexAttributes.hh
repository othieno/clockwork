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
#ifndef CLOCKWORK_VERTEX_ATTRIBUTES_HH
#define CLOCKWORK_VERTEX_ATTRIBUTES_HH


namespace clockwork {
/**
 * @see math/Point.hh.
 */
struct Point;
/**
 * @see math/Point3.hh.
 */
struct Point3;
/**
 * @see math/Vector3.hh.
 */
struct Vector3;
/**
 *
 */
struct VertexAttributes {
	/**
	 * Instantiates a VertexAttributes object.
	 */
	VertexAttributes(
		const Point3* position = nullptr,
		const Vector3* normal = nullptr,
		const Point* textureCoordinates = nullptr
	);
	/**
	 * A reference to a vertex position.
	 */
	const Point3* position;
	/**
	 * A reference to a vertex's normal vector.
	 */
	const Vector3* normal;
	/**
	 * A reference to a vertex's texture mapping coordinates.
	 */
	const Point* textureCoordinates;
};
} // namespace clockwork

#endif // CLOCKWORK_VERTEX_ATTRIBUTES_HH
