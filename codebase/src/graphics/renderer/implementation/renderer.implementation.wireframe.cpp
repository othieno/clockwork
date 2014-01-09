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
#include "renderer.implementation.wireframe.hh"
#include "wireframe.render.task.hh"
#include "services.hh"


clockwork::graphics::WireframeRenderer::WireframeRenderer() :
Renderer(clockwork::graphics::Renderer::Type::Wireframe),
_lineAlgorithm(clockwork::graphics::WireframeRenderer::LineAlgorithm::XiaolinWu)
{}


const clockwork::graphics::WireframeRenderer::LineAlgorithm&
clockwork::graphics::WireframeRenderer::getLineAlgorithm() const
{
	return _lineAlgorithm;
}


std::list<clockwork::graphics::WireframeRenderer::LineAlgorithm>
clockwork::graphics::WireframeRenderer::getLineAlgorithmList() const
{
	return
	{
		clockwork::graphics::WireframeRenderer::LineAlgorithm::Bresenham,
		clockwork::graphics::WireframeRenderer::LineAlgorithm::XiaolinWu,
	};
}


void
clockwork::graphics::WireframeRenderer::setLineAlgorithm(const clockwork::graphics::WireframeRenderer::LineAlgorithm& algorithm)
{
	_lineAlgorithm = algorithm;
}


clockwork::concurrency::RenderTask*
clockwork::graphics::WireframeRenderer::createRenderTask
(
	const clockwork::physics::RigidBody& body,
	const clockwork::scene::Viewer& viewer
) const
{
	using std::placeholders::_1;
	using std::placeholders::_2;
	using clockwork::graphics::Fragment;

	// Get the current drawline function.
	std::function<void(const Fragment&, const Fragment&)> drawline;
	if (_lineAlgorithm == LineAlgorithm::Bresenham)
		drawline = std::bind(&WireframeRenderer::drawlineBresenham, this, _1, _2);
	else if (_lineAlgorithm == LineAlgorithm::XiaolinWu)
		drawline = std::bind(&WireframeRenderer::drawlineXiaolinWu, this, _1, _2);
	else
		return nullptr;

	return new clockwork::concurrency::WireframeRenderTask(body, viewer, drawline);
}


void
clockwork::graphics::WireframeRenderer::drawlineBresenham
(
	const clockwork::graphics::Fragment& f0,
	const clockwork::graphics::Fragment& f1
) const
{
	auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();
	const auto plot = [&framebuffer](const clockwork::graphics::Fragment& f)
	{
		framebuffer.plot(f.x, f.y, f.z, f.color.merge());
	};

	const double dx = f1.x - f0.x;
	const double dy = f1.y - f0.y;

	// Base method.
	const double slope = dy / dx;
	const double b = f0.y - (slope * f0.x);

	// Plot the origin.
	plot(f0);

	if (dx == 0)
	{
		const auto ymin = static_cast<int>(std::round(std::min(f0.y, f1.y)));
		const auto ymax = static_cast<int>(std::round(std::max(f0.y, f1.y)));

		for (auto y = ymin; y <= ymax; ++y)
		{
			// Interpolate a new fragment.
			const auto interpolant = (dy != 0) ? static_cast<double>((y - f0.y) / dy) : 0;
			auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, interpolant);
			fi.x = f0.x;
			fi.y = y;

			// Plot the interpolated fragment.
			plot(fi);
		}
	}
	else if (std::abs(slope) < 1)
	{
		const auto xmin = static_cast<int>(std::round(std::min(f0.x, f1.x)));
		const auto xmax = static_cast<int>(std::round(std::max(f0.x, f1.x)));

		for (auto x = xmin; x <= xmax; ++x)
		{
			// Interpolate a new fragment.
			const auto interpolant = (dx != 0) ? static_cast<double>((x - f0.x) / dx) : 0;
			auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, interpolant);
			fi.x = x;
			fi.y = (slope * x) + b;

			// Plot the interpolated fragment.
			plot(fi);
		}
	}
	else
	{
		const auto ymin = static_cast<int>(std::round(std::min(f0.y, f1.y)));
		const auto ymax = static_cast<int>(std::round(std::max(f0.y, f1.y)));

		for (auto y = ymin; y <= ymax; ++y)
		{
			// Interpolate a new fragment.
			const auto interpolant = (dy != 0) ? static_cast<double>((y - f0.y) / dy) : 0;
			auto fi = clockwork::graphics::Fragment::interpolate(f0, f1, interpolant);
			fi.x = (y - b) / slope;
			fi.y = y;

			// Plot the interpolated fragment.
			plot(fi);
		}
	}
}


void
clockwork::graphics::WireframeRenderer::drawlineXiaolinWu
(
	const clockwork::graphics::Fragment& f0,
	const clockwork::graphics::Fragment& f1
) const
{
	auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();
	const auto plot = [&framebuffer](const int& x, const int& y, const double& intensity)
	{
		framebuffer.plot(x, y, 0, mergeColorChannels(1.0, intensity, intensity, intensity));
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

	double x1 = f0.x;
	double y1 = f0.y;
	double x2 = f1.x;
	double y2 = f1.y;

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
		plot(xpxl1, ypxl1, rfpart(yend) * xgap);
		plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
		double intery = yend + gradient;

		xend = round(x2);
		yend = y2 + (gradient * (xend - x2));
		xgap = fpart(x2 + 0.5);
		const int xpxl2 = xend;
		const int ypxl2 = ipart(yend);
		plot(xpxl2, ypxl2, rfpart(yend) * xgap);
		plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);

		for(auto x = xpxl1 + 1; x <= (xpxl2 - 1); ++x)
		{
			plot(x, ipart(intery), rfpart(intery));
			plot(x, ipart(intery) + 1, fpart(intery));
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
		plot(xpxl1, ypxl1, rfpart(xend) * ygap);
		plot(xpxl1, ypxl1 + 1, fpart(xend) * ygap);
		double interx = xend + gradient;

		yend = round(y2);
		xend = x2 + (gradient * (yend - y2));
		ygap = fpart(y2 + 0.5);
		int ypxl2 = yend;
		int xpxl2 = ipart(xend);
		plot(xpxl2, ypxl2, rfpart(xend) * ygap);
		plot(xpxl2, ypxl2 + 1, fpart(xend) * ygap);

		for(int y=ypxl1+1; y <= (ypxl2-1); y++)
		{
			plot(ipart(interx), y, rfpart(interx));
			plot(ipart(interx) + 1, y, fpart(interx));
			interx += gradient;
		}
	}
}
