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
#ifndef CLOCKWORK_MESH_HH
#define CLOCKWORK_MESH_HH

#include "Resource.hh"
#include "Material.hh"
#include <QList>
#include <QVector3D>
#include <QPointF>


namespace clockwork {
/**
 *
 */
class Mesh : public Resource {
	friend class ResourceManager;
public:
	/**
	 * A polygon mesh's triangular face.
	 */
	struct Face {
		/**
		 * The number of elements in the face.
		 */
		constexpr static std::size_t length = 3;
		/**
		 * An array of pointers to geometric positions.
		 */
		using Positions = std::array<const QVector3D*, Face::length>;
		/**
		 * An array of pointers to 2D texture coordinates.
		 */
		using TextureCoordinates = std::array<const QPointF*, Face::length>;
		/**
		 * An array of pointers to 3D normal vectors.
		 */
		using Normals = std::array<const QVector3D*, Face::length>;
		/**
		 * Instantiates a Face object with references to the specified positions,
		 * texture coordinates and normal vectors.
		 */
		Face(const Positions&, const TextureCoordinates&, const Normals&);
		/**
		 * The positions of each vertex in the face.
		 */
		const Positions positions;
		/**
		 * The texture coordinates for each vertex in the face.
		 */
		const TextureCoordinates textureCoordinates;
		/**
		 * The normal vectors for each vertex in the face.
		 */
		const Normals normals;
		/**
		 * The surface normal.
		 */
		const QVector3D surfaceNormal;
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
	 * Removes all data from the mesh's arrays.
	 */
	void clear();
	/**
	 * The polygon mesh's vertex positions.
	 */
	QList<QVector3D> positions;
	/**
	 * The polygon mesh's texture coordinates.
	 */
	QList<QPointF> textureCoordinates;
	/**
	 * The polygon mesh's vertex normals.
	 */
	QList<QVector3D> normals;
	/**
	 * The polygon mesh's faces.
	 */
	QList<Face> faces;
	/**
	 * The polygon mesh's material information.
	 */
	Material material;
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
};
} // namespace clockwork

#endif // CLOCKWORK_MESH_HH
