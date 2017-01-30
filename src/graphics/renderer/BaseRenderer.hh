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
#ifndef CLOCKWORK_BASE_RENDERER_HH
#define CLOCKWORK_BASE_RENDERER_HH

#include "RenderingContext.hh"


namespace clockwork {
/**
 * @see BaseFragment.hh.
 */
struct BaseFragment;
/**
 *
 */
class BaseRenderer {
protected:
	/**
	 * Instantiates a BaseRenderer object.
	 */
	BaseRenderer() = default;
	/**
	 * Performs tests to check whether the specified fragment can be written to the
	 * framebuffer. If the fragment passes all tests, an index to a location in the
	 * framebuffer where the fragment can be written to is returned. If a test fails
	 * however, -1 is returned.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static int fragmentPasses(const RenderingContext& context, const BaseFragment& fragment);
private:
	/**
	 * Returns true if the specified fragment passes the pixel-ownership test, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPassesPixelOwnershipTest(
		const RenderingContext& context,
		const BaseFragment& fragment
	);
	/**
	 * Returns true if the specified fragment passes the scissor test, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPassesScissorTest(
		const RenderingContext& context,
		const BaseFragment& fragment
	);
	/**
	 * Returns true if the specified fragment passes the stencil test, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPassesStencilTest(
		const RenderingContext& context,
		const BaseFragment& fragment
	);
	/**
	 * Returns true if the specified fragment passes the depth test, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPassesDepthTest(
		const RenderingContext& context,
		const BaseFragment& fragment
	);
};
} // namespace clockwork

#endif // CLOCKWORK_BASE_RENDERER_HH
