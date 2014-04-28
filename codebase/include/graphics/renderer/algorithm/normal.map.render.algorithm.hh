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

#include "polygon.render.algorithm.hh"


namespace clockwork {
namespace graphics {

/**
 * @see render.algorithm.factory.hh.
 */
class RenderAlgorithmFactory;

/**
 * A normal-map render algorithm.
 */
class NormalMapRenderAlgorithm : public PolygonRenderAlgorithm
{
friend class RenderAlgorithmFactory;
public:
   /**
    * @see RenderAlgorithm::vertexProgram.
    */
   Vertex vertexProgram
   (
      const RenderAlgorithm::Parameters&,
      const clockwork::Point3& position,
      const clockwork::Vector3& normal,
      const Texture::Coordinates&
   ) const override final;
   /**
    * This implementation of the fragment program converts a fragment's surface normal into a color.
    * @see RenderAlgorithm::fragmentProgram.
    */
   uint32_t fragmentProgram(const RenderAlgorithm::Parameters&, const Fragment&) const override final;
private:
   /**
    * The NormalMapRenderAlgorithm is a singleton, and only instantiable by the RenderAlgorithmFactory.
    */
   NormalMapRenderAlgorithm();
   NormalMapRenderAlgorithm(const NormalMapRenderAlgorithm&) = delete;
   NormalMapRenderAlgorithm& operator=(const NormalMapRenderAlgorithm&) = delete;
};

} // namespace graphics
} // namespace clockwork
