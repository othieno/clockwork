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

#include <string>
#include "vertex.hh"


namespace clockwork {
namespace graphics {

/**
 * A fragment is the result of a renderer's per-vertex operation applied to a vertex.
 * Primarily, a fragment should contain a vertex's 2D screen space coordinates its depth
 * value, its surface normal and a base color that will all be used to determine a color
 * that will be written to the framebuffer.
 */
struct Fragment
{
public:
   /**
    * The fragment's screen space position.
    */
   uint32_t x, y;
   /**
    * The fragment's depth value.
    */
   double z;
   /**
    * The fragment's normal vector.
    */
   clockwork::Vector3 normal;
   /**
    * The fragment's texture mapping coordinates.
    */
   double u, v;
   /**
    * The fragment's normalised color.
    */
   ColorRGBA color;
   /**
    * The fragment's stencil value.
    */
   uint8_t stencil;
   /**
    * The default constructor.
    */
   Fragment();
   /**
    * Instantiate a fragment from a given vertex attribute. Note that the vertex's
    * position must be in window space coordinates. To make sure that no precision is
    * lost, make sure that the vertex's X and Y coordinates are positive and rounded-off
    * to the nearest integer because this constructor truncates the aforementioned
    * coordinates to unsigned integers.
    * @param vertex the vertex attribute that will initialise this fragment.
    */
   explicit Fragment(const Vertex& vertex);
   /**
    * Interpolate the value of a fragment in between two other fragments.
    * @param start the first fragment.
    * @param end the second fragment.
    * @param p the interpolant.
    */
   static Fragment interpolate(const Fragment& start, const Fragment& end, const double& p);
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::Fragment&);
