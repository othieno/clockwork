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
#include <QList>


namespace clockwork {
namespace graphics {

/**
 * @see render.parameters.factory.hh.
 */
class RenderParametersFactory;

/**
 * A line render's parameters.
 */
class LineRenderParameters: public RenderParameters
{
friend class RenderParametersFactory;
public:
   /**
    * Line algorithms.
    */
   enum class LineAlgorithm
   {
      Bresenham,
      XiaolinWu
   };
   /**
    * Line primitives.
    */
   enum class LinePrimitive
   {
      Line,
      LineStrip,
      LineLoop
   };
   /**
    * Return the list of available line algorithms.
    */
   static QList<LineRenderParameters::LineAlgorithm> getLineAlgorithms();
   /**
    * Return the current line algorithm.
    */
   const LineRenderParameters::LineAlgorithm& getLineAlgorithm() const;
   /**
    * Set the line algorithm.
    * @param algorithm the line algorithm to set.
    */
   void setLineAlgorithm(const LineRenderParameters::LineAlgorithm& algorithm);
   /**
    * Return the list of available line primitives.
    */
   static QList<LineRenderParameters::LinePrimitive> getLinePrimitives();
   /**
    * Return the current type of line primitive used during rasterisation.
    */
   const LineRenderParameters::LinePrimitive& getLinePrimitive() const;
   /**
    * Set the line primitive to use during rasterisation.
    * @param primitive the line primitive type to use.
    */
   void setLinePrimitive(const LineRenderParameters::LinePrimitive& primitive);
   /**
    * Perform line clipping (Cohen-Sutherland) on a collection of primitives.
    * @param vertices the vertices to clip.
    */
   VertexArray& clip(VertexArray& vertices) const override final;
   /**
    * Rasterise line primitives using either Bresenham or Xiaolin Wu's line algorithm.
    * @param uniforms uniform values.
    * @param vertices the vertices that form line primitives to rasterise.
    */
   void rasterise(const RenderParameters::Uniforms& uniforms, const VertexArray& vertices) const override final;
   /**
    * Draw a line between two vertices using Bresenham's line algorithm.
    * @param uniforms uniform variables that will be passed to the fragment program.
    * @param V0 the line's origin.
    * @param V1 the line's endpoint.
    */
   void drawlineBresenham(const RenderParameters::Uniforms& uniforms, const Vertex& V0, const Vertex& V1) const;
   /**
    * Draw a line between two vertices using Xiaolin Wu's line algorithm.
    * @param uniforms uniform variables that will be passed to the fragment program.
    * @param V0 the line's origin.
    * @param V1 the line's endpoint.
    */
   void drawlineXiaolinWu(const RenderParameters::Uniforms& uniforms, const Vertex& V0, const Vertex& V1) const;
private:
   /**
    * The LineRenderParameters is a singleton, and only instantiable by the RenderParametersFactory.
    */
   LineRenderParameters();
   LineRenderParameters(const LineRenderParameters&) = delete;
   LineRenderParameters& operator=(const LineRenderParameters&) = delete;
   /**
    * The type of line primitives to use during rasterisation.
    */
   LineRenderParameters::LinePrimitive _linePrimitive;
   /**
    * The line algorithm.
    */
   LineRenderParameters::LineAlgorithm _lineAlgorithm;
   /**
    * The line drawing function.
    */
   std::function<void(const RenderParameters::Uniforms&, const Vertex&, const Vertex&)> _drawline;
};

} // namespace graphics
} // namespace clockwork
