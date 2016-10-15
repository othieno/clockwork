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
#include <cmath>

using clockwork::WireframeRenderer;


void
WireframeRenderer::sanitizeContext(RenderingContext& context) {
	// The Wireframe renderer only draws line primitives so if the primitive mode
	// is not set to Line, LineStrip or LineLoop, it will be set to LineLoop.
	auto& mode = context.primitiveMode;
	if (mode != Primitive::Line && mode != Primitive::LineStrip && mode != Primitive::LineLoop) {
		mode = Primitive::LineLoop;
	}
}


void
WireframeRenderer::primitiveAssembly(const RenderingContext&, VertexArray&) {}


void
WireframeRenderer::clip(const RenderingContext&, VertexArray&) {}


WireframeRenderer::FragmentArray
WireframeRenderer::rasterize(const RenderingContext& context, const VertexArray& vertices) {
	const std::size_t primitiveCount = vertices.size();

	FragmentArray (*getLineFragments)(const PipelineFragment&, const PipelineFragment&) = nullptr;
	switch (context.lineDrawingAlgorithm) {
		case LineDrawingAlgorithm::XiaolinWu:
			getLineFragments = &WireframeRenderer::getXiaolinWuLineFragments;
			break;
		case LineDrawingAlgorithm::Bresenham:
		default:
			getLineFragments = &WireframeRenderer::getBresenhamLineFragments;
			break;
	}

	FragmentArray fragments;
	switch (context.primitiveMode) {
		case Primitive::Line: {
			// In the case of Line primitives, the number of primitves must be
			// even to prevent accessing data out of the primitives array. If
			// the number of primitives is odd, the last primitive is discared.
			// To make sure the number is even, we simply apply the mask 0xF...FFFFFE
			// to it.
			constexpr auto MASK = std::numeric_limits<decltype(primitiveCount)>::max() - 1;
			for (std::size_t i = 0; i < (primitiveCount & MASK); ++i) {
				const PipelineFragment f0(vertices[i]);
				const PipelineFragment f1(vertices[i + 1]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
		}
		case Primitive::LineStrip:
			for (std::size_t i = 0; i < (primitiveCount - 1); ++i) {
				const PipelineFragment f0(vertices[i]);
				const PipelineFragment f1(vertices[i + 1]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
		case Primitive::LineLoop:
			for (std::size_t i = 0; i < primitiveCount; ++i) {
				const PipelineFragment f0(vertices[i]);
				const PipelineFragment f1(vertices[(i + 1) % primitiveCount]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
		default:
			break;
	}
	return fragments;
}


WireframeRenderer::FragmentArray
WireframeRenderer::getBresenhamLineFragments(const PipelineFragment& from, const PipelineFragment& to) {
	FragmentArray fragments;

	const int x0 = from.data.x;
	const int y0 = from.data.y;
	const int x1 = to.data.x;
	const int y1 = to.data.y;
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
			auto f = PipelineFragment::lerp(from, to, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.data.x = x0;
			f.data.y = y;
			fragments.append(f);
		}
	} else if (std::abs(slope) < 1.0) {
		for (int x = xmin; x <= xmax; ++x) {
			auto f = PipelineFragment::lerp(from, to, dx == 0 ? 0.0f : (x - x0) / double(dx));
			f.data.x = x;
			f.data.y = std::round((slope * x) + b);
			fragments.append(f);
		}
	} else {
		for (int y = ymin; y <= ymax; ++y) {
			auto f = PipelineFragment::lerp(from, to, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.data.x = std::round((y - b) / slope);
			f.data.y = y;
			fragments.append(f);
		}
	}
	return fragments;
}


WireframeRenderer::FragmentArray
WireframeRenderer::getXiaolinWuLineFragments(const PipelineFragment& from, const PipelineFragment& to) {
	return getBresenhamLineFragments(from, to);
}
