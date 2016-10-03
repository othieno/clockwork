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
	 * The polygon mesh's vertices.
	 */
	QList<Point3> vertices;
	/**
	 * The polygon mesh's vertex index buffer.
	 */
	QList<std::uint32_t> vertexIndices;
	/**
	 * The polygon mesh's texture coordinates.
	 */
	QList<Point> textureCoordinates;
	/**
	 * The polygon mesh's texture coordinate index buffer.
	 */
	QList<std::uint32_t> textureCoordinateIndices;
	/**
	 * The polygon mesh's vertex normals.
	 */
	QList<Vector3> normals;
	/**
	 * The polygon mesh's normal index buffer.
	 */
	QList<std::uint32_t> normalIndices;
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
