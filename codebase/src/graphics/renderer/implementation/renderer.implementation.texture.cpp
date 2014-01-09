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
#include "renderer.implementation.texture.hh"
#include "texture.filter.factory.hh"
#include "texture.render.task.hh"


clockwork::graphics::TextureRenderer::TextureRenderer() :
PolygonRenderer(clockwork::graphics::Renderer::Type::Texture),
_textureFilter(clockwork::graphics::TextureFilterFactory::getUniqueInstance().getDefaultValue())
{}


void
clockwork::graphics::TextureRenderer::setTextureFilter(const clockwork::graphics::TextureFilter::Type& type)
{
	if (_textureFilter != nullptr && _textureFilter->getType() == type)
		return;

	_textureFilter = clockwork::graphics::TextureFilterFactory::getUniqueInstance().get(type);
}


clockwork::concurrency::RenderTask*
clockwork::graphics::TextureRenderer::createRenderTask
(
	const clockwork::physics::RigidBody& body,
	const clockwork::scene::Viewer& viewer
) const
{
	return new clockwork::concurrency::TextureRenderTask(body, viewer);
}
