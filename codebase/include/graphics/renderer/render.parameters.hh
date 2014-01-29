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

#include <iostream>
#include <array>
#include <functional>
#include "fragment.hh"
#include "services.hh"
#include "model3d.hh"


namespace clockwork {

/**
 * @see scene.viewer.hh.
 */
namespace scene { class Viewer; }

/**
 * @see rigid.body.hh.
 */
namespace physics { class RigidBody; }

namespace graphics {

class RenderParameters
{
public:
   /**
    * Available types of renders.
    */
   enum class Type
   {
      Point,
      Line,
      Wireframe,
      Random,
      Depth,
      Normals,
      Texture,
      Constant,
      Phong,
      Cel,
      Bump,
      Deferred
   };
   /**
    * TODO Explain me.
    */
   struct Uniforms
   {
      /**
       * TODO Explain me.
       */
      Uniforms(const clockwork::physics::RigidBody& body, const clockwork::scene::Viewer& viewer);
      /**
       * The rigid body's model transformation matrix.
       */
      const clockwork::Matrix4& MODEL;
      /**
       * The inverse MODEL matrix.
       */
      const clockwork::Matrix4 INVERSE_MODEL;
      /**
       * The viewer's view transformation matrix.
       */
      const clockwork::Matrix4& VIEW;
      /**
       * The MODEL-VIEW transformation matrix.
       */
      const clockwork::Matrix4 MODELVIEW;
      /**
       * The viewer's projection transformation matrix.
       */
      const clockwork::Matrix4& PROJECTION;
      /**
       * The view-projection transformation matrix.
       */
      const clockwork::Matrix4& VIEWPROJECTION;
      /**
       * The MODEL-VIEW-PROJECTION transformation matrix.
       */
      const clockwork::Matrix4 MODELVIEWPROJECTION;
      /**
       * The normals transformation matrix.
       */
      const clockwork::Matrix4 NORMAL;
      /**
       * The viewer's position in world space.
       */
      const clockwork::Point3& viewpoint;
   };
   /**
    * Return the type of render performed by these parameters.
    */
   const Type& getType() const;
   /**
    * The vertex program is responsible for primarily transforming a vertex position from
    * object (model) to clip space.
    * @param uniform uniform values.
    * @param position the vertex's position in object space.
    * @param normal the vertex's normal in object space.
    * @param uvmap the vertex's texture mapping coordinates.
    */
   virtual Vertex vertexProgram
   (
      const RenderParameters::Uniforms& uniforms,
      const clockwork::Point3& position,
      const clockwork::Vector3& normal,
      const Texture::Coordinates& uvmap
   ) const;
   /**
    * The primitive assembly operation creates point, line or polygon primitives from a
    * collection of vertices in clip space.
    * @param vertices the collection of vertices that will be considered primitives.
    */
   virtual VertexArray& primitiveAssembly(VertexArray& vertices) const;
   /**
    * Perform backface culling to remove triangular primitives that are not facing the viewer,
    * i.e. surfaces that are not visible to the viewer.
    * @param vertices the vertices to cull.
    */
   virtual VertexArray& backfaceCulling(VertexArray& vertices) const;
   /**
    * Perform occlusion culling to remove primitives that are occluded from the viewer by other primitives.
    * @param vertices the vertices to cull.
    */
   VertexArray& occlusionCulling(VertexArray& vertices) const;
   /**
    * TODO Explain me.
    */
   virtual VertexArray& geometryProgram(const RenderParameters::Uniforms& uniforms, VertexArray& vertices) const;
   /**
    * Perform point, line or polygon clipping on a collection of primitives.
    * @param primitives the primitives to clip.
    */
   virtual VertexArray& clip(VertexArray& vertices) const = 0;
   /**
    * Rasterise primitives.
    * @param uniforms uniform values.
    * @param vertices the vertices that form the primitives to rasterise.
    */
   virtual void rasterise(const RenderParameters::Uniforms& uniforms, const VertexArray& vertices) const = 0;
   /**
    * The fragment program calculates a color from given fragment attributes.
    * @param uniforms uniform values.
    * @param fragment the fragment used to calculate a color.
    */
   virtual uint32_t fragmentProgram(const RenderParameters::Uniforms& uniforms, const Fragment& fragment) const;
protected:
   /**
    * Instantiate a render parameter set.
    * @param type the type of render performed by this set of parameters.
    */
   RenderParameters(const Type& type);
   /**
    * @see Framebuffer::plot(2).
    */
   inline void plot(const Fragment& f, const std::function<uint32_t(const Fragment&)> fop) const
   {
      clockwork::system::Services::Graphics.plot(f, fop);
   }
   /**
    * @see Framebuffer::plot(3).
    */
   inline void plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t color) const
   {
      clockwork::system::Services::Graphics.plot(x, y, z, color);
   }
private:
   /**
    * The type of render performed by these parameters.
    */
   const Type _type;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::RenderParameters::Type&);
