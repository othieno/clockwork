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
#ifndef CLOCKWORK_NORMAL_MAP_SHADER_PROGRAM_HH
#define CLOCKWORK_NORMAL_MAP_SHADER_PROGRAM_HH

#include "ShaderProgram.hh"


namespace clockwork {
namespace detail {
/**
 *
 */
template<>
struct ShaderProgram<RenderingAlgorithm::NormalMapping>::Vertex : clockwork::Vertex {
	/**
	 * Performs a linear interpolation to find the Vertex at a specified
	 * percentage between two Vertex instances.
	 */
	static Vertex lerp(const Vertex& from, const Vertex& to, const double percentage);
	/**
	 *
	 */
	QVector4D normal;
};
/**
 *
 */
template<>
struct ShaderProgram<RenderingAlgorithm::NormalMapping>::Fragment : clockwork::Fragment {
	/**
	 * Instantiates a Fragment object.
	 */
	Fragment() = default;
	/**
	 *
	 */
	explicit Fragment(const Vertex&);
	/**
	 * Performs a linear interpolation to find the Fragment at a specified
	 * percentage between two Fragment instances.
	 */
	static Fragment lerp(const Fragment& from, const Fragment& to, const double percentage);
	/**
	 *
	 */
	QVector4D normal;
};
/**
 * Initializes the vertex attributes used by the vertex shader.
 */
template<> void
ShaderProgram<RenderingAlgorithm::NormalMapping>::setVertexAttributes(VertexAttributes&, const Mesh::Face&, const std::size_t);
/**
 * The vertex shader used by the normal mapping renderer.
 */
template<> ShaderProgram<RenderingAlgorithm::NormalMapping>::Vertex
ShaderProgram<RenderingAlgorithm::NormalMapping>::vertexShader(const Uniforms&, Varying&, const VertexAttributes&);
/**
 * The fragment shader used by the normal mapping renderer.
 */
template<> std::uint32_t
ShaderProgram<RenderingAlgorithm::NormalMapping>::fragmentShader(const Uniforms&, const Varying&, const Fragment&);
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_NORMAL_MAP_SHADER_PROGRAM_HH
