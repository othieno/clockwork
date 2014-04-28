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

#include "resource.hh"
#include "face.hh"
#include "material.hh"
#include <vector>


namespace clockwork {
namespace graphics {

class Model3D : public clockwork::system::Resource
{
public:
   /**
    * The default constructor.
    */
   Model3D();
   /**
    * Instantiate a 3D model with a given set of vertex positions, triangular polygonal faces,
    * and a material.
    * @param positions the model's vertex position data.
    * @param faces the model's polygonal face data.
    * @param material the model's material data.
    */
   Model3D(const std::vector<clockwork::Point3>& positions, const std::vector<Face>& faces, const Material& material);
   /**
    * Return the model's vertex position data.
    */
   const std::vector<clockwork::Point3>& getVertexPositions() const;
   /**
    * Return the model's triangular polygonal face data.
    */
   const std::vector<Face>& getFaces() const;
   /**
    * Add a polygonal face.
    * @param indices the face's index list.
    * @param indices the face's vertex normals.
    * @param textureMappingCoordinates the face's texture mapping coordinates.
    */
   void addFace
   (
      const std::array<const uint32_t, 3>& indices,
      const std::array<const clockwork::Vector3, 3>& normals,
      const std::array<const Texture::Coordinates, 3>& textureMappingCoordinates
   );
   /**
    * Return the model's material data.
    */
   const Material& getMaterial() const;
   /**
    * Return true if this container does not have any vertices or faces, false otherwise.
    */
   bool isEmpty() const;
private:
   /**
    * The 3D model's vertex positions.
    */
   std::vector<clockwork::Point3> _positions;
   /**
    * The 3D model's polygonal face data.
    */
   std::vector<Face> _faces;
   /**
    * The 3D model's material data.
    */
   Material _material;
};

} // namespace graphics
} // namespace clockwork
