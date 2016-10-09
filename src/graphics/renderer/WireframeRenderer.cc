/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
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


WireframeRenderer::Fragments
WireframeRenderer::rasterize(const RenderingContext& context, const VertexShaderOutputs& primitives) {
	const std::size_t primitiveCount = primitives.size();

	std::function<Fragments(const Fragment&, const Fragment)> getLineFragments = nullptr;
	switch (context.lineDrawingAlgorithm) {
		case LineDrawingAlgorithm::XiaolinWu:
			getLineFragments = &WireframeRenderer::getXiaolinWuLineFragments;
			break;
		case LineDrawingAlgorithm::Bresenham:
		default:
			getLineFragments = &WireframeRenderer::getBresenhamLineFragments;
			break;
	}

	Fragments fragments;
	switch (context.primitiveMode) {
		case Primitive::Line: {
			// In the case of Line primitives, the number of primitves must be
			// even to prevent accessing data out of the primitives array. If
			// the number of primitives is odd, the last primitive is discared.
			// To make sure the number is even, we simply apply the mask 0xF...FFFFFE
			// to it.
			constexpr auto MASK = std::numeric_limits<decltype(primitiveCount)>::max() - 1;
			for (std::size_t i = 0; i < (primitiveCount & MASK); ++i) {
				const auto& f0 = createFragment(primitives[i]);
				const auto& f1 = createFragment(primitives[i + 1]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
		}
		case Primitive::LineStrip:
			for (std::size_t i = 0; i < (primitiveCount - 1); ++i) {
				const auto& f0 = createFragment(primitives[i]);
				const auto& f1 = createFragment(primitives[i + 1]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
		case Primitive::LineLoop:
		default:
			for (std::size_t i = 0; i < primitiveCount; ++i) {
				const auto& f0 = createFragment(primitives[i]);
				const auto& f1 = createFragment(primitives[(i + 1) % primitiveCount]);
				fragments.append(f0);
				fragments.append(f1);
				fragments.append(getLineFragments(f0, f1));
			}
			break;
	}
	return fragments;
}


WireframeRenderer::Fragment
WireframeRenderer::createFragment(const VertexShaderOutput& primitive) {
	Fragment fragment;
	const auto& position = primitive.position;

	fragment.x = std::round(position.x);
	fragment.y = std::round(position.y);
	fragment.z = position.z;
	fragment.stencil = 0xFF;

	return fragment;
}


WireframeRenderer::Fragment
WireframeRenderer::interpolate(const Fragment& f0, const Fragment& f1, const double p) {
	// The only value to interpolate is the fragment's depth value. Its stencil
	// will be set to 0xFF while its <x, y> coordinates are calculated in the
	// algorithm that generates line fragments.
	Fragment fragment;
	fragment.z = ((1.0 - p) * f0.z) + (p * f1.z);
	fragment.stencil = 0xFF;

	return fragment;
}


WireframeRenderer::Fragments
WireframeRenderer::getBresenhamLineFragments(const Fragment& f0, const Fragment& f1) {
	Fragments fragments;

	const int x0 = f0.x;
	const int y0 = f0.y;
	const int x1 = f1.x;
	const int y1 = f1.y;
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
			Fragment f = interpolate(f0, f1, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.x = x0;
			f.y = y;
			fragments.append(f);
		}
	} else if (std::abs(slope) < 1.0) {
		for (int x = xmin; x <= xmax; ++x) {
			Fragment f = interpolate(f0, f1, dx == 0 ? 0.0f : (x - x0) / double(dx));
			f.x = x;
			f.y = std::round((slope * x) + b);
			fragments.append(f);
		}
	} else {
		for (int y = ymin; y <= ymax; ++y) {
			Fragment f = interpolate(f0, f1, dy == 0 ? 0.0 : (y - y0) / double(dy));
			f.x = std::round((y - b) / slope);
			f.y = y;
			fragments.append(f);
		}
	}
	return fragments;
}


WireframeRenderer::Fragments
WireframeRenderer::getXiaolinWuLineFragments(const Fragment& f0, const Fragment& f1) {
	return getBresenhamLineFragments(f0, f1);
}
