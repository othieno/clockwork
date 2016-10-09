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
#ifndef CLOCKWORK_RANDOM_SHADING_RENDERER_HH
#define CLOCKWORK_RANDOM_SHADING_RENDERER_HH

#include "PolygonRenderer.hh"


namespace clockwork {
/**
 *
 */
class RandomShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::RandomShading, RandomShadingRenderer> {
public:
	/**
	 * Returns a Varying object based on the specified face.
	 */
	static Varying createVarying(const Mesh::Face&, const std::size_t);
	/**
	 * Returns a pixel value.
	 */
	static std::uint32_t fragmentShader(const Uniforms&, const Varying&, const Fragment&);
	/**
	 * Creates a fragment from the specified VertexShaderOutput object.
	 */
	static Fragment createFragment(const VertexShaderOutput&);
	/**
	 *
	 */
	static VertexShaderOutput lerp(const VertexShaderOutput&, const VertexShaderOutput&, const double percentage);
	/**
	 *
	 */
	static Fragment lerp(const Fragment&, const Fragment&, const double percentage);
private:
	/**
	 *
	 */
	static Varying lerp(const Varying&, const Varying&, const double percentage);
};
} // namespace clockwork

#endif // CLOCKWORK_RANDOM_SHADING_RENDERER_HH
