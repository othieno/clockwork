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
#include "renderer.factory.hh"
#include "renderer.implementation.point.hh"
#include "renderer.implementation.wireframe.hh"
#include "renderer.implementation.random.hh"
#include "renderer.implementation.texture.hh"


clockwork::graphics::RendererFactory::RendererFactory() :
Factory(clockwork::graphics::Renderer::Type::Wireframe)
{
	put(clockwork::graphics::Renderer::Type::Point, new clockwork::graphics::PointRenderer);
	put(clockwork::graphics::Renderer::Type::Wireframe, new clockwork::graphics::WireframeRenderer);
	put(clockwork::graphics::Renderer::Type::Random, new clockwork::graphics::RandomRenderer);
	put(clockwork::graphics::Renderer::Type::Texture, new clockwork::graphics::TextureRenderer);
}


clockwork::graphics::RendererFactory&
clockwork::graphics::RendererFactory::getUniqueInstance()
{
	static clockwork::graphics::RendererFactory UNIQUE_INSTANCE;
	return UNIQUE_INSTANCE;
}
