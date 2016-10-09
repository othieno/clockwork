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
#include "RandomShadingRenderer.hh"
#include "lerp.hh"

using clockwork::RandomShadingRenderer;


RandomShadingRenderer::Varying
RandomShadingRenderer::createVarying(const Mesh::Face& face, const std::size_t) {
	// Use the face's memory address as an ARGB value. The address is a sufficiently
	// random 32-bit number that can be split into a ColorARGB object.
	const auto address = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&face));

	// Note that 0xFF000000 is OR'd to the address to make sure the generated color's
	// alpha channel is equal to 1.0.
	Varying varying;
	varying.faceColor = Color(address | 0xFF000000);

	return varying;
}


std::uint32_t
RandomShadingRenderer::fragmentShader(const Uniforms&, const Varying& varying, const Fragment&) {
	return varying.faceColor;
}


RandomShadingRenderer::Fragment
RandomShadingRenderer::createFragment(const VertexShaderOutput& output) {
	const auto& position = output.position;
	Fragment fragment;
	fragment.x = std::round(position.x);
	fragment.y = std::round(position.y);
	fragment.varying.faceColor = output.varying.faceColor;

	return fragment;
}


RandomShadingRenderer::VertexShaderOutput
RandomShadingRenderer::lerp(const VertexShaderOutput& from, const VertexShaderOutput& to, const double p) {
	VertexShaderOutput output;
	output.position = clockwork::lerp(from.position, to.position, p);
	output.varying = RandomShadingRenderer::lerp(from.varying, to.varying, p);

	return output;
}


RandomShadingRenderer::Fragment
RandomShadingRenderer::lerp(const Fragment& from, const Fragment& to, const double p) {
	const double pp = 1.0 - p;

	Fragment fragment;
//	fragment.x = 0;	// <x, y> are ignored because they are always set to some other value after
//	fragment.y = 0;	// interpolation. For more info, check out PolygonRenderer::rasterize.
	fragment.z = (pp * from.z) + (p * to.z);
	fragment.stencil = std::round((pp * from.stencil) + (p * to.stencil));
	fragment.varying.faceColor = clockwork::lerp(from.varying.faceColor, to.varying.faceColor, p);

	return fragment;
}

RandomShadingRenderer::Varying
RandomShadingRenderer::lerp(const Varying& from, const Varying& to, const double p) {
	Varying varying;
	varying.faceColor = clockwork::lerp(from.faceColor, to.faceColor, p);

	return varying;
}
