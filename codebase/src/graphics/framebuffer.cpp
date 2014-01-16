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
#include "framebuffer.hh"
#include "services.hh"
#include <limits>


clockwork::graphics::Framebuffer::Framebuffer(const uint32_t& width, const uint32_t& height) :
_width(0),
_height(0),
_pixelBuffer(nullptr),
_pixelBufferClearValue(0xff000000),
_depthBuffer(nullptr),
_depthBufferClearValue(std::numeric_limits<double>::max()),
_stencilBuffer(nullptr),
_stencilBufferClearValue(0),
_accumulationBuffer(nullptr),
_accumulationBufferClearValue(0xff000000)
{
   // Resize all buffers and initialise them for use.
   resize(width, height);
}


clockwork::graphics::Framebuffer::~Framebuffer()
{
   free();
}


const uint32_t*
clockwork::graphics::Framebuffer::getPixelBuffer() const
{
   return _pixelBuffer;
}


const uint32_t&
clockwork::graphics::Framebuffer::getPixelBufferClearValue() const
{
   return _pixelBufferClearValue;
}


void
clockwork::graphics::Framebuffer::setPixelBufferClearValue(const uint32_t& value)
{
   _pixelBufferClearValue = value;
}


const double*
clockwork::graphics::Framebuffer::getDepthBuffer() const
{
   return _depthBuffer;
}


const double&
clockwork::graphics::Framebuffer::getDepthBufferClearValue() const
{
   return _depthBufferClearValue;
}


void
clockwork::graphics::Framebuffer::setDepthBufferClearValue(const double& value)
{
   _depthBufferClearValue = value;
}


const uint8_t*
clockwork::graphics::Framebuffer::getStencilBuffer() const
{
   return _stencilBuffer;
}


const uint8_t&
clockwork::graphics::Framebuffer::getStencilBufferClearValue() const
{
   return _stencilBufferClearValue;
}


void
clockwork::graphics::Framebuffer::setStencilBufferClearValue(const uint8_t& value)
{
   _stencilBufferClearValue = value;
}


const uint32_t*
clockwork::graphics::Framebuffer::getAccumulationBuffer() const
{
   return _accumulationBuffer;
}


const uint32_t&
clockwork::graphics::Framebuffer::getAccumulationBufferClearValue() const
{
   return _accumulationBufferClearValue;
}


void
clockwork::graphics::Framebuffer::setAccumulationBufferClearValue(const uint32_t& value)
{
   _accumulationBufferClearValue = value;
}


void
clockwork::graphics::Framebuffer::plot
(
   const clockwork::graphics::Fragment& fragment,
   const std::function<uint32_t(const clockwork::graphics::Fragment&)>& fop
)
{
   const auto offset = fragmentPasses(fragment);
   if (offset >= 0)
   {
      _pixelBuffer[offset] = fop(fragment);
      _depthBuffer[offset] = fragment.position.z;
      _accumulationBuffer[offset] = _accumulationBufferClearValue;
      _stencilBuffer[offset] = fragment.stencil;
   }
}


void
clockwork::graphics::Framebuffer::plot
(
   const uint32_t& x,
   const uint32_t& y,
   const double& z,
   const uint32_t& pixel
)
{
   const auto offset = getOffset(x, y);
   if (offset >= 0)
   {
      _pixelBuffer[offset] = pixel;
      _depthBuffer[offset] = z;
      _stencilBuffer[offset] = _stencilBufferClearValue;
      _accumulationBuffer[offset] = _accumulationBufferClearValue;
   }
}


const uint32_t&
clockwork::graphics::Framebuffer::getWidth() const
{
   return _width;
}


const uint32_t&
clockwork::graphics::Framebuffer::getHeight() const
{
   return _height;
}


void
clockwork::graphics::Framebuffer::clear()
{
   for (uint32_t i = 0; i < _width * _height; ++i)
   {
      _pixelBuffer[i] = _pixelBufferClearValue;
      _depthBuffer[i] = _depthBufferClearValue;
      _stencilBuffer[i] = _stencilBufferClearValue;
      _accumulationBuffer[i] = _accumulationBufferClearValue;
   }
}


void
clockwork::graphics::Framebuffer::resize(const uint32_t& w, const uint32_t& h)
{
   if (_width != w && _height != h)
   {
      _width = w;
      _height = h;
      const auto length = w * h;

      // Dispose of the previous buffers and create new ones.
      free();
      if (length > 0)
      {
         _pixelBuffer = new uint32_t[length];
         _depthBuffer = new double[length];
         _stencilBuffer = new uint8_t[length];
         _accumulationBuffer = new uint32_t[length];
      }

      // Initialise the buffers.
      clear();
   }
}


void
clockwork::graphics::Framebuffer::discard(const uint32_t& x, const uint32_t& y)
{
   const auto offset = getOffset(x, y);
   if (offset >= 0)
   {
      _pixelBuffer[offset] = _pixelBufferClearValue;
      _depthBuffer[offset] = _depthBufferClearValue;
      _stencilBuffer[offset] = _stencilBufferClearValue;
      _accumulationBuffer[offset] = _accumulationBufferClearValue;
   }
}


std::string
clockwork::graphics::Framebuffer::toString(const clockwork::graphics::Framebuffer&)
{
   return "Implement clockwork::graphics::Framebuffer::toString";
}


int
clockwork::graphics::Framebuffer::getOffset(const uint32_t& x, const uint32_t& y) const
{
   return (x < _width && y < _height) ? x + (y * _width) : -1;
}


int
clockwork::graphics::Framebuffer::getOffset(const double& x, const double& y) const
{
   if (x > 0 && y > 0)
   {
      const uint32_t xw = static_cast<uint32_t>(std::lround(x));
      const uint32_t yw = static_cast<uint32_t>(std::lround(y));

      return getOffset(xw, yw);
   }
   else
      return -1;
}


int
clockwork::graphics::Framebuffer::fragmentPasses(const clockwork::graphics::Fragment& fragment) const
{
   const uint32_t xw = static_cast<uint32_t>(std::lround(fragment.position.x));
   const uint32_t yw = static_cast<uint32_t>(std::lround(fragment.position.y));

   const auto offset = getOffset(xw, yw);
   if (offset >= 0)
   {
      using clockwork::system::Services;

      if (Services::Graphics.isScissorTestEnabled())
         return -1;

      if (Services::Graphics.isAlphaTestEnabled())
         return -1;

      if (Services::Graphics.isStencilTestEnabled())
         return -1;

      if (Services::Graphics.isDepthTestEnabled() && !(fragment.position.z < _depthBuffer[offset]))
         return -1;
   }
   return offset;
}


void
clockwork::graphics::Framebuffer::free()
{
   if (_pixelBuffer != nullptr)
   {
      delete _pixelBuffer;
      _pixelBuffer = nullptr;
   }

   if (_depthBuffer != nullptr)
   {
      delete _depthBuffer;
      _depthBuffer = nullptr;
   }

   if (_stencilBuffer != nullptr)
   {
      delete _stencilBuffer;
      _stencilBuffer = nullptr;
   }

   if (_accumulationBuffer != nullptr)
   {
      delete _accumulationBuffer;
      _accumulationBuffer = nullptr;
   }
}
