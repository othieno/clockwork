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

#include <iostream>
#include "fragment.hh"
#include "factory.hh"
#include "matrix4.hh"
#include "model3d.hh"
#include "viewport.hh"
#include <functional>


/**
 * @see scene.object.hh and scene.viewer.hh.
 */
namespace clockwork { namespace scene { class Object; class Viewer; } }

namespace clockwork {
namespace graphics {

/**
 * @see primitive.mode.hh.
 */
class PrimitiveMode;

/**
 * @see line.algorithm.hh.
 */
class LineAlgorithm;


class RenderAlgorithm
{
public:
   /**
    * Available render algorithm identifiers.
    */
   enum class Identifier
   {
      Point,
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
    * Render parameters.
    */
   struct Parameters
   {
   friend class RenderAlgorithm;
   private:
      Parameters
      (
         const clockwork::graphics::Model3D&,
         const clockwork::graphics::Material&,
         const clockwork::Matrix4& MODEL,
         clockwork::scene::Viewer&
      );
      // TODO Uncomment and fix!
//      Parameters(const Parameters&) = delete;
      Parameters& operator=(const Parameters&) = delete;
   public:
      const Model3D& model3D;
      const Material& material;
      const clockwork::Point3& viewpoint;
      const clockwork::graphics::Viewport& viewport;

      const clockwork::graphics::PrimitiveMode& primitiveMode;
      const clockwork::graphics::LineAlgorithm& lineAlgorithm;

      const clockwork::Matrix4& MODEL;
      const clockwork::Matrix4  INVERSE_MODEL;
      const clockwork::Matrix4& VIEW;
      const clockwork::Matrix4  MODELVIEW;
      const clockwork::Matrix4& PROJECTION;
      const clockwork::Matrix4& VIEWPROJECTION;
      const clockwork::Matrix4  MODELVIEWPROJECTION;
      const clockwork::Matrix4  NORMAL;
   };
   /**
    * Return the algorithm's identifier.
    */
   const RenderAlgorithm::Identifier& getIdentifier() const;
   /**
    * Apply this algorithm to a scene object that is observed by a given viewer.
    * @param object the scene object to render.
    * @param viewer the viewer from which the object is being observed.
    */
   void apply(clockwork::scene::Object& object, clockwork::scene::Viewer& viewer) const;
protected:
   /**
    * Instantiate a render algorithm with a given identifier.
    * @param identifier the render algorithm's identifier.
    */
   RenderAlgorithm(const RenderAlgorithm::Identifier& identifier);
   /**
    * The vertex program is responsible for transforming a vertex position from object to clip space.
    * @param parameters the render parameters.
    * @param position the vertex's position in object space.
    * @param normal the vertex's normal in object space.
    * @param uvmap the vertex's texture mapping coordinates.
    */
   virtual Vertex vertexProgram
   (
      const RenderAlgorithm::Parameters& parameters,
      const clockwork::Point3& position,
      const clockwork::Vector3& normal,
      const Texture::Coordinates& uvmap
   ) const;
   /**
    * TODO Explain me.
    */
   virtual VertexArray& primitiveAssembly(const clockwork::graphics::PrimitiveMode&, VertexArray&) const = 0;
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
   virtual VertexArray& geometryProgram(const RenderAlgorithm::Parameters& parameters, VertexArray& vertices) const;
   /**
    * Perform point, line or polygon clipping on a collection of primitives.
    * @param primitives the primitives to clip.
    */
   virtual VertexArray& clip(VertexArray& vertices) const = 0;
   /**
    * Rasterise primitives with a given set of parameters.
    * @param parameters the render parameters.
    * @param vertices the vertices that form the primitives to rasterise.
    */
   virtual void rasterise(const RenderAlgorithm::Parameters& parameters, const VertexArray& vertices) const = 0;
   /**
    * The fragment program calculates an RGBA color from given fragment attributes.
    * @param parameters the render parameters.
    * @param fragment the fragment used to calculate a color.
    */
   virtual uint32_t fragmentProgram(const RenderAlgorithm::Parameters& parameters, const Fragment& fragment) const;
   /**
    * @see Framebuffer::plot(2).
    */
   void plot(const Fragment& f, const std::function<uint32_t(const Fragment&)> fop) const;
   /**
    * @see Framebuffer::plot(3).
    */
   void plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t color) const;
private:
   /**
    * The render algorithm's identifier.
    */
   const RenderAlgorithm::Identifier _identifier;
};


/**
 * The RenderAlgorithmFactory is a factory that creates and stores RenderAlgorithm objects.
 */
class RenderAlgorithmFactory : public clockwork::Factory<RenderAlgorithm::Identifier, const RenderAlgorithm*>
{
public:
   static RenderAlgorithmFactory& getInstance();
private:
   RenderAlgorithmFactory();
   RenderAlgorithmFactory(const RenderAlgorithmFactory&) = delete;
   RenderAlgorithmFactory& operator=(const RenderAlgorithmFactory&) = delete;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::RenderAlgorithm::Identifier&);
