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
#include "PointRenderer.hh"
#include "Framebuffer.hh"
#include "Mesh.hh"
#include <cmath>

using clockwork::PointRenderer;


void
PointRenderer::clip(VertexShaderOutputs& outputs) {
	static const auto& filter = [](const VertexShaderOutput& output) {
		// Use a normalized 2D viewing volume: [-1, 1] x [-1, 1].
		constexpr double xmin = -1.0;
		constexpr double xmax =  1.0;
		constexpr double ymin = -1.0;
		constexpr double ymax =  1.0;

		const auto& p = output.position;
		return p.x < xmin || p.x > xmax || p.y < ymin || p.y > ymax;
	};
	const auto& begin = outputs.begin();
	const auto& end = outputs.end();

	outputs.erase(std::remove_if(begin, end, filter), end);
}


PointRenderer::Fragments
PointRenderer::rasterize(const RenderingContext&, const VertexShaderOutputs& primitives) {
	Fragments fragments;
	for (const auto& primitive : primitives) {
		const auto& position = primitive.position;
		Fragment fragment;
		fragment.x = std::round(position.x);
		fragment.y = std::round(position.y);
		fragment.z = position.z;
		fragment.stencil = 0xFF;

		fragments.append(fragment);
	}
	return fragments;
}
