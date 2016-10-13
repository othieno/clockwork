/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#ifndef CLOCKWORK_WIREFRAME_RENDERER_HH
#define CLOCKWORK_WIREFRAME_RENDERER_HH

#include "Renderer.hh"


namespace clockwork {
/**
 *
 */
class WireframeRenderer : public Renderer<RenderingAlgorithm::Wireframe, WireframeRenderer> {
public:
	/**
	 * Sanitizes the rendering context and makes sure it is compatible with this renderer.
	 */
	static void sanitizeContext(RenderingContext&);
	/**
	 * Rearranges the specified set of vertices into a collection of geometric primitives.
	 */
	static void primitiveAssembly(const RenderingContext&, VertexArray&);
	/**
	 * Removes vertices that are not visible on the screen.
	 */
	static void clip(const RenderingContext&, VertexArray&);
	/**
	 * Generates fragments from the specified collection of vertices.
	 */
	static FragmentArray rasterize(const RenderingContext&, const VertexArray&);
private:
	/**
	 *
	 */
	static FragmentArray getBresenhamLineFragments(const Fragment&, const Fragment&);
	/**
	 *
	 */
	static FragmentArray getXiaolinWuLineFragments(const Fragment&, const Fragment&);
};
} // namespace clockwork

#endif // CLOCKWORK_WIREFRAME_RENDERER_HH
