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

#include "asset.hh"
#include "vertex.hh"
#include "point3.hh"
#include "vector3.hh"
#include <array>
#include <vector>


namespace clockwork {
namespace graphics {

class Mesh : public clockwork::io::Asset
{
	/**
	 * TODO Explain me.
	 */
	struct Face
	{
		/**
		 * UV mapping coordinates.
		 */
		struct UVMap { double u, v; };
		/**
		 * Instantiate a face with given indices and texture coordinates,
		 * that is bound to a mesh.
		 * @param mesh the mesh that this face is bound to.
		 * @param indices the face's vertex indices.
		 * @param uvmap the face's UV mapping coordinates.
		 */
		Face
		(
			const Mesh& mesh,
			const std::array<uint32_t, 3> indices,
			const std::array<Face::UVMap, 3> uvmap
		);
		/**
		 * Instantiate a face with given indices, that is bound to a mesh.
		 * @param mesh the mesh that this face is bound to.
		 * @param indices the face's vertex indices.
		 */
		Face
		(
			const Mesh& mesh,
			const std::array<uint32_t, 3> indices
		);
		/**
		 * The face's vertices.
		 */
		const std::array<const clockwork::graphics::Vertex*, 3> vertices;
		/**
		 * The face's mapping coordinates.
		 */
		const std::array<Face::UVMap, 3> uvmap;
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
	 * Add a face.
	 * @param indices the indices of the vertices that make up the face.
	 */
	void addFace(const std::array<uint32_t, 3>& indices);
	/**
	 * Add a face.
	 * @param face the face to add.
	 */
	void addFace(const Mesh::Face& face);
	/**
	 * Return the mesh's faces.
	 */
	const std::vector<Mesh::Face>& getFaces() const;
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
