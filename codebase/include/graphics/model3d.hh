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
#pragma once

#include "asset.hh"
#include "face.hh"
#include "material.hh"
#include <vector>


namespace clockwork {
namespace graphics {

class Model3D : public clockwork::io::Asset
{
public:
   /**
    * The default constructor.
    */
   Model3D();
   /**
    * Instantiate a 3D model with a given set of vertices, polygonal faces
    * and a material.
    * @param vertices the model's vertex data.
    * @param faces the model's polygonal face data.
    * @param material the model's material data.
    */
   Model3D(const std::vector<Vertex>& vertices, const std::vector<Face>& faces, const Material& material);
   /**
    * Return the model's vertex data.
    */
   const std::vector<Vertex>& getVertices() const;
   /**
    * Return the model's polygonal face data.
    */
   const std::vector<Face>& getFaces() const;
   /**
    * Add a polygonal face.
    * @param indices the face's index list.
    * @param textureCoordinates the face's texture mapping coordinates.
    */
   void addFace
   (
      const std::array<const uint32_t, 3>& indices,
      const std::array<const Face::TextureCoordinates, 3>& textureCoordinates
   );
   /**
    * Return the model's material data.
    */
   const Material& getMaterial() const;
   /**
    * Return true if this container does not have any vertices or faces, false otherwise.
    */
   bool empty() const;
private:
   /**
    * The 3D model's vertex data.
    */
   std::vector<Vertex> _vertices;
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
