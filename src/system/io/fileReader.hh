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
#ifndef CLOCKWORK_FILE_READER_HH
#define CLOCKWORK_FILE_READER_HH

#include "Error.hh"


/**
 * @see QFile.
 */
class QFile;
/**
 * @see QString.
 */
class QString;
namespace clockwork {
/**
 * @see graphics/Material.hh.
 */
class Material;
/**
 * @see graphics/Mesh.hh.
 */
class Mesh;
/**
 * Parses a .mat file.
 * @param file the file containing the data to parse.
 * @param materialName the material name.
 * @param material a reference to the material where the data will be stored.
 */
Error parseMATFile(QFile& file, const QString& materialName, Material& material);
/**
 * Parses a .obj file.
 * @param file the file containing the data to parse.
 * @param mesh a reference to the polygon mesh where the data will be stored.
 */
Error parseOBJFile(QFile& file, Mesh& mesh);
} // namespace clockwork

#endif // CLOCKWORK_FILE_READER_HH
