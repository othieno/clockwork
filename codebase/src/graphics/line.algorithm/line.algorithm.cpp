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
#include "line.algorithm.hh"

using clockwork::graphics::LineAlgorithm;
using clockwork::graphics::LineAlgorithmFactory;


LineAlgorithmFactory::LineAlgorithmFactory() :
Factory(LineAlgorithm::Identifier::Bresenham)
{
   put(LineAlgorithm::Identifier::Bresenham, nullptr);
   put(LineAlgorithm::Identifier::XiaolinWu, nullptr);
//   put(LineAlgorithm::Identifier::Bresenham, new BresenhamLineAlgorithm);
//   put(LineAlgorithm::Identifier::XiaolinWu, new XiaolinWuLineAlgorithm);
}


LineAlgorithmFactory&
LineAlgorithmFactory::getInstance()
{
   static LineAlgorithmFactory INSTANCE;
   return INSTANCE;
}






















#ifdef __TO_REFACTOR
using clockwork::graphics::LineRenderAlgorithm;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;


LineRenderAlgorithm::LineRenderAlgorithm() :
RenderAlgorithm(RenderAlgorithm::Identifier::Line),
_drawline(std::bind(&LineRenderAlgorithm::drawlineBresenham, this, _1, _2, _3))
{}


clockwork::graphics::VertexArray&
LineRenderAlgorithm::clip(VertexArray& vertices) const
{
   return vertices;
}


void
LineRenderAlgorithm::rasterise(const Renderable::Uniforms& uniforms, const VertexArray& vertices) const
{
#ifdef FIXME
   auto it = vertices.begin();
   auto end = vertices.end();
   if (it != end)
   {
      if (_linePrimitive == LineRenderAlgorithm::LinePrimitive::Line)
      {
         // If the number of vertices is odd, then the extra vertex is discarded.
         end -= std::distance(it, end) & 1 ? 1 : 0;

         // Render the lines {v0, v1}, {v2, v3}, ..., {vn-1, vn}.
         while (it != end)
         {
            // Render the lines {v0, v1}, {v2, v3}, ..., {vn-1, vn}.
            const auto& a = *it++;
            const auto& b = *it++;
            _drawline(uniforms, a, b);
         }
      }
      else if (_linePrimitive == LineRenderAlgorithm::LinePrimitive::LineStrip)
      {
         // For N vertices, N - 1 lines are rendered.
         --end;
         do
         {
            // Render the lines {v0, v1}, {v1, v2}, ..., {vn-1, vn}.
            const auto& a = *it++;
            const auto& b = *it;
            _drawline(uniforms, a, b);
         } while (it != end);
      }
      else if (_linePrimitive == LineRenderAlgorithm::LinePrimitive::LineLoop)
      {
         const auto begin = it;
         // For N vertices, N - 1 lines are rendered.
         --end;
         do
         {
            // Render the lines {v0, v1}, {v1, v2}, ..., {vn-1, vn}.
            const auto& a = *it++;
            const auto& b = *it;
            _drawline(uniforms, a, b);
         } while (it != end);

         // Then render the line {vn, v0}.
         _drawline(uniforms, *it, *begin);
      }
   }
#endif
}


void
LineRenderAlgorithm::drawlineBresenham(const Renderable::Uniforms& uniforms, const Vertex& V0, const Vertex& V1) const
{
   const auto& fop = std::bind(&LineRenderAlgorithm::fragmentProgram, this, uniforms, std::placeholders::_1);
   const auto plot = [this, &fop](const Vertex& v)
   {
      this->plot(Fragment(v), fop);
   };

   const double& x0 = V0.x;
   const double& y0 = V0.y;
   const double& x1 = V1.x;
   const double& y1 = V1.y;
   const double  dx = x1 - x0;
   const double  dy = y1 - y0;

   if (!dx && dy > 0)
   {
      const auto& ymin = static_cast<uint32_t>(std::round(std::min(y0, y1)));
      const auto& ymax = static_cast<uint32_t>(std::round(std::max(y0, y1)));
      for (auto y = ymin; y <= ymax; ++y)
      {
         // Interpolate a new vertex.
         auto v = Vertex::interpolate(V0, V1, (y - y0) / dy);
         v.x = x0;
         v.y = y;

         // Plot the interpolated vertex.
         plot(v);
      }
   }
   else if (dx)
   {
      const auto& xmin = static_cast<uint32_t>(std::round(std::min(x0, x1)));
      const auto& xmax = static_cast<uint32_t>(std::round(std::max(x0, x1)));

      // Base method.
      const double m = dy / dx;
      const double b = y0 - (m * x0);

      if (std::abs(m) < 1.0)
      {
         for (auto x = xmin; x <= xmax; ++x)
         {
            // Interpolate a new vertex.
            auto v = Vertex::interpolate(V0, V1, (x - x0) / dx);
            v.x = x;
            v.y = std::round((m * x) + b);

            // Plot the interpolated fragment.
            plot(v);
         }
      }
      else
      {
         const auto& ymin = static_cast<uint32_t>(std::round(std::min(y0, y1)));
         const auto& ymax = static_cast<uint32_t>(std::round(std::max(y0, y1)));
         for (auto y = ymin; y <= ymax; ++y)
         {
            // Interpolate a new vertex.
            auto v = Vertex::interpolate(V0, V1, (y - y0) / dy);
            v.x = std::round((y - b) / m);
            v.y = y;

            // Plot the interpolated vertex.
            plot(v);
         }
      }
   }
}


