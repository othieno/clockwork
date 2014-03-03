/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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
#include "texture.hh"
#include "color.hh"
#include <vector>


namespace clockwork {
namespace graphics {

struct Vertex : public clockwork::Point4
{
public:
   /**
    * Instantiate a Vertex at the given position.
    * @param x the vertex's X coordinate.
    * @param y the vertex's Y coordinate.
    * @param z the vertex's Z coordinate.
    * @param w the vertex's W coordinate.
    */
   Vertex(const double& x = 0, const double& y = 0, const double& z = 0, const double& w = 1);
   /**
    * Initialise a vertex with a given 3D homogeneous position.
    * @param position the vertex's position.
    */
   explicit Vertex(const clockwork::Point4& position);
   /**
    * The vertex's normal.
    */
   clockwork::Vector3 normal;
   /**
    * The vertex's color.
    */
   ColorRGBA color;
   /**
    * The vertex's texture mapping coordinates.
    */
   Texture::Coordinates uvmap;
   /**
    * The less than operator for vertices returns true if the vertex V is 'smaller' than
    * this vertex. A vertex is considered 'smaller' if its Y coordinate is smaller than
    * the vertex it's being compared to. If both Y coordinates are equivalent, then the X
    * coordinates are compared, and so forth until the Z coordinates.
    * @param V a vertex to compare against this vertex.
    */
   bool operator<(const Vertex& V) const;
   /**
    * Interpolate the value of a vertex in between two other vertices.
    * @param start the first vertex.
    * @param end the second vertex.
    * @param p the interpolant.
    */
   static Vertex interpolate(const Vertex& start, const Vertex& end, const double& p);
};

/**
 * An array of vertices.
 */
using VertexArray = std::vector<Vertex>;

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::Vertex&);
