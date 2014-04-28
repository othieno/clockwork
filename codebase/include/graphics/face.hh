/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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
#include <array>


namespace clockwork {
namespace graphics {

/**
 * TODO Explain me.
 */
class Face
{
public:
   /**
    * Instantiate a face with a given list of vertex indices, normals and texture mapping coordinates.
    * @param indices the list of vertices that make up this face.
    * @param normals the face's vertex normals.
    * @param texcoords the face's texture mapping coordinates.
    */
   Face
   (
      const std::array<const uint32_t, 3>& indices,
      const std::array<const clockwork::Vector3, 3>& normals,
      const std::array<const Texture::Coordinates, 3>& textureCoordinates
   );
   /**
    * Instantiate a face with a given list of vertex indices.
    * @param indices the face's vertices.
    */
   explicit Face(const std::array<const uint32_t, 3>& indices);
   /**
    * Return the face's vertex indices.
    */
   const std::array<const uint32_t, 3>& getIndices() const;
   /**
    * Return the face's texture coordinates.
    */
   const std::array<const clockwork::Vector3, 3>& getNormals() const;
   /**
    * Return the face's texture coordinates.
    */
   const std::array<const Texture::Coordinates, 3>& getTextureMappingCoordinates() const;
private:
   /**
    * The face's vertex indices.
    */
   const std::array<const uint32_t, 3> _indices;
   /**
    * The vertex normals.
    */
   const std::array<const clockwork::Vector3, 3> _normals;
   /**
    * The texture mapping coordinates.
    */
   const std::array<const Texture::Coordinates, 3> _textureMappingCoordinates;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::Face&);