void
LineRenderAlgorithm::drawlineXiaolinWu(const Renderable::Uniforms&, const Vertex& V0, const Vertex& V1) const
{
   // Plot a color at the given <X, Y> coordinates.
   const auto plotxy = [this](const uint32_t& x, const uint32_t& y, const double& intensity)
   {
      this->plot(x, y, 0.0, ColorRGBA(intensity, intensity, intensity));
   };

   // fpart returns the fractional part of a floating point number.
   const auto fpart = [](const double& x) -> double
   {
      return std::fmod(x, 1.0);
   };

   // ipart returns the integer part of a floating-point number.
   // Taken from http://stackoverflow.com/a/343602.
   const auto ipart = [&fpart](const double& x) -> int
   {
      return static_cast<int>(x - fpart(x));
   };

   // rfpart returns the reverse of fpart.
   const auto rfpart = [&fpart](const double& x) -> double
   {
      return 1.0 - fpart(x);
   };

   // round rounds off a floating-point value.
   const auto round = [&ipart](const double& x) -> int
   {
      return ipart(x + 0.5);
   };

   double x0 = V0.x;
   double y0 = V0.y;
   double x1 = V1.x;
   double y1 = V1.y;

   const double dx = x1 - x0;
   const double dy = y1 - y0;

   if (std::abs(dx) > std::abs(dy))
   {
      if (x0 > x1)
      {
         std::swap(x0, x1);
         std::swap(y0, y1);
      }

      const double m = dy / dx;

      auto xend = round(x0);
      double yend = y0 + (m * (xend - x0));
      double xgap = rfpart(x0 + 0.5);
      const auto xpxl1 = xend;
      const auto ypxl1 = ipart(yend);
      plotxy(xpxl1, ypxl1, rfpart(yend) * xgap);
      plotxy(xpxl1, ypxl1 + 1, fpart(yend) * xgap);

      double intery = yend + m;
      xend = round(x1);
      yend = y1 + (m * (xend - x1));
      xgap = fpart(x1 + 0.5);
      const auto xpxl2 = xend;
      const auto ypxl2 = ipart(yend);
      plotxy(xpxl2, ypxl2, rfpart(yend) * xgap);
      plotxy(xpxl2, ypxl2 + 1, fpart(yend) * xgap);

      for(auto x = xpxl1 + 1; x <= (xpxl2 - 1); ++x)
      {
         const auto y = ipart(intery);
         plotxy(x, y, rfpart(intery));
         plotxy(x, y + 1, fpart(intery));
         intery += m;
      }
   }
   else
   {
      if (y0 > y1)
      {
         std::swap(x0, x1);
         std::swap(y0, y1);
      }

      const double m = dx / dy;

      auto yend = round(y0);
      double xend = x0 + (m * (yend - y0));
      double ygap = rfpart(y0 + 0.5);
      const auto ypxl1 = yend;
      const auto xpxl1 = ipart(xend);
      plotxy(xpxl1, ypxl1, rfpart(xend) * ygap);
      plotxy(xpxl1, ypxl1 + 1, fpart(xend) * ygap);

      double interx = xend + m;
      yend = round(y1);
      xend = x1 + (m * (yend - y1));
      ygap = fpart(y1 + 0.5);
      int ypxl2 = yend;
      int xpxl2 = ipart(xend);
      plotxy(xpxl2, ypxl2, rfpart(xend) * ygap);
      plotxy(xpxl2, ypxl2 + 1, fpart(xend) * ygap);

      for(int y = ypxl1 + 1; y <= (ypxl2 - 1); y++)
      {
         const auto x = ipart(interx);
         plotxy(x, y, rfpart(interx));
         plotxy(x + 1, y, fpart(interx));
         interx += m;
      }
   }
}
#endif
