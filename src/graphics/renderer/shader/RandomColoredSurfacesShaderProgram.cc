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
#include "RandomColoredSurfacesShaderProgram.hh"

using clockwork::ShaderProgramIdentifier;
using ShaderProgram = clockwork::detail::ShaderProgram<ShaderProgramIdentifier::RandomColoredSurfaces>;


ShaderProgram::Varying
ShaderProgram::Varying::lerp(const Varying& from, const Varying&, const double) {
	// Since vertices of a same face share an identical color, and both the fragments
	// belong to the same face, the result of the interpolation is the same color as
	// that of both fragments.
	Varying varying;
	varying.faceColor = from.faceColor;

	return varying;
}


template<> void
ShaderProgram::setVertexAttributes(VertexAttributes& attributes, const Mesh::Face& face, const std::size_t i) {
	if (Q_UNLIKELY(i >= face.length)) {
		return;
	}
	attributes.position = face.positions[i];
	attributes.faceAddress = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&face));
}


template<> ShaderProgram::Vertex
ShaderProgram::vertexShader(const Uniforms& uniforms, Varying& varying, const VertexAttributes& attributes) {
	const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const QMatrix4x4>();
	const auto& position = QVector4D(*attributes.position, 1.0);

	Vertex output;
	output.position = MVP * position;

	// Note that 0xFF000000 is OR'd to the address to make sure the generated color's
	// alpha channel is equal to 1.0.
	varying.faceColor = Color(attributes.faceAddress | 0xFF000000);

	return output;
}


template<> std::uint32_t
ShaderProgram::fragmentShader(const Uniforms&, const Varying& varying, const Fragment&) {
	return varying.faceColor;
}
