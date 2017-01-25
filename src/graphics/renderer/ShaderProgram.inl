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
#ifndef CLOCKWORK_SHADER_PROGRAM_INL
#define CLOCKWORK_SHADER_PROGRAM_INL

#include "lerp.hh"
#include <cmath>


namespace clockwork {
namespace detail {

template<ShaderProgramIdentifier I> typename ShaderProgram<I>::Varying
ShaderProgram<I>::Varying::lerp(const Varying&, const Varying&, const double) {
	return Varying();
}


template<ShaderProgramIdentifier I> typename ShaderProgram<I>::Vertex
ShaderProgram<I>::Vertex::lerp(const Vertex& from, const Vertex& to, const double p) {
	Vertex vertex;
	vertex.position = clockwork::lerp(from.position, to.position, p);
	return vertex;
}


template<ShaderProgramIdentifier I>
ShaderProgram<I>::Fragment::Fragment(const Vertex& v) {
	x = std::round(v.position.x());
	y = std::round(v.position.y());
	z = v.position.z();
}


template<ShaderProgramIdentifier I> typename ShaderProgram<I>::Fragment
ShaderProgram<I>::Fragment::lerp(const Fragment& from, const Fragment& to, const double p) {
	const double pp = 1.0 - p;

	Fragment fragment;
//	fragment.x = 0;	// <x, y> are ignored because they are always set to some other value after
//	fragment.y = 0;	// interpolation. For more info, please refer to any renderer's rasterize function.
	fragment.z = (pp * from.z) + (p * to.z);

	return fragment;
}


template<ShaderProgramIdentifier I> void
ShaderProgram<I>::setVertexAttributes(VertexAttributes& attributes, const Mesh::Face& face, const std::size_t i) {
	if (Q_UNLIKELY(i >= face.length)) {
		return;
	}
	attributes.position = face.positions[i];
}


template<ShaderProgramIdentifier I> typename ShaderProgram<I>::Vertex
ShaderProgram<I>::vertexShader(const Uniforms& uniforms, Varying&, const VertexAttributes& attributes) {
	const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const QMatrix4x4>();
	const auto& position = QVector4D(*attributes.position, 1.0);

	Vertex output;
	output.position = MVP * position;

	return output;
}


template<ShaderProgramIdentifier I> std::uint32_t
ShaderProgram<I>::fragmentShader(const Uniforms&, const Varying&, const Fragment&) {
	return 0xFFFFFFFF;
}
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_SHADER_PROGRAM_INL
