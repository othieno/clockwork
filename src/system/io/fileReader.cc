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
#include "fileReader.hh"
#include "Mesh.hh"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QtDebug>


clockwork::Error
clockwork::parseMATFile(QFile& file, const QString& materialName, Material& material) {
	if (materialName.isEmpty()) {
		qWarning() << "[parseMATFile] The .mat reader did not receive a material name.";
		return Error::None;
	}

	// If the file is closed, it needs to be opened before it can be processed,
	// and closed when parsing completes.
	const bool fileOpened = file.isOpen();
	if (!fileOpened) {
		if (!file.open(QIODevice::ReadOnly) || !file.isReadable()) {
			return Error::FileNotAccessible;
		}
	}
	file.reset();
	material = Material(); // Reset the material.

	bool parsing = false;
	QTextStream stream(&file);
	stream.skipWhiteSpace();
	while (!stream.atEnd()) {
		// Read a line and remove any leading and trailing spaces. Furthermore,
		// ignore empty lines and comments.
		const auto& line = stream.readLine().simplified();
		if (line.isEmpty() || line[0] == '#') {
			continue;
		}
		auto tokens = line.split(" ");
		if (tokens.isEmpty()) {
			continue;
		}

		const auto& command = tokens.takeFirst();
		if (!QString::compare(command, "newmtl", Qt::CaseInsensitive)) {
			// We've reached a new material section. If the material to parse has
			// already been found, this means that there's nothing left to parse
			// in the current material section. If no material was previously found,
			// we can start parsing this new section if its material name matches
			// the one being looked for.
			if (parsing) {
				break;
			} else if (!parsing && materialName == tokens.takeFirst()) {
				parsing = true;
			}
		} else if (parsing) {
			if (!QString::compare(command, "Ka", Qt::CaseInsensitive)) {
				material.Ka.red = tokens.takeFirst().toDouble();
				material.Ka.green = tokens.takeFirst().toDouble();
				material.Ka.blue = tokens.takeFirst().toDouble();
			} else if (!QString::compare(command, "Kd", Qt::CaseInsensitive)) {
				material.Kd.red = tokens.takeFirst().toDouble();
				material.Kd.green = tokens.takeFirst().toDouble();
				material.Kd.blue = tokens.takeFirst().toDouble();
			} else if (!QString::compare(command, "Ks", Qt::CaseInsensitive)) {
				material.Ks.red = tokens.takeFirst().toDouble();
				material.Ks.green = tokens.takeFirst().toDouble();
				material.Ks.blue = tokens.takeFirst().toDouble();
			} else if (!QString::compare(command, "Tr", Qt::CaseInsensitive)) {
				material.transparency = tokens.takeFirst().toDouble();
			} else if (!QString::compare(command, "Ns", Qt::CaseInsensitive)) {
				material.shininess = tokens.takeFirst().toDouble();
			} else if (!QString::compare(command, "illum", Qt::CaseInsensitive)) {
			} else {
				qWarning() << "[parseMATFile] The .mat reader does not recognize the" << command << "command.";
			}
		}
	}
	// Close the file if it was opened in the parser.
	if (!fileOpened) {
		file.close();
	}
	return Error::None;
}


