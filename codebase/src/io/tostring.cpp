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
clockwork::toString(const clockwork::graphics::LineAlgorithm::Identifier& identifier)
{
   switch (identifier)
   {
      case clockwork::graphics::LineAlgorithm::Identifier::Bresenham:
         return "Bresenham";
      case clockwork::graphics::LineAlgorithm::Identifier::XiaolinWu:
         return "Xiaolin Wu";
      default:
         return "Unknown line algorithm";
   }
}


QString
clockwork::toString(const clockwork::graphics::PrimitiveMode::Identifier& identifier)
{
   switch (identifier)
   {
      case clockwork::graphics::PrimitiveMode::Identifier::Points:
         return "Points";
      case clockwork::graphics::PrimitiveMode::Identifier::Lines:
         return "Lines";
      case clockwork::graphics::PrimitiveMode::Identifier::LineStrip:
         return "Line Strip";
      case clockwork::graphics::PrimitiveMode::Identifier::LineLoop:
         return "Line Loop";
      case clockwork::graphics::PrimitiveMode::Identifier::Triangles:
         return "Triangles";
      case clockwork::graphics::PrimitiveMode::Identifier::TriangleStrip:
         return "Triangle Strip";
      case clockwork::graphics::PrimitiveMode::Identifier::TriangleFan:
         return "Triangle Fan";
      default:
         return "Unknown primitive mode";
   }
}


QString
clockwork::toString(const clockwork::graphics::RenderAlgorithm::Identifier& identifier)
{
   switch (identifier)
   {
      case clockwork::graphics::RenderAlgorithm::Identifier::Point:
         return "Points";
      case clockwork::graphics::RenderAlgorithm::Identifier::Wireframe:
         return "Wireframe";
      case clockwork::graphics::RenderAlgorithm::Identifier::Random:
         return "Random";
      case clockwork::graphics::RenderAlgorithm::Identifier::Depth:
         return "Depth Map";
      case clockwork::graphics::RenderAlgorithm::Identifier::Normals:
         return "Normal Map";
      case clockwork::graphics::RenderAlgorithm::Identifier::Texture:
         return "Texture Map";
      case clockwork::graphics::RenderAlgorithm::Identifier::Constant:
         return "Constant Shading";
      case clockwork::graphics::RenderAlgorithm::Identifier::Phong:
         return "Phong Shading";
      case clockwork::graphics::RenderAlgorithm::Identifier::Cel:
         return "Cel Shading";
      case clockwork::graphics::RenderAlgorithm::Identifier::Bump:
         return "Bump Map";
      case clockwork::graphics::RenderAlgorithm::Identifier::Deferred:
         return "Deferred Shading";
      default:
         return "Unknown render type";
   }
}


QString
clockwork::toString(const clockwork::graphics::Fragment& f)
{
   std::stringstream stream;
   stream.precision(3);
   stream << "fragment: <" << f.x << ", " << f.y << ", " << f.z << ">";

   return QString(stream.str().c_str());
}


QString
clockwork::toString(const clockwork::graphics::Vertex& v)
{
   std::stringstream stream;
   stream.precision(3);
   stream << "vertex: <" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ">";

   return QString(stream.str().c_str());
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


QString
clockwork::toString(const clockwork::graphics::Viewport& vp)
{
   std::stringstream stream;
   stream.precision(2);
   stream << "viewport (x, y, width, height, near, far): <"
   << vp.x << ", " << vp.y << ", " << vp.width << ", " << vp.height << ", " << vp.near << ", " << vp.far << ">";

   return QString(stream.str().c_str());
}
