/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
#include "BaseRenderer.hh"
#include "BaseFragment.hh"

using clockwork::BaseRenderer;


int
BaseRenderer::fragmentPasses(const RenderingContext& context, const BaseFragment& fragment) {
	const bool passes =
		fragmentPassesPixelOwnershipTest(context, fragment) &&
		fragmentPassesScissorTest(context, fragment) &&
		fragmentPassesStencilTest(context, fragment) &&
		fragmentPassesDepthTest(context, fragment);

	return passes ? context.framebuffer.getOffset(fragment.x, fragment.y) : -1;
}


bool
BaseRenderer::fragmentPassesPixelOwnershipTest(
	const RenderingContext& context,
	const BaseFragment& fragment
) {
	return true;
}


bool
BaseRenderer::fragmentPassesScissorTest(
	const RenderingContext& context,
	const BaseFragment& fragment
) {
	bool passes = true;
	if (context.enableScissorTest) {
	}
	return passes;
}


bool
BaseRenderer::fragmentPassesStencilTest(
	const RenderingContext& context,
	const BaseFragment& fragment
) {
	bool passes = true;
	if (context.enableStencilTest) {
	}
	return passes;
}


bool
BaseRenderer::fragmentPassesDepthTest(
	const RenderingContext& context,
	const BaseFragment& fragment
) {
	bool passes = true;
	if (context.enableDepthTest) {
		const std::size_t index = context.framebuffer.getOffset(fragment.x, fragment.y);
		passes = fragment.z < context.framebuffer.getDepthBuffer()[index];
	}
	return passes;
}
