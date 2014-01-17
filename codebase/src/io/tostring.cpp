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
#include "tostring.hh"


QString
clockwork::toString(const clockwork::Error& error)
{
   QString output("Error: ");
   switch (error)
   {
      case clockwork::Error::None:
         output.append("None");
         break;
      case clockwork::Error::Unknown:
      default:
         output.append("???");
         break;
   }
   return output;
}


QString
clockwork::toString(const clockwork::graphics::Projection::Type& type)
{
   switch (type)
   {
      case clockwork::graphics::Projection::Type::Orthographic:
         return "Orthographic";
      case clockwork::graphics::Projection::Type::Cabinet:
         return "Cabinet";
      case clockwork::graphics::Projection::Type::Cavalier:
         return "Cavalier";
      case clockwork::graphics::Projection::Type::Perspective:
         return "Perspective";
      default:
         return "Unknown projection";
   }
}


QString
clockwork::toString(const clockwork::graphics::ImageFilter::Type& type)
{
   switch (type)
   {
      case clockwork::graphics::ImageFilter::Type::None:
         return "None";
      case clockwork::graphics::ImageFilter::Type::BlackAndWhite:
         return "Black & White";
      case clockwork::graphics::ImageFilter::Type::Grayscale:
         return "Grayscale";
      default:
         return "Unknown image filter";
   }
}


QString
clockwork::toString(const clockwork::graphics::TextureFilter::Type& type)
{
   switch (type)
   {
      case clockwork::graphics::TextureFilter::Type::None:
         return "None";
      case clockwork::graphics::TextureFilter::Type::Bilinear:
         return "Bilinear";
      case clockwork::graphics::TextureFilter::Type::Trilinear:
         return "Trilinear";
      case clockwork::graphics::TextureFilter::Type::Anisotropic:
         return "Anisotropic";
      default:
         return "Unknown texture filter";
   }
}


QString
clockwork::toString(const clockwork::graphics::WireframeRenderParameters::LineAlgorithm& algorithm)
{
   switch (algorithm)
   {
      case clockwork::graphics::WireframeRenderParameters::LineAlgorithm::Bresenham:
         return "Bresenham";
      case clockwork::graphics::WireframeRenderParameters::LineAlgorithm::XiaolinWu:
         return "Xiaolin Wu";
      default:
         return "Unknown line algorithm";
   }
}


QString
clockwork::toString(const clockwork::graphics::RenderParameters::Type& type)
{
   switch (type)
   {
      case clockwork::graphics::RenderParameters::Type::Point:
         return "Points";
      case clockwork::graphics::RenderParameters::Type::Wireframe:
         return "Wireframe";
      case clockwork::graphics::RenderParameters::Type::Random:
         return "Random shading";
      case clockwork::graphics::RenderParameters::Type::Depth:
         return "Depth shading";
      case clockwork::graphics::RenderParameters::Type::Normals:
         return "Normals shading";
      case clockwork::graphics::RenderParameters::Type::Texture:
         return "Texture mapping";
      case clockwork::graphics::RenderParameters::Type::Constant:
         return "Constant shading";
      case clockwork::graphics::RenderParameters::Type::Phong:
         return "Phong shading";
      case clockwork::graphics::RenderParameters::Type::Cel:
         return "Cel shading";
      case clockwork::graphics::RenderParameters::Type::Bump:
         return "Bump mapping";
      case clockwork::graphics::RenderParameters::Type::Deferred:
         return "Deferred shading";
      default:
         return "Unknown render type";
   }
}


QString
clockwork::toString(const clockwork::graphics::Fragment&)
{
   return "Implement clockwork::toString(const clockwork::graphics::Fragment&)";
}


QString
clockwork::toString(const clockwork::graphics::Framebuffer&)
{
   return "Implement clockwork::toString(const clockwork::graphics::Framebuffer&)";
}


QString
clockwork::toString(const clockwork::graphics::Framebuffer::Resolution& resolution)
{
   switch (resolution)
   {
      case clockwork::graphics::Framebuffer::Resolution::VGA:
         return "VGA (640x480)";
      case clockwork::graphics::Framebuffer::Resolution::SVGA:
         return "SVGA (800x600)";
      case clockwork::graphics::Framebuffer::Resolution::XGA:
         return "XGA (1024x768)";
      case clockwork::graphics::Framebuffer::Resolution::SXGA:
         return "SXGA (1280x1024)";
      case clockwork::graphics::Framebuffer::Resolution::FHD:
         return "FHD (1920x1080)";
      case clockwork::graphics::Framebuffer::Resolution::QSXGA:
         return "QSXGA (2560x2048)";
      case clockwork::graphics::Framebuffer::Resolution::UHD8K:
         return "8K UHD (7680x4320)";
      default:
         return "Unknown resolution";
   }
}
