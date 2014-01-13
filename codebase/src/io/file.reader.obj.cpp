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
#include "file.reader.hh"
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QFileInfo>
#include "io.output.hh"


/**
 * Load the material with the given name, from a given text stream and store it in a
 * Material object. If any errors occur, an appropriate error value is returned.
 */
clockwork::Error loadMaterial(const QString& name, QTextStream& from, clockwork::graphics::Material& to);


clockwork::Error
clockwork::io::loadOBJ(QFile& file, clockwork::graphics::Model3D& model)
{
	clockwork::Error error = clockwork::Error::None;
	if (file.open(QIODevice::ReadOnly))
	{
		auto& vertices = const_cast<std::vector<clockwork::graphics::Vertex>&>(model.getVertices());
		std::vector<clockwork::Vector3> normals;
		std::vector<clockwork::graphics::Face::TextureCoordinates> texcoords;
		QString materialFilename;

		QTextStream stream(&file);
		stream.skipWhiteSpace();
		while (!stream.atEnd())
		{
			// Read a line and remove any leading and trailing spaces.
			const auto& line = stream.readLine().simplified();

			// Skip comments and empty lines.
			if (!line.isEmpty() && line[0] != '#')
			{
				auto tokens = line.split(" ");
				if (!tokens.isEmpty())
				{
					const auto& command = tokens.takeFirst();
					if (command == "v")
					{
						const auto& x = tokens.takeFirst().toDouble();
						const auto& y = tokens.takeFirst().toDouble();
						const auto& z = tokens.takeFirst().toDouble();

						vertices.push_back(clockwork::graphics::Vertex(x, y, z));
					}
					else if (command == "vt")
					{
						const auto& u = tokens.takeFirst().toDouble();
						const auto& v = 1.0 - tokens.takeFirst().toDouble();

						texcoords.push_back(clockwork::graphics::Face::TextureCoordinates(u, v));
					}
					else if (command == "vn")
					{
						const auto& i = tokens.takeFirst().toDouble();
						const auto& j = tokens.takeFirst().toDouble();
						const auto& k = tokens.takeFirst().toDouble();

						// The vector is normalised to make sure it is a unit.
						normals.push_back(clockwork::Vector3::normalise(clockwork::Vector3(i, j, k)));
					}
					else if (command == "f")
					{
						// Keep track of the current vertex so a normal can be assigned to it.
						clockwork::graphics::Vertex* currentVertex = nullptr;

						const auto& vertexCount = vertices.size();
						const auto& texcoordCount = texcoords.size();
						const auto& normalCount = normals.size();

						std::vector<uint32_t> faceIndices;
						std::vector<clockwork::graphics::Face::TextureCoordinates*> faceTexcoords;

						while (!tokens.empty())
						{
							// Split the token into one or more indices.
							auto tokenisedIndices = tokens.takeFirst().split("/");

							// Get the vertex from its index.
							int index = tokenisedIndices.takeFirst().toInt() - 1;
							if (index < 0)
								index += vertexCount + 1;
							faceIndices.push_back(index);

							// Store the current vertex.
							currentVertex = &vertices[index];

							// Get the texture coordinate if it's given.
							if (!tokenisedIndices.empty())
							{
								// Since texture coordinates are optional, make sure we're not
								// parsing an empty string.
								const auto& tokenisedIndex = tokenisedIndices.takeFirst();
								if (!tokenisedIndex.isEmpty())
								{
									index = tokenisedIndex.toInt() - 1;
									if (index < 0)
										index += texcoordCount + 1;

									faceTexcoords.push_back(&texcoords[index]);
								}
							}
							// Set the vertex normal if it's specified.
							if (!tokenisedIndices.empty() && currentVertex != nullptr)
							{
								index = tokenisedIndices.takeFirst().toInt() - 1;
								if (index < 0)
									index += normalCount + 1;

								currentVertex->setNormal(normals[index]);
							}
						}
						// Create polygonal faces from the vertices and mapping coordinates we obtained.
						// If there're more than three vertices, triangulate.
						for (unsigned int i = 0; i < faceIndices.size() - 2; ++i)
						{
							model.addFace
							(
								{
									faceIndices[0],
									faceIndices[i + 1],
									faceIndices[i + 2]
								},
								{
									*faceTexcoords[0],
									*faceTexcoords[i + 1],
									*faceTexcoords[i + 2]
								}
							);
						}
					}
					else if (command == "mtllib")
					{
						// TODO See QDir::separator() and QDir::toNativeSeparators.
						materialFilename =
						QFileInfo(file).canonicalPath().append("/").append(tokens.takeFirst());
					}
					else if (command == "usemtl")
					{
						if (!materialFilename.isEmpty())
						{
							QFileInfo info(materialFilename);
							if (info.exists() && info.isFile() && info.isReadable() && info.size())
							{
								QFile materialFile(info.canonicalFilePath());
								if (materialFile.open(QIODevice::ReadOnly))
								{
									const QString materialName(tokens.takeFirst());
									QTextStream materialFileStream(&materialFile);
									auto& material(const_cast<clockwork::graphics::Material&>(model.getMaterial()));

									auto error = loadMaterial(materialName, materialFileStream, material);
									if (error != clockwork::Error::None)
										std::cout << "Warning! Could not load the material data." << error << std::endl;
								}
							}
						}
					}
					else
						std::cout
						<< "Warning! The .obj reader does not support the '"
						<< command.toStdString() << "' command." << std::endl;
				}
			}
		}
		file.close();
	}
	else
		error = clockwork::Error::Unknown;
	return error;
}


