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
#ifndef CLOCKWORK_SHADER_PROGRAM_HH
#define CLOCKWORK_SHADER_PROGRAM_HH

#include "RenderingAlgorithm.hh"
#include "Fragment.hh"
#include "Vertex.hh"
#include "VertexAttributes.hh"
#include "lerp.hh"
#include <cmath>


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
	struct Varying {};
	/**
	 *
	 */
	struct Vertex : clockwork::Vertex {
		/**
		 *
		 */
		static Vertex lerp(const Vertex& from, const Vertex& to, const double percentage);
		/**
		 * The attached set of varying variables to be passed on to the fragment shader.
		 */
		Varying varying;
	};
	/**
	 *
	 */
	using VertexAttributes = clockwork::VertexAttributes;
	/**
	 *
	 */
	struct Fragment : clockwork::Fragment {
		/**
		 * Instantiates a Fragment object.
		 */
		Fragment() = default;
		/**
		 *
		 */
		explicit Fragment(const Vertex&);
		/**
		 *
		 */
		static Fragment lerp(const Fragment& from, const Fragment& to, const double percentage);
		/**
		 * The attached set of varying variables.
		 */
		Varying varying;
	};
	/**
	 * Initializes the vertex attributes used by the vertex shader.
	 */
	static void setVertexAttributes(VertexAttributes&, const Mesh::Face&, const std::size_t);
	/**
	 * Initializes the varying variables used by the vertex and fragment shaders.
	 */
	static void setVarying(Varying&, const Mesh::Face&, const std::size_t);
	/**
	 * Performs a basic per-vertex operation on the specified set of vertex attributes.
	 */
	static Vertex vertexShader(const Uniforms&, Varying&, const VertexAttributes&);
	/**
	 * Returns a pixel value.
	 */
	static std::uint32_t fragmentShader(const Uniforms&, const Varying&, const Fragment&);
};


template<RenderingAlgorithm A> typename ShaderProgram<A>::Vertex
ShaderProgram<A>::Vertex::lerp(const Vertex& from, const Vertex& to, const double p) {
	Vertex vertex;
	vertex.position = clockwork::lerp(from.position, to.position, p);
	return vertex;
}


template<RenderingAlgorithm A>
ShaderProgram<A>::Fragment::Fragment(const Vertex& v) {
	x = std::round(v.position.x);
	y = std::round(v.position.y);
	z = v.position.z;
	stencil = 0xFF;
	varying = v.varying;
}


template<RenderingAlgorithm A> typename ShaderProgram<A>::Fragment
ShaderProgram<A>::Fragment::lerp(const Fragment& from, const Fragment& to, const double p) {
	const double pp = 1.0 - p;

	Fragment fragment;
//	fragment.x = 0;	// <x, y> are ignored because they are always set to some other value after
//	fragment.y = 0;	// interpolation. For more info, please refer to any renderer's rasterize function.
	fragment.z = (pp * from.z) + (p * to.z);
	fragment.stencil = std::round((pp * from.stencil) + (p * to.stencil));

	return fragment;
}


template<RenderingAlgorithm A> void
ShaderProgram<A>::setVertexAttributes(VertexAttributes& attributes, const Mesh::Face& face, const std::size_t i) {
	if (Q_UNLIKELY(i >= face.length)) {
		return;
	}
	attributes.position = face.positions[i];
	attributes.normal = face.normals[i];
	attributes.textureCoordinates = face.textureCoordinates[i];
}


template<RenderingAlgorithm A> void
ShaderProgram<A>::setVarying(Varying&, const Mesh::Face&, const std::size_t) {}


template<RenderingAlgorithm A> typename ShaderProgram<A>::Vertex
ShaderProgram<A>::vertexShader(const Uniforms& uniforms, Varying&, const VertexAttributes& attributes) {
	const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const Matrix4>();
	const auto& position = *attributes.position;

	Vertex output;
	output.position = MVP * Point4(position);

	return output;
}


template<RenderingAlgorithm A> std::uint32_t
ShaderProgram<A>::fragmentShader(const Uniforms&, const Varying&, const Fragment&) {
	return 0xFFFFFFFF;
}
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_SHADER_PROGRAM_HH
