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
#ifndef CLOCKWORK_RANDOM_SHADING_SHADER_PROGRAM_HH
#define CLOCKWORK_RANDOM_SHADING_SHADER_PROGRAM_HH

#include "ShaderProgram.hh"


namespace clockwork {
namespace detail {
/**
 * The set of varying variables used by the random shading renderer.
 */
template<>
struct ShaderProgram<RenderingAlgorithm::RandomShading>::Varying {
	/**
	 *
	 */
	static Varying lerp(const Varying& from, const Varying& to, const double percentage);
	/**
	 * A random color shared by all vertices that belong to an identical face.
	 */
	Color faceColor;
};
/**
 * The set of vertex attributes used by the random shading renderer.
 */
template<>
struct ShaderProgram<RenderingAlgorithm::RandomShading>::VertexAttributes : BaseVertexAttributes {
	/**
	 * The address of the face that the vertex belongs to. The memory address
	 * is sufficiently random and can be converted into a 32-bit ARGB color
	 * value that can in turn be transformed into a Color object.
	 */
	std::uint32_t faceAddress;
};
/**
 * Initializes the vertex attributes used by the vertex shader.
 */
template<> void
ShaderProgram<RenderingAlgorithm::RandomShading>::setVertexAttributes(VertexAttributes&, const Mesh::Face&, const std::size_t);
/**
 * The vertex shader used by the random shading renderer.
 */
template<> ShaderProgram<RenderingAlgorithm::RandomShading>::Vertex
ShaderProgram<RenderingAlgorithm::RandomShading>::vertexShader(const Uniforms&, Varying&, const VertexAttributes&);
/**
 * The fragment shader used by the random shading renderer.
 */
template<> std::uint32_t
ShaderProgram<RenderingAlgorithm::RandomShading>::fragmentShader(const Uniforms&, const Varying&, const Fragment&);
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_RANDOM_SHADING_SHADER_PROGRAM_HH
