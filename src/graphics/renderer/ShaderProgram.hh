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
#ifndef CLOCKWORK_SHADER_PROGRAM_HH
#define CLOCKWORK_SHADER_PROGRAM_HH

#include "ShaderProgramIdentifier.hh"
#include "RenderingAlgorithm.hh"
#include "BaseFragment.hh"
#include "BaseVertex.hh"
#include "BaseVertexAttributes.hh"
#include "Uniform.hh"
#include "Mesh.hh"

namespace clockwork {
namespace detail {
/**
 *
 */
template<RenderingAlgorithm algorithm>
class ShaderProgram {
public:
	/**
	 *
	 */
	struct Varying {
		/**
		 * Performs a linear interpolation to find the Varying at a specified
		 * percentage between two Varying instances.
		 */
		static Varying lerp(const Varying& from, const Varying& to, const double percentage);
	};
	/**
	 *
	 */
	struct Vertex : BaseVertex {
		/**
		 * Performs a linear interpolation to find the Vertex at a specified
		 * percentage between two Vertex instances.
		 */
		static Vertex lerp(const Vertex& from, const Vertex& to, const double percentage);
	};
	/**
	 *
	 */
	struct VertexAttributes : BaseVertexAttributes {};
	/**
	 *
	 */
	struct Fragment : BaseFragment {
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
	};
	/**
	 * Initializes the vertex attributes used by the vertex shader.
	 */
	static void setVertexAttributes(VertexAttributes&, const Mesh::Face&, const std::size_t);
	/**
	 * Performs a basic per-vertex operation on the specified set of vertex attributes.
	 */
	static Vertex vertexShader(const Uniforms&, Varying&, const VertexAttributes&);
	/**
	 * Returns a pixel value.
	 */
	static std::uint32_t fragmentShader(const Uniforms&, const Varying&, const Fragment&);
};
} // namespace detail
} // namespace clockwork

#include "ShaderProgram.inl"

#endif // CLOCKWORK_SHADER_PROGRAM_HH
