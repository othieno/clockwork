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
#include "render.parameters.hh"
#include "services.hh"
#include "scene.viewer.hh"
#include "rigid.body.hh"

using clockwork::graphics::RenderParameters;


RenderParameters::Uniforms::Uniforms(const clockwork::physics::RigidBody& body, const clockwork::scene::Viewer& viewer) :
MODEL(body.getModelMatrix()),
INVERSE_MODEL(clockwork::Matrix4::inverse(MODEL)),
VIEW(viewer.getViewMatrix()),
MODELVIEW(VIEW * MODEL),
PROJECTION(viewer.getProjectionMatrix()),
VIEWPROJECTION(viewer.getViewProjectionMatrix()),
MODELVIEWPROJECTION(VIEWPROJECTION * MODEL),
NORMAL(clockwork::Matrix4::transpose(clockwork::Matrix4::inverse(MODELVIEW))),
viewpoint(viewer.getPosition())
{}


RenderParameters::RenderParameters(const RenderParameters::Type& type) :
_type(type)
{}


const RenderParameters::Type&
RenderParameters::getType() const
{
   return _type;
}


clockwork::graphics::Vertex
RenderParameters::vertexProgram
(
   const RenderParameters::Uniforms& uniforms,
   const clockwork::Point3& position,
   const clockwork::Vector3&,
   const Texture::Coordinates& uvmap
) const
{
   // Set the vertex's position in clip space, as well as its texture mapping coordinates.
   Vertex output(uniforms.MODELVIEWPROJECTION * clockwork::Point4(position));
   output.uvmap = uvmap;

   return output;
}


clockwork::graphics::VertexArray&
RenderParameters::primitiveAssembly(VertexArray& vertices) const
{
   return vertices;
}


clockwork::graphics::VertexArray&
RenderParameters::backfaceCulling(VertexArray& vertices) const
{
   return vertices;
}


clockwork::graphics::VertexArray&
RenderParameters::occlusionCulling(VertexArray& vertices) const
{
   //TODO Implement me.
   return vertices;
}


clockwork::graphics::VertexArray&
RenderParameters::geometryProgram(const RenderParameters::Uniforms&, VertexArray& vertices) const
{
   return vertices;
}


uint32_t
RenderParameters::fragmentProgram(const RenderParameters::Uniforms&, const Fragment& f) const
{
   return f.color;
}