clockwork::Error
loadMaterial(const QString& name, QTextStream& stream, clockwork::graphics::Material& material)
{
	auto error = clockwork::Error::None;
	auto processingMaterial = false;

	stream.skipWhiteSpace();
	while (!stream.atEnd())
	{
		// Read a line and remove any leading and trailing spaces.
		const auto& line = stream.readLine().simplified();

		// Skip comments and empty lines.
		if (!line.isEmpty() && line[0] != '#')
		{
			auto tokens = line.split(" ");
			if (!tokens.isEmpty())
			{
				const auto& command = tokens.takeFirst();

				// We've reached a material section. Process or ignore it.
				if (command == "newmtl")
				{
					// If a material is currently being processed and a new section is
					// reached, then we know we've reached the end of the target material.
					if (processingMaterial)
						break;
					else if (!processingMaterial && name == tokens.takeFirst())
						processingMaterial = true;
				}
				else if (processingMaterial)
				{
					if (!QString::compare(command, "Ka", Qt::CaseInsensitive))
					{
						material.Ka.red = tokens.takeFirst().toDouble();
						material.Ka.green = tokens.takeFirst().toDouble();
						material.Ka.blue = tokens.takeFirst().toDouble();
					}
					else if (!QString::compare(command, "Kd", Qt::CaseInsensitive))
					{
						material.Kd.red = tokens.takeFirst().toDouble();
						material.Kd.green = tokens.takeFirst().toDouble();
						material.Kd.blue = tokens.takeFirst().toDouble();
					}
					else if (!QString::compare(command, "Ks", Qt::CaseInsensitive))
					{
						material.Ks.red = tokens.takeFirst().toDouble();
						material.Ks.green = tokens.takeFirst().toDouble();
						material.Ks.blue = tokens.takeFirst().toDouble();
					}
					else if (!QString::compare(command, "Tr", Qt::CaseInsensitive))
						material.transparency = tokens.takeFirst().toDouble();
					else if (!QString::compare(command, "Ns", Qt::CaseInsensitive))
						material.shininess = tokens.takeFirst().toDouble();

					// TODO Load textures.
				}
			}
		}
	}
	return error;
}
