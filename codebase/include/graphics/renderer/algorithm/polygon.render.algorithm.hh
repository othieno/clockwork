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

#include "render.algorithm.hh"


namespace clockwork {
namespace graphics {

/**
 * A generic polygon render algorithm.
 */
class PolygonRenderAlgorithm : public RenderAlgorithm
{
public:
   /**
    * @see RenderAlgorithm::primitiveAssembly.
    */
   VertexArray& primitiveAssembly(const clockwork::graphics::PrimitiveMode&, VertexArray&) const override final;
   /**
    * Perform polygon clipping (Sutherland-Hodgman) on a collection of vertices.
    * @param vertices the vertices to clip.
    */
   VertexArray& clip(VertexArray& vertices) const override final;
   /**
    * @see RenderAlgorithm::backfaceCulling.
    */
   VertexArray& backfaceCulling(VertexArray&) const override final;
   /**
    * Rasterise triangle primitives using polygon scan conversion, under a given set of render parameters.
    * @see RenderAlgorithm::rasterise.
    */
   void rasterise(const RenderAlgorithm::Parameters&, const VertexArray&) const override;
protected:
   /**
    * Instantiate a PolygonRenderAlgorithm with a given algorithm identifier.
    * @param identifier the render algorithm's identifier.
    */
   PolygonRenderAlgorithm(const RenderAlgorithm::Identifier& identifier);
private:
   /**
    * A PolygonRenderAlgorithm object are not copyable.
    */
   PolygonRenderAlgorithm(const PolygonRenderAlgorithm&) = delete;
   PolygonRenderAlgorithm& operator=(const PolygonRenderAlgorithm&) = delete;
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
