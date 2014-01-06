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
	const auto& V0 = *vertices[0];
	const auto& V1 = *vertices[1];
	const auto& V2 = *vertices[2];

	// Calculate the face's normal.
	auto& _normal = const_cast<clockwork::Vector3&>(normal);
	_normal = clockwork::Vector3::cross(V1 - V0, V2 - V0);

	// Calculate the face's center.
	auto& _center = const_cast<clockwork::Point3&>(center);
	_center.x = (V0.x + V1.x + V2.x) * 0.333333; // 1/3 = 0.333333
	_center.y = (V0.y + V1.y + V2.y) * 0.333333;
	_center.z = (V0.z + V1.z + V2.z) * 0.333333;
}


clockwork::graphics::Mesh::Face::Face(const std::array<const clockwork::graphics::Vertex*, 3> vertices) :
Face(vertices, {Face::UVMap(), Face::UVMap(), Face::UVMap()})
{}


clockwork::graphics::Mesh::Face::Face::UVMap::UVMap(const double& inu, const double& inv) :
u(inu),
v(inv)
{}
