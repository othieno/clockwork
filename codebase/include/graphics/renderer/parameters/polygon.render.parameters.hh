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

#include "render.parameters.hh"


namespace clockwork {
namespace graphics {

/**
 * A polygon renderer's parameter set.
 */
class PolygonRenderParameters : public RenderParameters
{
public:
   /**
    * @see RenderParameters::primitiveAssembly.
    */
   virtual void primitiveAssembly(const std::array<const Fragment*, 3>& triangle) const override final;
protected:
   /**
    * Instantiate a PolygonRenderParameters object with a given render type.
    * @param type the render type.
    */
   PolygonRenderParameters(const RenderParameters::Type& type);
private:
   /**
    * A PolygonRenderParameters object are not copyable.
    */
   PolygonRenderParameters(const PolygonRenderParameters&) = delete;
   PolygonRenderParameters& operator=(const PolygonRenderParameters&) = delete;
   /**
    * Perform scan conversion on a triangular polygonal face. The fragments must be
    * arranged in a such a way that f0 has the smallest y value, f2 has the largest
    * and f1's y value is between the two.
    * @param f0 the first fragment that will make one point of a triangle.
    * @param f1 the second fragment that will make one point of a triangle.
    * @param f2 the third fragment that will make one point of a triangle.
    */
   void scanConversion(const Fragment& f0, const Fragment& f1, const Fragment& f2) const;
};

} // namespace graphics
} // namespace clockwork
