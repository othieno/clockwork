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


clockwork::Error
clockwork::io::loadOBJ(QFile& file, clockwork::graphics::Mesh& mesh, clockwork::graphics::Material&)
{
	clockwork::Error error = clockwork::Error::None;
	if (file.open(QIODevice::ReadOnly))
	{
		auto& vertices = const_cast<std::vector<clockwork::graphics::Vertex>&>(mesh.getVertices());
		auto& faces = const_cast<std::vector<clockwork::graphics::Mesh::Face>&>(mesh.getFaces());
		std::vector<clockwork::Vector3> normals;
		std::vector<clockwork::graphics::Mesh::Face::UVMap> uvmaps;

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

						uvmaps.push_back(clockwork::graphics::Mesh::Face::UVMap(u, v));
					}
					else if (command == "vn")
					{
						const auto& i = tokens.takeFirst().toDouble();
						const auto& j = tokens.takeFirst().toDouble();
						const auto& k = tokens.takeFirst().toDouble();

						normals.push_back(clockwork::Vector3(i, j, k).normalise());
					}
					else if (command == "f")
					{
						const auto& nVertices = vertices.size();
						const auto& nUVs = uvmaps.size();
						const auto& nNormals = normals.size();

						clockwork::graphics::Vertex* currentVertex = nullptr;
						std::vector<const clockwork::graphics::Vertex*> localVertices;
						std::vector<const clockwork::graphics::Mesh::Face::UVMap*> localUVMap;

						while (!tokens.empty())
						{
							// Split the token into one or more indices.
							auto indices = tokens.takeFirst().split("/");

							// Get the vertex from its index.
							int index = indices.takeFirst().toInt() - 1;
							if (index < 0)
								index += nVertices + 1;
							currentVertex = &vertices[index];
							localVertices.push_back(currentVertex);

							// Get the texture coordinate if it's given.
							if (!indices.empty())
							{
								// Since texture coordinates are optional, make sure we're not
								// parsing an empty string.
								const auto& indexString = indices.takeFirst();
								if (!indexString.isEmpty())
								{
									index = indexString.toInt() - 1;
									if (index < 0)
										index += nUVs + 1;

									localUVMap.push_back(&uvmaps[index]);
								}
							}

							// Set the vertex normal if it's specified.
							if (!indices.empty() && currentVertex != nullptr)
							{
								index = indices.takeFirst().toInt() - 1;
								if (index < 0)
									index += nNormals + 1;

								currentVertex->setNormal(normals[index]);
							}
						}

						// Create polygonal faces from the vertices and mapping coordinates we obtained.
						// If there're more than three vertices, triangulate.
						for (unsigned int i = 0; i < localVertices.size() - 2; ++i)
						{
							std::array<const clockwork::graphics::Vertex*, 3> faceVertices =
							{
								localVertices[0],
								localVertices[i + 1],
								localVertices[i + 2]
							};
							std::array<const clockwork::graphics::Mesh::Face::UVMap, 3> faceUVMap =
							{
								*localUVMap[0],
								*localUVMap[i + 1],
								*localUVMap[i + 2]
							};
							faces.push_back(clockwork::graphics::Mesh::Face(faceVertices, faceUVMap));
						}
					}
					else if (command == "mtllib")
					{
						//TODO
					}
					else if (command == "usemtl")
					{
						//TODO
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

