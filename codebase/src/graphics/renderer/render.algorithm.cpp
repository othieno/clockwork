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
#include "point.render.algorithm.hh"
#include "wireframe.render.algorithm.hh"
#include "random.shading.render.algorithm.hh"
#include "depth.map.render.algorithm.hh"
#include "normal.map.render.algorithm.hh"
#include "texture.map.render.algorithm.hh"
#include "constant.shading.render.algorithm.hh"
#include "phong.shading.render.algorithm.hh"
#include "cel.shading.render.algorithm.hh"
#include "bump.map.render.algorithm.hh"
#include "deferred.render.algorithm.hh"
#include "services.hh"
#include "scene.viewer.hh"
#include "property.appearance.hh"
#include "primitive.mode.hh"


using clockwork::graphics::RenderAlgorithm;
using clockwork::graphics::RenderAlgorithmFactory;


RenderAlgorithm::Parameters::Parameters
(
   const clockwork::graphics::Model3D& mod3d,
   const clockwork::graphics::Material& mat,
   const clockwork::Matrix4& modelTransform,
   clockwork::scene::Viewer& viewer
) :
model3D(mod3d),
material(mat),
viewpoint(viewer.getPosition()),
viewport(viewer.getViewport()),
primitiveMode(*clockwork::graphics::PrimitiveModeFactory::getInstance().get(viewer.getPrimitiveMode())),
lineAlgorithm(*clockwork::graphics::LineAlgorithmFactory::getInstance().get(viewer.getLineAlgorithm())),
MODEL(modelTransform),
INVERSE_MODEL(clockwork::Matrix4::inverse(MODEL)),
VIEW(viewer.getViewTransform()),
MODELVIEW(VIEW * MODEL),
PROJECTION(viewer.getProjectionTransform()),
VIEWPROJECTION(viewer.getViewProjectionTransform()),
MODELVIEWPROJECTION(VIEWPROJECTION * MODEL),
NORMAL(clockwork::Matrix4::transpose(clockwork::Matrix4::inverse(MODELVIEW)))
{}


RenderAlgorithm::RenderAlgorithm(const RenderAlgorithm::Identifier& identifier) :
_identifier(identifier)
{}


const RenderAlgorithm::Identifier&
RenderAlgorithm::getIdentifier() const
{
   return _identifier;
}


void
RenderAlgorithm::apply(clockwork::scene::Object& object, clockwork::scene::Viewer& viewer) const
{
   using clockwork::scene::Appearance;
   using clockwork::scene::Property;

   const auto* appearance =
   static_cast<const Appearance*>(object.getProperty(Property::Identifier::Appearance));
   assert(appearance != nullptr);

   const auto* model3D = appearance->getModel3D();
   assert(model3D != nullptr && !model3D->isEmpty());

   const auto& material = appearance->getMaterial();
   const auto& MODEL = object.getModelTransform();

   const RenderAlgorithm::Parameters parameters(*model3D, material, MODEL, viewer);

   VertexArray vertices;

   // Apply the vertex program to each position, normal and mapping coordinate attribute,
   // then store the resulting vertex.
   const auto& positions = model3D->getVertexPositions();
   for (const auto& face : model3D->getFaces())
   {
      const auto& indices = face.getIndices();
      const auto& normals = face.getNormals();
      const auto& uvmaps  = face.getTextureMappingCoordinates();

      for (unsigned int i = 0; i < 3; ++i)
      {
         const auto& index = indices[i];
         const auto& position = positions[index];
         const auto& normal = normals[i];
         const auto& uvmap = uvmaps[i];

         vertices.push_back(vertexProgram(parameters, position, normal, uvmap));
      }
   }

   // Create primitives and apply the geometry program to possibly generate more. Once
   // the geometry program completes, remove any hidden surfaces and continue down the
   // pipeline.
   if (!geometryProgram(parameters, primitiveAssembly(parameters.primitiveMode, vertices)).empty())
   {
      // Remove hidden surfaces.
      occlusionCulling(backfaceCulling(vertices));

      // Clip (remove) vertices that are not visible on the screen.
      clip(vertices);

      // Perform perspective-divide on the visible vertices. This will convert vertex
      // positions from clipping coordinate space to normalised device coordinate space.
      for (auto& vertex : vertices)
      {
         vertex.x /= vertex.w;
         vertex.y /= vertex.w;
         vertex.z /= vertex.w;
         vertex.w  = 1.0;
      }

      // Perform the viewport transform which converts vertex positions from normalised
      // device coordinate space to window coordinate space.
      const auto& framebuffer = clockwork::system::Services::Graphics.getFramebuffer();

      // TODO Fix viewport transform!
      const auto& viewport = parameters.viewport;
//      std::cout << "Rendering to " << viewport << std::endl;
      const auto& vpw = 0.5 * viewport.width * framebuffer.getWidth();
      const auto& vph = 0.5 * viewport.height * framebuffer.getHeight();

      for (auto& vertex : vertices)
      {
         vertex.x = std::round((vpw * vertex.x) + (viewport.x + vpw));
         vertex.y = std::round((vph * vertex.y) + (viewport.y + vph));
         vertex.z = ((viewport.far - viewport.near) * vertex.z * 0.5f) + (viewport.far + viewport.near) * 0.5;
      }
      rasterise(parameters, vertices);
   }
}


