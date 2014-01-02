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
#include "renderer.implementation.wireframe.hh"


clockwork::graphics::WireframeRenderer::WireframeRenderer() :
Renderer(clockwork::graphics::Renderer::Type::Wireframe),
_lineAlgorithm(clockwork::graphics::WireframeRenderer::LineAlgorithm::XiaolinWu)
{}


const clockwork::graphics::WireframeRenderer::LineAlgorithm&
clockwork::graphics::WireframeRenderer::getLineAlgorithm() const
{
	return _lineAlgorithm;
}


std::list<clockwork::graphics::WireframeRenderer::LineAlgorithm>
clockwork::graphics::WireframeRenderer::getLineAlgorithmList() const
{
	return
	{
		clockwork::graphics::WireframeRenderer::LineAlgorithm::Bresenham,
		clockwork::graphics::WireframeRenderer::LineAlgorithm::XiaolinWu,
	};
}


void
clockwork::graphics::WireframeRenderer::setLineAlgorithm(const clockwork::graphics::WireframeRenderer::LineAlgorithm& algorithm)
{
	_lineAlgorithm = algorithm;
}
