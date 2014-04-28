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
#include "model3d.hh"

using clockwork::graphics::Model3D;


Model3D::Model3D()
{}


Model3D::Model3D(const std::vector<clockwork::Point3>& positions, const std::vector<Face>& faces, const Material& material) :
_positions(positions),
_faces(faces),
_material(material)
{}


const std::vector<clockwork::Point3>&
Model3D::getVertexPositions() const
{
   return _positions;
}


const std::vector<clockwork::graphics::Face>&
Model3D::getFaces() const
{
   return _faces;
}


void
Model3D::addFace
(
   const std::array<const uint32_t, 3>& indices,
   const std::array<const clockwork::Vector3, 3>& normals,
   const std::array<const Texture::Coordinates, 3>& texcoords
)
{
   _faces.push_back(Face(indices, normals, texcoords));
}


const clockwork::graphics::Material&
Model3D::getMaterial() const
{
   return _material;
}


bool
Model3D::isEmpty() const
{
   return _positions.empty() || _faces.empty();
}