clockwork::graphics::Vertex
RenderAlgorithm::vertexProgram
(
   const RenderAlgorithm::Parameters& parameters,
   const clockwork::Point3& position,
   const clockwork::Vector3&,
   const Texture::Coordinates& uvmap
) const
{
   // Set the vertex's position in clip space, as well as its texture mapping coordinates.
   Vertex output(parameters.MODELVIEWPROJECTION * clockwork::Point4(position));
   output.uvmap = uvmap;

   return output;
}


clockwork::graphics::VertexArray&
RenderAlgorithm::backfaceCulling(VertexArray& vertices) const
{
   return vertices;
}


clockwork::graphics::VertexArray&
RenderAlgorithm::occlusionCulling(VertexArray& vertices) const
{
   return vertices;
}


clockwork::graphics::VertexArray&
RenderAlgorithm::geometryProgram(const RenderAlgorithm::Parameters&, VertexArray& vertices) const
{
   return vertices;
}


uint32_t
RenderAlgorithm::fragmentProgram(const RenderAlgorithm::Parameters&, const Fragment& f) const
{
   return f.color;
}


void
RenderAlgorithm::plot(const Fragment& f, const std::function<uint32_t(const Fragment&)> fop) const
{
   clockwork::system::Services::Graphics.plot(f, fop);
}


void
RenderAlgorithm::plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t color) const
{
   clockwork::system::Services::Graphics.plot(x, y, z, color);
}


RenderAlgorithmFactory::RenderAlgorithmFactory() :
Factory(RenderAlgorithm::Identifier::Normals)
{
   put(RenderAlgorithm::Identifier::Point, new PointRenderAlgorithm);
//   put(RenderAlgorithm::Identifier::Wireframe, new WireframeRenderAlgorithm);
   put(RenderAlgorithm::Identifier::Random, new RandomShadingRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Depth, new DepthMapRenderAlgorithm);
   put(RenderAlgorithm::Identifier::Normals, new NormalMapRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Texture, new TextureMapRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Constant, new ConstantShadingRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Phong, new PhongShadingRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Cel, new CelShadingRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Bump, new BumpMapRenderAlgorithm);
   //put(RenderAlgorithm::Identifier::Deferred, new DeferredRenderAlgorithm);
}


RenderAlgorithmFactory&
RenderAlgorithmFactory::getInstance()
{
   static clockwork::graphics::RenderAlgorithmFactory INSTANCE;
   return INSTANCE;
}
