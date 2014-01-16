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

#include "vertex.hh"
#include <array>


namespace clockwork {
namespace graphics {

/**
 * @see model3d.hh
 */
class Model3D;

/**
 * TODO Explain me.
 */
class Face
{
public:
   /**
    * Texture mapping coordinates.
    */
   struct TextureCoordinates
   {
      double u, v;
      /**
       * Instantiate texture mapping coordinates with the given U and V pair.
       */
      TextureCoordinates(const double& u = 0, const double& v = 0);
   };
   /**
    * Instantiate a face with given list of vertex indices and texture mapping coordinates,
    * that is bound to a 3D model.
    * @param model3D the 3D model that owns this polygonal face.
    * @param indices the list of vertices that make up this face.
    * @param texcoords the face's texture mapping coordinates.
    */
   Face
   (
      const Model3D& model3D,
      const std::array<const uint32_t, 3>& indices,
      const std::array<const Face::TextureCoordinates, 3>& textureCoordinates
   );
   /**
    * Instantiate a face with a given list of vertex indices, that is bound to a 3D model.
    * @param model3D the 3D model that owns this polygonal face.
    * @param indices the face's vertices.
    */
   Face(const Model3D& model3D, const std::array<const uint32_t, 3>& indices);
   /**
    * Return the vertices that belong to this polygonal face.
    */
   std::array<const Vertex*, 3> getVertices() const;
   /**
    * Return the face's texture coordinates.
    */
   const std::array<const Face::TextureCoordinates, 3>& getTextureCoordinates() const;
   /**
    * Return the face's surface normal.
    */
   const clockwork::Vector3& getNormal() const;
   /**
    * Return the face's center.
    */
   const clockwork::Point3& getCenter() const;
private:
   /**
    * The 3D model that owns this polygonal face.
    */
   const clockwork::graphics::Model3D& _model3D;
   /**
    * The face's vertex indices.
    */
   const std::array<const uint32_t, 3> _indices;
   /**
    * The face's mapping coordinates.
    */
   const std::array<const Face::TextureCoordinates, 3> _textureCoordinates;
   /**
    * The face's surface normal.
    */
   const clockwork::Vector3 _normal;
   /**
    * The face's center.
    */
   const clockwork::Point3 _center;
};

} // namespace graphics
} // namespace clockwork
