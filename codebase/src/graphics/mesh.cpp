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
#include "mesh.hh"


const std::vector<clockwork::graphics::Mesh::Face>&
clockwork::graphics::Mesh::getFaces() const
{
	return _faces;
}


const std::vector<clockwork::graphics::Vertex>&
clockwork::graphics::Mesh::getVertices() const
{
	return _vertices;
}


clockwork::graphics::Mesh::Face::Face
(
	const std::array<const clockwork::graphics::Vertex*, 3>& vs,
	const std::array<const clockwork::graphics::Mesh::Face::UVMap, 3>& uvs
) :
vertices(vs),
uvmap(uvs)
{
	// Get the vertex affine positions.
	const clockwork::Point3& P0 = *vertices[0];
	const clockwork::Point3& P1 = *vertices[1];
	const clockwork::Point3& P2 = *vertices[2];

	// Calculate the face's normal.
	auto& _normal = const_cast<clockwork::Vector3&>(normal);
	_normal = clockwork::Vector3::cross(P1 - P0, P2 - P0);

	// Calculate the face's center.
	auto& _center = const_cast<clockwork::Point3&>(center);
	_center.x = (P0.x + P1.x + P2.x) * 0.333333; // 1/3 = 0.333333
	_center.y = (P0.y + P1.y + P2.y) * 0.333333;
	_center.z = (P0.z + P1.z + P2.z) * 0.333333;
}


clockwork::graphics::Mesh::Face::Face(const std::array<const clockwork::graphics::Vertex*, 3> vertices) :
Face(vertices, {Face::UVMap(), Face::UVMap(), Face::UVMap()})
{}


clockwork::graphics::Mesh::Face::Face::UVMap::UVMap(const double& inu, const double& inv) :
u(inu),
v(inv)
{}
