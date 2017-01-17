/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#include "WireframeRenderer.hh"

using clockwork::WireframeRenderer;


void
WireframeRenderer::sanitizeRenderingContext(RenderingContext& context) {
	// The Wireframe renderer only draws line primitives so if the primitive topology
	// is not set to Line, LineStrip or LineLoop, it will be set to LineLoop.
	auto& t = context.primitiveTopology;
	if (t != PrimitiveTopology::Line && t != PrimitiveTopology::LineStrip && t != PrimitiveTopology::LineLoop) {
		t = PrimitiveTopology::LineLoop;
	}
}


void
WireframeRenderer::primitiveAssembly(const RenderingContext&, VertexArray&) {}


void
WireframeRenderer::clip(const RenderingContext&, VertexArray&) {}


void
WireframeRenderer::rasterize(
	const RenderingContext& context,
	const VertexArray& vertices,
	Framebuffer& framebuffer
) {
	// Determine the number of primitives based on the current topology. Initially,
	// let's assume the topology is set to line loops.
	std::size_t primitiveCount = vertices.size();
	std::size_t step = 1;

	if (context.primitiveTopology != PrimitiveTopology::LineLoop) {
		return;
		switch (context.primitiveTopology) {
			case PrimitiveTopology::Line:
				// In the case of Line primitives, the number of primitives must be
				// even to prevent accessing data out of the primitives array. If
				// the number of primitives is odd, the last primitive is discared.
				primitiveCount &= ~1;
				step = 2;
				break;
			case PrimitiveTopology::LineStrip:
				primitiveCount--;
				break;
			default:
				qFatal("[WireframeRenderer::rasterize] Invalid primitive topology!");
		}
	}
	// Determine the line-drawing algorithm.
	void (*drawLine)(const RenderingContext&, const Fragment&, const Fragment&, Framebuffer&) = nullptr;
	switch (context.lineDrawingAlgorithm) {
		case LineDrawingAlgorithm::XiaolinWu:
			drawLine = &WireframeRenderer::drawXiaolinWuLine;
			break;
		case LineDrawingAlgorithm::Bresenham:
		default:
			drawLine = &WireframeRenderer::drawBresenhamLine;
			break;
	}

	for (std::size_t i = 0; i < primitiveCount; i += step) {
		drawLine(
			context,
			Fragment(vertices[i]),
			Fragment(vertices[(i + 1) % primitiveCount]),
			framebuffer
		);
	}
}


void
WireframeRenderer::drawBresenhamLine(
	const RenderingContext& context,
	const Fragment& from,
	const Fragment& to,
	Framebuffer& framebuffer
) {
	const int x0 = from.x;
	const int y0 = from.y;
	const int x1 = to.x;
	const int y1 = to.y;
	const int xmin = std::min(x0, x1);
	const int xmax = std::max(x0, x1);
	const int ymin = std::min(y0, y1);
	const int ymax = std::max(y0, y1);
	const int dx = x1 - x0;
	const int dy = y1 - y0;
	const double slope = dy / double(dx);
	const double b = y0 - (slope * x0); // Remember, the line equation is y = mx + b.

	if (dx == 0) {
		for (int y = ymin; y <= ymax; ++y) {
			auto f = Fragment::lerp(from, to, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.x = x0;
			f.y = y;
			fragmentProcessing(context, f, framebuffer);
		}
	} else if (std::abs(slope) < 1.0) {
		for (int x = xmin; x <= xmax; ++x) {
			auto f = Fragment::lerp(from, to, dx == 0 ? 0.0f : (x - x0) / double(dx));
			f.x = x;
			f.y = std::round((slope * x) + b);
			fragmentProcessing(context, f, framebuffer);
		}
	} else {
		for (int y = ymin; y <= ymax; ++y) {
			auto f = Fragment::lerp(from, to, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.x = std::round((y - b) / slope);
			f.y = y;
			fragmentProcessing(context, f, framebuffer);
		}
	}
}


void
WireframeRenderer::drawXiaolinWuLine(
	const RenderingContext& context,
	const Fragment& from,
	const Fragment& to,
	Framebuffer& framebuffer
) {
	//TODO Implement me.
	return drawBresenhamLine(context, from, to, framebuffer);
}
