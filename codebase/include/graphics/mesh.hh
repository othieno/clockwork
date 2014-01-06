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
#pragma once

#include "vertex.hh"
#include "point3.hh"
#include "vector3.hh"
#include <array>
#include <vector>


namespace clockwork {
namespace graphics {

class Mesh
{
public:
	/**
	 * TODO Explain me.
	 */
	struct Face
	{
		/**
		 * UV mapping coordinates.
		 */
		struct UVMap
		{
			double u, v;
			/**
			 * Instantiate a mapping coordinate with given U and V coordinates.
			 */
			UVMap(const double& u = 0, const double& v = 0);
		};
		/**
		 * Instantiate a face with given vertices and texture coordinates.
		 * @param vertices the face's vertices.
		 * @param uvmap the face's UV mapping coordinates.
		 */
		Face
		(
			const std::array<const clockwork::graphics::Vertex*, 3>& vertices,
			const std::array<const Face::UVMap, 3>& uvmap
		);
		/**
		 * Instantiate a face with given vertices.
		 * @param indices the face's vertices.
		 */
		Face(const std::array<const clockwork::graphics::Vertex*, 3> vertices);
		/**
		 * The face's vertices.
		 */
		const std::array<const clockwork::graphics::Vertex*, 3> vertices;
		/**
		 * The face's mapping coordinates.
		 */
		const std::array<const Face::UVMap, 3> uvmap;
		/**
		 * The face's surface normal.
		 */
		const clockwork::Vector3 normal;
		/**
		 * The face's center.
		 */
		const clockwork::Point3 center;
	};
	/**
	 * Return the mesh's faces.
	 */
	const std::vector<Mesh::Face>& getFaces() const;
	/**
	 * Return the mesh's vertices.
	 */
	const std::vector<clockwork::graphics::Vertex>& getVertices() const;
private:
	/**
	 * The mesh's vertices.
	 */
	std::vector<clockwork::graphics::Vertex> _vertices;
	/**
	 * The mesh's faces.
	 */
	std::vector<Mesh::Face> _faces;
};

} // namespace graphics
} // namespace clockwork
