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

#include "renderer.hh"
#include <list>
#include "fragment.hh"


namespace clockwork {
namespace graphics {

/**
 * @see renderer.factory.hh.
 */
class RendererFactory;

class WireframeRenderer : public clockwork::graphics::Renderer
{
public:
	/**
	 * Line algorithms.
	 */
	enum class LineAlgorithm
	{
		Bresenham,
		XiaolinWu
	};
	/**
	 * @see Renderer::createRenderTask.
	 */
	virtual clockwork::concurrency::RenderTask* createRenderTask
	(
		const clockwork::physics::RigidBody&,
		const clockwork::scene::Viewer&
	) const override final;
	/**
	 * Return the line algorithm used during rendering.
	 */
	const WireframeRenderer::LineAlgorithm& getLineAlgorithm() const;
	/**
	 * Return a list of available line algorithms.
	 */
	std::list<WireframeRenderer::LineAlgorithm> getLineAlgorithmList() const;
	/**
	 * Set the line algorithm used during rendering.
	 * @param algorithm the line algorithm to set.
	 */
	void setLineAlgorithm(const WireframeRenderer::LineAlgorithm& algorithm);
	/**
	 * Draw a line between two fragments using Bresenham's line algorithm.
	 * @param f0 the line's origin.
	 * @param f1 the line's endpoint.
	 */
	void drawlineBresenham(const clockwork::graphics::Fragment& f0, const clockwork::graphics::Fragment& f1) const;
	/**
	 * Draw a line between two fragments using Xiaolin Wu's line algorithm.
	 * @param f0 the line's origin.
	 * @param f1 the line's endpoint.
	 */
	void drawlineXiaolinWu(const clockwork::graphics::Fragment& f0, const clockwork::graphics::Fragment& f1) const;
private:
	/**
	 * The line algorithm to use during rendering.
	 */
	WireframeRenderer::LineAlgorithm _lineAlgorithm;
	/**
	 * The default constructor. A renderer can only be instantiated by the renderer
	 * factory, as such the default constructor is private.
	 */
	WireframeRenderer();
	/**
	 * A renderer cannot be copied.
	 */
	WireframeRenderer(const WireframeRenderer&) = delete;
	WireframeRenderer& operator=(const WireframeRenderer&) = delete;
	/**
	 * Friendship between the renderer factory and this renderer.
	 */
	friend clockwork::graphics::RendererFactory;
};

} // namespace graphics
} // namespace clockwork
