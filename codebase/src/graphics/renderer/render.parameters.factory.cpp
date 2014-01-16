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
#include "render.parameters.factory.hh"
#include "point.render.parameters.hh"
#include "wireframe.render.parameters.hh"
#include "random.render.parameters.hh"
//#include "depth.render.parameters.hh"
//#include "normals.render.parameters.hh"
#include "texture.render.parameters.hh"
//#include "constant.render.parameters.hh"
//#include "phong.render.parameters.hh"
//#include "cel.render.parameters.hh"
//#include "bump.render.parameters.hh"
//#include "deferred.render.parameters.hh"


clockwork::graphics::RenderParametersFactory::RenderParametersFactory() :
Factory(clockwork::graphics::RenderParameters::Type::Wireframe)
{
   put(clockwork::graphics::RenderParameters::Type::Point, new clockwork::graphics::PointRenderParameters);
   put(clockwork::graphics::RenderParameters::Type::Wireframe, new clockwork::graphics::WireframeRenderParameters);
   put(clockwork::graphics::RenderParameters::Type::Random, new clockwork::graphics::RandomRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Depth, new clockwork::graphics::DepthRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Normals, new clockwork::graphics::NormalsRenderParameters);
   put(clockwork::graphics::RenderParameters::Type::Texture, new clockwork::graphics::TextureRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Constant, new clockwork::graphics::ConstantRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Phong, new clockwork::graphics::PhongRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Cel, new clockwork::graphics::CelRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Bump, new clockwork::graphics::BumpRenderParameters);
   //put(clockwork::graphics::RenderParameters::Type::Deferred, new clockwork::graphics::DeferredRenderParameters);
}


clockwork::graphics::RenderParametersFactory&
clockwork::graphics::RenderParametersFactory::getUniqueInstance()
{
   static clockwork::graphics::RenderParametersFactory UNIQUE_INSTANCE;
   return UNIQUE_INSTANCE;
}
