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

#include "point4.hh"
#include "vector3.hh"


namespace clockwork {
namespace graphics {

class Vertex : public clockwork::Point4
{
public:
	/**
	 * TODO Explain me better.
	 * Instantiate a Vertex at the given position.
	 */
	Vertex(const double& x = 0, const double& y = 0, const double& z = 0, const double& w = 1);
	/**
	 * Return the vertex normal.
	 */
	const clockwork::Vector3& getNormal() const;
	/**
	 * Set the vertex's normal.
	 * @param normal the normal to set.
	 */
	void setNormal(const clockwork::Vector3& normal);
private:
	/**
	 * The vertex's normal.
	 */
	clockwork::Vector3 _normal;
};

} // namespace graphics
} // namespace clockwork
