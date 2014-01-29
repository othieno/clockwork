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

using clockwork::graphics::Framebuffer;


Framebuffer::Framebuffer(const Framebuffer::Resolution& resolution) :
_width(0),
_height(0),
_pixelBuffer(nullptr),
_pixelBufferClearValue(0xff000000),
_depthBuffer(nullptr),
_depthBufferClearValue(std::numeric_limits<double>::max()),
_stencilBuffer(nullptr),
_stencilBufferClearValue(0),
_accumulationBuffer(nullptr),
_accumulationBufferClearValue(0xff000000),
_ignoreWrites(true)
{
   // Resize all buffers and initialise them for use.
   resize(resolution, true);
}


Framebuffer::~Framebuffer()
{
   free();
}


const uint32_t*
Framebuffer::getPixelBuffer() const
{
   return _pixelBuffer;
}


const uint32_t&
Framebuffer::getPixelBufferClearValue() const
{
   return _pixelBufferClearValue;
}


void
Framebuffer::setPixelBufferClearValue(const uint32_t& value)
{
   _pixelBufferClearValue = value;
}


const double*
Framebuffer::getDepthBuffer() const
{
   return _depthBuffer;
}


const double&
Framebuffer::getDepthBufferClearValue() const
{
   return _depthBufferClearValue;
}


void
Framebuffer::setDepthBufferClearValue(const double& value)
{
   _depthBufferClearValue = value;
}


const uint8_t*
Framebuffer::getStencilBuffer() const
{
   return _stencilBuffer;
}


const uint8_t&
Framebuffer::getStencilBufferClearValue() const
{
   return _stencilBufferClearValue;
}


void
Framebuffer::setStencilBufferClearValue(const uint8_t& value)
{
   _stencilBufferClearValue = value;
}


const uint32_t*
Framebuffer::getAccumulationBuffer() const
{
   return _accumulationBuffer;
}


const uint32_t&
Framebuffer::getAccumulationBufferClearValue() const
{
   return _accumulationBufferClearValue;
}


void
Framebuffer::setAccumulationBufferClearValue(const uint32_t& value)
{
   _accumulationBufferClearValue = value;
}


void
Framebuffer::plot(const Fragment& fragment, const std::function<uint32_t(const Fragment&)>& fop)
{
   if (_ignoreWrites)
      return;

   const auto offset = fragmentPasses(fragment);
   if (offset >= 0)
   {
      _pixelBuffer[offset] = fop(fragment);
      _depthBuffer[offset] = fragment.z;
      _accumulationBuffer[offset] = _accumulationBufferClearValue;
      _stencilBuffer[offset] = fragment.stencil;
   }
}


void
Framebuffer::plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t& pixel)
{
   if (_ignoreWrites)
      return;

   const auto offset = getOffset(x, y);
   if (offset >= 0)
   {
      _pixelBuffer[offset] = pixel;
      _depthBuffer[offset] = z;
      _stencilBuffer[offset] = _stencilBufferClearValue;
      _accumulationBuffer[offset] = _accumulationBufferClearValue;
   }
}


const Framebuffer::Resolution&
Framebuffer::getResolution() const
{
   return _resolution;
}


const uint32_t&
Framebuffer::getWidth() const
{
   return _width;
}


const uint32_t&
Framebuffer::getHeight() const
{
   return _height;
}


void
Framebuffer::clear()
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
Framebuffer::resize(const Framebuffer::Resolution& resolution, const bool& force)
{
   if (_resolution == resolution && !force)
      return;

   _resolution = resolution;

   switch (_resolution)
   {
      case Framebuffer::Resolution::VGA:
         _width = 640;
         _height = 480;
         break;
      case Framebuffer::Resolution::XGA:
         _width = 1024;
         _height = 768;
         break;
      case Framebuffer::Resolution::SXGA:
         _width = 1280;
         _height = 1024;
         break;
      case Framebuffer::Resolution::FHD:
         _width = 1920;
         _height = 1080;
         break;
      case Framebuffer::Resolution::QSXGA:
         _width = 2560;
         _height = 2048;
         break;
      case Framebuffer::Resolution::UHD8K:
         _width = 7680;
         _height = 4320;
         break;
      case Framebuffer::Resolution::SVGA:
      default:
         _width = 800;
         _height = 600;
         _resolution = Framebuffer::Resolution::SVGA;
         break;
   }

   // Resize the arrays with the new height. First make sure the framebuffer is readable only.
   _ignoreWrites = true;

   const auto length = _width * _height;

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

   // Make the framebuffer writable.
   _ignoreWrites = false;
}


void
Framebuffer::discard(const uint32_t& x, const uint32_t& y)
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


int
Framebuffer::getOffset(const uint32_t& x, const uint32_t& y) const
{
   return (x < _width && y < _height) ? x + (y * _width) : -1;
}


int
Framebuffer::fragmentPasses(const Fragment& fragment) const
{
   const auto offset = getOffset(fragment.x, fragment.y);
   if (offset >= 0)
   {
      using clockwork::system::Services;

      if (Services::Graphics.isScissorTestEnabled())
         return -1;

      if (Services::Graphics.isAlphaTestEnabled())
         return -1;

      if (Services::Graphics.isStencilTestEnabled())
         return -1;

      if (Services::Graphics.isDepthTestEnabled() && !(fragment.z < _depthBuffer[offset]))
         return -1;
   }
   return offset;
}


void
Framebuffer::free()
{
   // There're no buffers to write to.
   _ignoreWrites = true;

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



QList<Framebuffer::Resolution>
Framebuffer::getResolutions()
{
   return
   {
      Framebuffer::Resolution::VGA,
      Framebuffer::Resolution::SVGA,
      Framebuffer::Resolution::XGA,
      Framebuffer::Resolution::SXGA,
      Framebuffer::Resolution::FHD,
      Framebuffer::Resolution::QSXGA,
      Framebuffer::Resolution::UHD8K
   };
}
