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
    * This primitive assembly operation creates triangle primitives from a collection
    * of vertices in clip space.
    * @param vertices the collection of vertices that will create a set of primitives.
    */
   VertexArray& primitiveAssembly(VertexArray& vertices) const override final;
   /**
    * Perform polygon clipping (Sutherland-Hodgman) on a collection of vertices.
    * @param vertices the vertices to clip.
    */
   VertexArray& clip(VertexArray& vertices) const override final;
   /**
    * @see RenderParameters::backfaceCulling.
    */
   VertexArray& backfaceCulling(VertexArray&) const override final;
   /**
    * Rasterise triangle primitives using polygon scan conversion.
    * @param uniforms uniform values.
    * @param vertices the vertices that will form the triangle primitives to rasterise.
    */
   void rasterise(const RenderParameters::Uniforms& uniforms, const VertexArray& vertices) const override;
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
