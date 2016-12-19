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
#include "Mesh.hh"
#include "fileReader.hh"

using clockwork::Mesh;


/**
 * TODO Implement me.
 * Calculates a surface normal.
 */
static QVector3D
calculateSurfaceNormal(const Mesh::Face::Positions& positions) {
	const auto& p0 = *positions[0];
	const auto& p1 = *positions[1];
	const auto& p2 = *positions[2];

	Q_UNUSED(p0);
	Q_UNUSED(p1);
	Q_UNUSED(p2);
	return QVector3D(0, 0, 0);
}


Mesh::Face::Face(
	const Face::Positions& p,
	const Face::TextureCoordinates& uv,
	const Face::Normals& n
) :
positions(p),
textureCoordinates(uv),
normals(n),
surfaceNormal(calculateSurfaceNormal(p)) {}


void
Mesh::clear() {
	positions.clear();
	textureCoordinates.clear();
	normals.clear();
	faces.clear();
}


void
Mesh::load(QFile& file) {
	auto error = parseOBJFile(file, *this);
	if (error != Error::None) {
		qFatal("[Mesh::load] Could not load mesh data!");
	}
}