clockwork::Error
clockwork::parseOBJFile(QFile& file, Mesh& mesh) {
	// If the file is closed, it needs to be opened before it can be processed,
	// and closed when parsing completes.
	const bool fileOpened = file.isOpen();
	if (!fileOpened) {
		if (!file.open(QIODevice::ReadOnly) || !file.isReadable()) {
			return Error::FileNotAccessible;
		}
	}
	file.reset();
	mesh.clear();

	QFile materialFile;
	auto& positions = mesh.positions;
	auto& textureCoordinates = mesh.textureCoordinates;
	auto& normals = mesh.normals;
	auto& faces = mesh.faces;

	QTextStream stream(&file);
	stream.skipWhiteSpace();
	while (!stream.atEnd()) {
		// Read a line and remove any leading and trailing spaces. Furthermore,
		// ignore empty lines and comments.
		const auto& line = stream.readLine().simplified();
		if (line.isEmpty() || line[0] == '#') {
			continue;
		}
		auto tokens = line.split(" ");
		if (tokens.isEmpty()) {
			continue;
		}

		const auto& command = tokens.takeFirst();
		if (command == "v") {
			double x = tokens.takeFirst().toDouble();
			double y = tokens.takeFirst().toDouble();
			double z = tokens.takeFirst().toDouble();
/*
			double w = tokens.isEmpty() ? 1.0 : tokens.takeFirst().toDouble();
			if (!qFuzzyCompare(w, 1.0)) {
				x /= w;
				y /= w;
				z /= w;
			}
*/
			positions.append(Point3(x, y, z));
		} else if (command == "vt") {
			const double u = tokens.takeFirst().toDouble();
			const double v = 1.0 - tokens.takeFirst().toDouble();
			//double w = tokens.isEmpty() ? 0.0 : tokens.takeFirst().toDouble();

			textureCoordinates.append(Point(u, v));
		} else if (command == "vn") {
			const double i = tokens.takeFirst().toDouble();
			const double j = tokens.takeFirst().toDouble();
			const double k = tokens.takeFirst().toDouble();

			// Since the normal isn't always a unit vector, normalize it just in case.
			normals.append(Vector3::normalize(Vector3(i, j, k)));
		} else if (command == "f") {
			const std::size_t positionCount = positions.size();
			const std::size_t uvCount = textureCoordinates.size();
			const std::size_t normalCount = normals.size();
			const std::size_t tokenCount = tokens.size();

			QList<const Point3*> parsedPositions;
			QList<const Point*> parsedTextureCoordinates;
			QList<const Vector3*> parsedNormals;

			while (!tokens.isEmpty()) {
				auto subtokens = tokens.takeFirst().split("/");

				const Point3* p = nullptr;
				const Point* uv = nullptr;
				const Vector3* n = nullptr;

				// Parse the vertex position.
				const int positionIndex = subtokens.takeFirst().toInt();
				if (positionIndex < 0) {
					p = &positions[positionIndex + positionCount];
				} else {
					p = &positions[positionIndex - 1];
				}

				// Parse the texture coordinates and normal vectors. Since these
				// fields are optional, they may not be defined.
				if (!subtokens.isEmpty()) {
					const auto& uvIndexToken = subtokens.takeFirst();
					if (!uvIndexToken.isEmpty()) {
						const int uvIndex = uvIndexToken.toInt();
						if (uvIndex < 0) {
							uv = &textureCoordinates[uvIndex + uvCount];
						} else {
							uv = &textureCoordinates[uvIndex - 1];
						}
					}
					if (!subtokens.isEmpty()) {
						const auto& normalIndexToken = subtokens.takeFirst();
						if (!normalIndexToken.isEmpty()) {
							const int normalIndex = normalIndexToken.toInt();
							if (normalIndex < 0) {
								n = &normals[normalIndex + normalCount];
							} else {
								n = &normals[normalIndex - 1];
							}
						}
					}
				}
				parsedPositions.append(p);
				parsedTextureCoordinates.append(uv);
				parsedNormals.append(n);
			}
			for (std::size_t i = 0; i < tokenCount - 2; ++i) {
				const Mesh::Face::Positions facePositions = {
					parsedPositions[i + 0],
					parsedPositions[i + 1],
					parsedPositions[i + 2]
				};
				const Mesh::Face::TextureCoordinates faceTextureCoordinates = {
					parsedTextureCoordinates[i + 0],
					parsedTextureCoordinates[i + 1],
					parsedTextureCoordinates[i + 2]
				};
				const Mesh::Face::Normals faceNormals = {
					parsedNormals[i + 0],
					parsedNormals[i + 1],
					parsedNormals[i + 2]
				};
				faces.append(Mesh::Face(facePositions, faceTextureCoordinates, faceNormals));
			}
		} else if (command == "mtllib") {
			materialFile.setFileName(tokens.takeFirst());
		} else if (command == "usemtl") {
			if (!materialFile.fileName().isEmpty()) {
				const auto error = parseMATFile(materialFile, tokens.takeFirst(), mesh.material);
				if (error != Error::None) {
					qWarning() << "[parseOBJFile] The .obj reader could not parse the material file.";
				}
			}
		} else if (command == "s" || command == "mg") {
			// Ignore smoothing and merging groups.
		} else {
			qWarning() << "[parseOBJFile] The .obj reader does not recognize the" << command << "command.";
		}
	}
	// Close the file if it was opened in the parser.
	if (!fileOpened) {
		file.close();
	}
	return Error::None;
}
