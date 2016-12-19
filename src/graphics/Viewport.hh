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
#ifndef CLOCKWORK_VIEWPORT_HH
#define CLOCKWORK_VIEWPORT_HH

#include <QVector3D>


namespace clockwork {
/**
 * @see Framebuffer.hh.
 */
class Framebuffer;
/**
 * A normalised viewport with values that range from 0.0 (minimum) to 1.0 (maximum).
 */
struct Viewport
{
	/**
	 * The viewport's horizontal origin.
	 */
	double x;
	/**
	 * The viewport's vertical origin.
	 */
	double y;
	/**
	 * The viewport's width.
	 */
	double width;
	/**
	 * The viewport's height.
	 */
	double height;
	/**
	 * The linear mapping of the near clipping plane to the window coordinates.
	 * @see glDepthRange documentation
	 */
	double near;
	/**
	 * The linear mapping of the far clipping plane to the window coordinates.
	 * @see glDepthRange documentation
	 */
	double far;
	/**
	 * Instantiate a viewport with a given origin, width and height.
	 * @param x the viewport's origin on the horizontal axis.
	 * @param y the viewport's origin on the vertical axis.
	 * @param width the viewport's width.
	 * @param height the viewport's height.
	 * @param near the linear mapping of the near clipping plane to the window coordinates.
	 * @param far the linear mapping of the far clipping plane to the window coordinates.
	 */
	Viewport(
		const double x = 0.0,
		const double y = 0.0,
		const double width = 1.0,
		const double height = 1.0,
		const double near = 0.0,
		const double far = 1.0
	);
};
/**
 * The viewport transform converts points in normalized device coordinates space
 * to window space, thereby scaling and translating the coordinates to fit into
 * the rendering screen.
 */
struct ViewportTransform {
	/**
	 * Instantiates a ViewportTransform object.
	 */
	ViewportTransform();
	/**
	 * Instantiates a ViewportTransform object based on the parameters of the
	 * specified normalized viewport and framebuffer.
	 */
	ViewportTransform(const Viewport&, const Framebuffer&);
	/**
	 * The scaling factor.
	 */
	QVector3D scale;
	/**
	 * The translation factor.
	 */
	QVector3D translate;
};
} // namespace clockwork

#endif // CLOCKWORK_VIEWPORT_HH
