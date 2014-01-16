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

#include <QImage>
#include <cstdint>
#include "fragment.hh"


namespace clockwork {
namespace graphics {

class Framebuffer
{
public:
   /**
    * Instantiate a framebuffer with a given width and height.
    * @param width the framebuffer's width.
    * @param height the framebuffer's height.
    */
   Framebuffer(const uint32_t& width, const uint32_t& height);
   /**
    * The destructor.
    */
   ~Framebuffer();
   /**
    * Return the pixel buffer.
    */
   const uint32_t* getPixelBuffer() const;
   /**
    * Return the pixel buffer's clear value.
    */
   const uint32_t& getPixelBufferClearValue() const;
   /**
    * Set the pixel buffer's clear value.
    * @param value the clear value to set.
    */
   void setPixelBufferClearValue(const uint32_t& value);
   /**
    * Return the depth buffer.
    */
   const double* getDepthBuffer() const;
   /**
    * Return the depth buffer's clear value.
    */
   const double& getDepthBufferClearValue() const;
   /**
    * Set the depth buffer's clear value.
    * @param value the clear value to set.
    */
   void setDepthBufferClearValue(const double& value);
   /**
    * Return the stencil buffer.
    */
   const uint8_t* getStencilBuffer() const;
   /**
    * Return the stencil buffer's clear value.
    */
   const uint8_t& getStencilBufferClearValue() const;
   /**
    * Set the stencil buffer's clear value.
    * @param value the clear value to set.
    */
   void setStencilBufferClearValue(const uint8_t& value);
   /**
    * Return the accumulation buffer.
    */
   const uint32_t* getAccumulationBuffer() const;
   /**
    * Return the accumulation buffer's clear value.
    */
   const uint32_t& getAccumulationBufferClearValue() const;
   /**
    * Set the accumulation buffer's clear value.
    * @param value the clear value to set.
    */
   void setAccumulationBufferClearValue(const uint32_t& value);
   /**
    * Write a fragment to the framebuffer.
    * @param fragment the fragment to write to the framebuffer.
    * @param fop the fragment operation that converts a fragment into a pixel value.
    */
   void plot(const Fragment& fragment, const std::function<uint32_t(const Fragment&)>& fop);
   /**
    * Write a pixel and its depth value to the framebuffer at the given coordinate.
    * @param x the framebuffer element's row position.
    * @param y the framebuffer element's column position.
    * @param depth the depth value to write.
    * @param pixel the pixel value to write.
    */
   void plot(const uint32_t& x, const uint32_t& y, const double& depth, const uint32_t& pixel);
   /**
    * Return the framebuffer's width.
    */
   const uint32_t& getWidth() const;
   /**
    * Return the framebuffer's height.
    */
   const uint32_t& getHeight() const;
   /**
    * Clear the framebuffer.
    */
   void clear();
   /**
    * Resize the framebuffer.
    * @param width the framebuffer's new width.
    * @param height the framebuffer's new height.
    */
   void resize(const uint32_t& width, const uint32_t& height);
   /**
    * Discard the fragment at the given <x, y> coordinate.
    * @param x the framebuffer element's row position.
    * @param y the framebuffer element's column position.
    */
   void discard(const uint32_t& x, const uint32_t& y);
   /**
    * Convert the framebuffer data into string format.
    * @param framebuffer the framebuffer to convert.
    */
   static std::string toString(const Framebuffer& framebuffer);
private:
   /**
    * The framebuffer's width.
    */
   uint32_t _width;
   /**
    * The framebuffer's height.
    */
   uint32_t _height;
   /**
    * The depth buffer which holds color information for each pixel in the display.
    */
   uint32_t* _pixelBuffer;
   /**
    * The pixel buffer's clear value.
    */
   uint32_t _pixelBufferClearValue;
   /**
    * The depth buffer which holds depth information for each pixel in the display.
    */
   double* _depthBuffer;
   /**
    * The depth buffer's clear value.
    */
   double _depthBufferClearValue;
   /**
    * TODO Explain me.
    */
   uint8_t* _stencilBuffer;
   /**
    * The depth buffer's clear value.
    */
   uint8_t _stencilBufferClearValue;
   /**
    * TODO Explain me.
    */
   uint32_t* _accumulationBuffer;
   /**
    * The depth buffer's clear value.
    */
   uint32_t _accumulationBufferClearValue;
   /**
    * Return the buffer offset for a given <x, y> coordinate. If the coordinate
    * is out of the framebuffer's bounds, then -1 is returned.
    * @param x the buffer element's row position.
    * @param y the buffer element's column position.
    */
   int getOffset(const double& x, const double& y) const;
   /**
    * Return the buffer offset for a given <x, y> coordinate. If the coordinate
    * is out of the framebuffer's bounds, then -1 is returned.
    * @param x the buffer element's row position.
    * @param y the buffer element's column position.
    */
   int getOffset(const uint32_t& x, const uint32_t& y) const;
   /**
    * Test if a given fragment passes all fragment tests. It will return the
    * fragment's buffer offset if the fragment passes all tests, otherwise -1.
    * @param fragment the fragment to test.
    */
   int fragmentPasses(const Fragment& fragment) const;
   /**
    * Free the memory used by the internal buffers.
    */
   void free();
};

} // namespace graphics
} // namespace clockwork
