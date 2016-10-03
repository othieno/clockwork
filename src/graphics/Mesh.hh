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
#ifndef CLOCKWORK_MESH_HH
#define CLOCKWORK_MESH_HH

#include "Resource.hh"
#include "Point.hh"
#include "Point3.hh"
#include "Material.hh"
#include <QList>


namespace clockwork {
/**
 *
 */
class Mesh : public Resource {
	friend class ResourceManager;
public:
	/**
	 * A triangle polygon face.
	 */
	struct Face {
		/**
		 * The index of each vertex that makes up this face.
		 */
		std::array<std::uint32_t, 3> indices;
		/**
		 * The surface normals for each vertex in the face.
		 */
		std::array<Vector3, 3> normals;
		/**
		 * The texture mapping coordinates for each vertex in the face.
		 */
		std::array<Point, 3> uv;
	};
	/**
	 *
	 */
	Mesh(const Mesh&) = delete;
	/**
	 *
	 */
	Mesh(Mesh&&) = delete;
	/**
	 *
	 */
	Mesh& operator=(const Mesh&) = delete;
	/**
	 *
	 */
	Mesh& operator=(Mesh&&) = delete;
	/**
	 * Returns the mesh's vertex positions.
	 */
	const QList<Point3>& getVertices() const;
	/**
	 * Sets the polygon mesh's vertex positions.
	 * @param vertices the mesh's vertex positions.
	 */
	void setVertices(const QList<Point3>& vertices);
	/**
	 * Returns the mesh's polygon faces.
	 */
	const QList<Face>& getFaces() const;
	/**
	 * Sets the polygon mesh's faces.
	 * @param faces the mesh's faces.
	 */
	void setFaces(const QList<Face>& faces);
	/**
	 * Returns the mesh's material.
	 */
	const Material& getMaterial() const;
	/**
	 * Sets the mesh's material.
	 * @param material the material to set.
	 */
	void setMaterial(const Material& material);
private:
	/**
	 *
	 */
	Mesh() = default;
	/**
	 * Loads a polygon mesh from the specified file.
	 * @param file a file containing the data to load.
	 */
	void load(QFile& file) override;
	/**
	 * The polygon mesh's vertices.
	 */
	QList<Point3> vertices_;
	/**
	 * The polygon mesh's polygon faces.
	 */
	QList<Face> faces_;
	/**
	 * The polygon mesh's material information.
	 */
	Material material_;
};
} // namespace clockwork

#endif // CLOCKWORK_MESH_HH
