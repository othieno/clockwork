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
#include "face.hh"
#include "model3d.hh"

using clockwork::graphics::Face;


Face::Face
(
   const std::array<const uint32_t, 3>& indices,
   const std::array<const clockwork::Vector3, 3>& normals,
   const std::array<const Texture::Coordinates, 3>& texcoords
) :
_indices(indices),
_normals(normals),
_textureMappingCoordinates(texcoords)
{}


Face::Face(const std::array<const uint32_t, 3>& indices) :
Face
(
   indices,
   {clockwork::Vector3(), clockwork::Vector3(), clockwork::Vector3()},
   {Texture::Coordinates(), Texture::Coordinates(), Texture::Coordinates()}
)
{}


const std::array<const uint32_t, 3>&
Face::getIndices() const
{
   return _indices;
}


const std::array<const clockwork::Vector3, 3>&
Face::getNormals() const
{
   return _normals;
}


const std::array<const clockwork::graphics::Texture::Coordinates, 3>&
Face::getTextureMappingCoordinates() const
{
   return _textureMappingCoordinates;
}
