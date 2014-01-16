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
#include "model3d.hh"

clockwork::graphics::Model3D::Model3D()
{}


clockwork::graphics::Model3D::Model3D
(
   const std::vector<clockwork::graphics::Vertex>& vertices,
   const std::vector<clockwork::graphics::Face>& faces,
   const clockwork::graphics::Material& material
) :
_vertices(vertices),
_faces(faces),
_material(material)
{}


const std::vector<clockwork::graphics::Vertex>&
clockwork::graphics::Model3D::getVertices() const
{
   return _vertices;
}


const std::vector<clockwork::graphics::Face>&
clockwork::graphics::Model3D::getFaces() const
{
   return _faces;
}


void
clockwork::graphics::Model3D::addFace
(
   const std::array<const uint32_t, 3>& indices,
   const std::array<const clockwork::graphics::Face::TextureCoordinates, 3>& textureCoordinates
)
{
   _faces.push_back(clockwork::graphics::Face(*this, indices, textureCoordinates));
}


const clockwork::graphics::Material&
clockwork::graphics::Model3D::getMaterial() const
{
   return _material;
}


bool
clockwork::graphics::Model3D::empty() const
{
   return _vertices.empty() || _faces.empty();
}
