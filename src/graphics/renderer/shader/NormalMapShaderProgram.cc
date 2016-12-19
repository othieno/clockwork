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
#include "NormalMapShaderProgram.hh"

using clockwork::RenderingAlgorithm;
using ShaderProgram = clockwork::detail::ShaderProgram<RenderingAlgorithm::NormalMapping>;


ShaderProgram::Vertex
ShaderProgram::Vertex::lerp(const Vertex& from, const Vertex& to, const double p) {
	Vertex vertex;
	vertex.position = clockwork::lerp(from.position, to.position, p);
	vertex.normal = clockwork::lerp(from.normal, to.normal, p);
	return vertex;
}


ShaderProgram::Fragment::Fragment(const Vertex& vertex) {
	x = std::round(vertex.position.x());
	y = std::round(vertex.position.y());
	z = vertex.position.z();
	normal = vertex.normal;
}


ShaderProgram::Fragment
ShaderProgram::Fragment::lerp(const Fragment& from, const Fragment& to, const double p) {
	Fragment fragment;
//	fragment.x = 0;	// <x, y> are ignored because they are always set to some other value after
//	fragment.y = 0;	// interpolation. For more info, please refer to any renderer's rasterize function.
	fragment.z = ((1.0 - p) * from.z) + (p * to.z);
	fragment.normal = clockwork::lerp(from.normal, to.normal, p);
	return fragment;
}


template<> void
ShaderProgram::setVertexAttributes(VertexAttributes& attributes, const Mesh::Face& face, const std::size_t i) {
	if (Q_UNLIKELY(i >= face.length)) {
		return;
	}
	attributes.position = face.positions[i];
	attributes.normal = face.normals[i];
}


template<> ShaderProgram::Vertex
ShaderProgram::vertexShader(const Uniforms& uniforms, Varying&, const VertexAttributes& attributes) {
	const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const QMatrix4x4>();
	const auto& N = uniforms["NORMAL"].as<const QMatrix4x4>();
	const auto& position = QVector4D(*attributes.position, 1.0);
	const auto& normal = QVector4D(*attributes.normal).normalized();

	Vertex output;
	output.position = MVP * QVector4D(position);
	output.normal = N * normal;

	return output;
}


template<> std::uint32_t
ShaderProgram::fragmentShader(const Uniforms&, const Varying&, const Fragment& fragment) {
	return Color(
		(fragment.normal.x() + 1.0) * 0.5,
		(fragment.normal.y() + 1.0) * 0.5,
		(fragment.normal.z() + 1.0) * 0.5
	);
}
