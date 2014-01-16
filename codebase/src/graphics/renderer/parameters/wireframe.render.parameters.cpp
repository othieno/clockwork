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
#include "wireframe.render.parameters.hh"
#include "numerical.hh"

using clockwork::graphics::WireframeRenderParameters;


WireframeRenderParameters::WireframeRenderParameters() :
RenderParameters(RenderParameters::Type::Wireframe),
_lineAlgorithm(WireframeRenderParameters::LineAlgorithm::Bresenham),
drawline(std::bind(&WireframeRenderParameters::drawlineBresenham, this, std::placeholders::_1, std::placeholders::_2))
{
	setLineAlgorithm(WireframeRenderParameters::LineAlgorithm::XiaolinWu);
}


QList<WireframeRenderParameters::LineAlgorithm>
WireframeRenderParameters::getLineAlgorithms()
{
	QList<WireframeRenderParameters::LineAlgorithm> output =
	{
		WireframeRenderParameters::LineAlgorithm::Bresenham,
		WireframeRenderParameters::LineAlgorithm::XiaolinWu
	};
	return output;
}


const WireframeRenderParameters::LineAlgorithm&
WireframeRenderParameters::getLineAlgorithm() const
{
	return _lineAlgorithm;
}


void
WireframeRenderParameters::setLineAlgorithm(const WireframeRenderParameters::LineAlgorithm& algorithm)
{
	if (_lineAlgorithm != algorithm)
	{
		_lineAlgorithm = algorithm;
		switch (_lineAlgorithm)
		{
			using namespace std::placeholders;

			case WireframeRenderParameters::LineAlgorithm::Bresenham:
				drawline = std::bind(&WireframeRenderParameters::drawlineBresenham, this, _1, _2);
				break;
			case WireframeRenderParameters::LineAlgorithm::XiaolinWu:
				drawline = std::bind(&WireframeRenderParameters::drawlineXiaolinWu, this, _1, _2);
				break;
			default:
				break;
		}
	}
}


void
WireframeRenderParameters::primitiveAssembly(const std::array<const Fragment*, 3>& triangle) const
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		auto* const f0 = triangle[i];
		auto* const f1 = triangle[(i + 1) % 3];

		if (f0 != nullptr && f1 != nullptr)
			drawline(*f0, *f1);
	}
}


void
WireframeRenderParameters::drawlineBresenham(const Fragment& f0, const Fragment& f1) const
{
	const double& x0 = f0.position.x;
	const double& y0 = f0.position.y;
	const double& x1 = f1.position.x;
	const double& y1 = f1.position.y;

	const double dx = x1 - x0;
	const double dy = y1 - y0;

	// Plot the origin.
	plot(f0);

	if (dx == 0.0 && dy > 0.0)
	{
		const auto ymin = std::round(std::min(y0, y1));
		const auto ymax = std::round(std::max(y0, y1));

		for (auto y = ymin; y <= ymax; ++y)
		{
			// Interpolate a new fragment.
			const double p = (static_cast<double>(y) - y0) / dy;
			auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, p);
			fi.position.x = x0;
			fi.position.y = y;

			// Plot the interpolated fragment.
			plot(fi);
		}
	}
	else if (dx != 0.0)
	{
		// Base method.
		const double slope = dy / dx;
		const double b = y0 - (slope * x0);

		if (std::abs(slope) < 1)
		{
			const auto xmin = std::round(std::min(x0, x1));
			const auto xmax = std::round(std::max(x0, x1));

			for (auto x = xmin; x <= xmax; ++x)
			{
				// Interpolate a new fragment.
				const double p = (static_cast<double>(x) - x0) / dx;
				auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, p);
				fi.position.x = x;
				fi.position.y = (slope * x) + b;

				// Plot the interpolated fragment.
				plot(fi);
			}
		}
		else
		{
			const auto ymin = std::round(std::min(y0, y1));
			const auto ymax = std::round(std::max(y0, y1));

			for (auto y = ymin; y <= ymax; ++y)
			{
				// Interpolate a new fragment.
				const double p = (static_cast<double>(y) - y0) / dy;
				auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, p);
				fi.position.x = (y - b) / slope;
				fi.position.y = y;

				// Plot the interpolated fragment.
				plot(fi);
			}
		}
	}
}


void
WireframeRenderParameters::drawlineXiaolinWu(const Fragment& f0, const Fragment& f1) const
{
	const auto _plot = [this](const uint32_t& x, const uint32_t& y, const double& intensity)
	{
		plot(x, y, 0.0, ColorRGBA(intensity, intensity, intensity).merge());
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

	double x1 = f0.position.x;
	double y1 = f0.position.y;
	double x2 = f1.position.x;
	double y2 = f1.position.y;

	double dx = x2 - x1;
	double dy = y2 - y1;

	if (std::abs(dx) > std::abs(dy))
	{
		if (x2 < x1)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const double gradient = dy / dx;
		int xend = round(x1);
		double yend = y1 + (gradient * (xend - x1));
		double xgap = rfpart(x1 + 0.5);


		const int xpxl1 = xend;
		const int ypxl1 = ipart(yend);
		_plot(xpxl1, ypxl1, rfpart(yend) * xgap);
		_plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
		double intery = yend + gradient;

		xend = round(x2);
		yend = y2 + (gradient * (xend - x2));
		xgap = fpart(x2 + 0.5);
		const int xpxl2 = xend;
		const int ypxl2 = ipart(yend);
		_plot(xpxl2, ypxl2, rfpart(yend) * xgap);
		_plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);

		for(auto x = xpxl1 + 1; x <= (xpxl2 - 1); ++x)
		{
			_plot(x, ipart(intery), rfpart(intery));
			_plot(x, ipart(intery) + 1, fpart(intery));
			intery += gradient;
		}
	}
	else
	{
		if (y2 < y1)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		double gradient = dx / dy;
		int yend = round(y1);
		double xend = x1 + (gradient * (yend - y1));
		double ygap = rfpart(y1 + 0.5);

		int ypxl1 = yend;
		int xpxl1 = ipart(xend);
		_plot(xpxl1, ypxl1, rfpart(xend) * ygap);
		_plot(xpxl1, ypxl1 + 1, fpart(xend) * ygap);
		double interx = xend + gradient;

		yend = round(y2);
		xend = x2 + (gradient * (yend - y2));
		ygap = fpart(y2 + 0.5);
		int ypxl2 = yend;
		int xpxl2 = ipart(xend);
		_plot(xpxl2, ypxl2, rfpart(xend) * ygap);
		_plot(xpxl2, ypxl2 + 1, fpart(xend) * ygap);

		for(int y=ypxl1+1; y <= (ypxl2-1); y++)
		{
			_plot(ipart(interx), y, rfpart(interx));
			_plot(ipart(interx) + 1, y, fpart(interx));
			interx += gradient;
		}
	}
}
