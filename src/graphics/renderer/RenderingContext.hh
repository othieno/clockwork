/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
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
#ifndef CLOCKWORK_RENDERING_CONTEXT_HH
#define CLOCKWORK_RENDERING_CONTEXT_HH

#include "Framebuffer.hh"
#include "PrimitiveTopology.hh"
#include "ShadeModel.hh"
#include "PolygonMode.hh"
#include "LineDrawingAlgorithm.hh"
#include "Uniform.hh"


namespace clockwork {
/**
 *
 */
struct RenderingContext {
	/**
	 * The framebuffer.
	 */
	Framebuffer framebuffer;
	/**
	 * The polygon mode.
	 */
	PolygonMode polygonMode;
	/**
	 * The primitive topology.
	 */
	PrimitiveTopology primitiveTopology;
	/**
	 * Enables clipping if set to true, disables it otherwise.
	 */
	bool enableClipping;
	/**
	 * Enables backface culling if set to true, disables it otherwise.
	 */
	bool enableBackfaceCulling;
	/**
	 * The shade model.
	 */
	ShadeModel shadeModel;
	/**
	 * The line drawing algorithm used by the Wireframe renderer.
	 */
	LineDrawingAlgorithm lineDrawingAlgorithm;
	/**
	 * The set of uniform variables used by the shader programs.
	 */
	Uniforms uniforms;
	/**
	 * If set to true, a scissor test will be performed on each fragment before
	 * it's written to the framebuffer.
	 */
	bool enableScissorTest;
	/**
	 * If set to true, a stencil test will be performed on each fragment before
	 * it's written to the framebuffer.
	 */
	bool enableStencilTest;
	/**
	 * If set to true, a depth test will be performed on each fragment before
	 * it's written to the framebuffer.
	 */
	bool enableDepthTest;
	/**
	 * The viewport transformation matrix.
	 */
	QMatrix2x3 viewportTransform;
};
} // namespace clockwork

#endif // CLOCKWORK_RENDERING_CONTEXT_HH
