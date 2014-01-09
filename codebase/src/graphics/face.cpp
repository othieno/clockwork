/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
 *
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
#include "face.hh"
#include "model3d.hh"


clockwork::graphics::Face::TextureCoordinates::TextureCoordinates(const double& U, const double& V) :
u(U),
v(V)
{}


clockwork::graphics::Face::Face
(
	const clockwork::graphics::Model3D& model3D,
	const std::array<const uint32_t, 3>& indices,
	const std::array<const clockwork::graphics::Face::TextureCoordinates, 3>& textureCoordinates
) :
_model3D(model3D),
_indices(indices),
_textureCoordinates(textureCoordinates)
{
	const auto& vertices = _model3D.getVertices();

	// Get the vertex affine positions.
	const clockwork::Point3& P0 = vertices[_indices[0]];
	const clockwork::Point3& P1 = vertices[_indices[1]];
	const clockwork::Point3& P2 = vertices[_indices[2]];

	// Calculate the face's surface normal.
	auto& N = const_cast<clockwork::Vector3&>(_normal);
	N = clockwork::Vector3::cross(P1 - P0, P2 - P0);

	// Calculate the face's center.
	auto& C = const_cast<clockwork::Point3&>(_center);
	C.x = (P0.x + P1.x + P2.x) * 0.333333; // 0.333333 == 1/3
	C.y = (P0.y + P1.y + P2.y) * 0.333333;
	C.z = (P0.z + P1.z + P2.z) * 0.333333;
}


clockwork::graphics::Face::Face
(
	const clockwork::graphics::Model3D& model3D,
	const std::array<const uint32_t, 3>& indices
) :
Face(model3D, indices, {Face::TextureCoordinates(0, 0), Face::TextureCoordinates(0, 0), Face::TextureCoordinates(0, 0)})
{}


std::array<const clockwork::graphics::Vertex*, 3>
clockwork::graphics::Face::getVertices() const
{
	const auto& vertices = _model3D.getVertices();
	return
	{
		&vertices[_indices[0]],
		&vertices[_indices[1]],
		&vertices[_indices[2]]
	};
}


const std::array<const clockwork::graphics::Face::TextureCoordinates, 3>&
clockwork::graphics::Face::getTextureCoordinates() const
{
	return _textureCoordinates;
}


const clockwork::Vector3&
clockwork::graphics::Face::getNormal() const
{
	return _normal;
}


const clockwork::Point3&
clockwork::graphics::Face::getCenter() const
{
	return _center;
}
