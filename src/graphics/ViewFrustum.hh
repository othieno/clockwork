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
#ifndef CLOCKWORK_VIEW_FRUSTUM_HH
#define CLOCKWORK_VIEW_FRUSTUM_HH

#include <QVector3D>


namespace clockwork {
/**
 *
 */
struct ViewFrustum {
	/**
	 * Instantiates a ViewFrustum object.
	 */
	ViewFrustum();
	/**
	 * The frustum's origin which is also a viewer's reference point, i.e. the
	 * position that it is looking at.
	 */
	QVector3D center;
	/**
	 * The field of view angle, in degrees, in the Y direction.
	 */
	qreal fieldOfView;
	/**
	 * The ratio of width to height that determines the field of view in the X direction.
	 */
	qreal aspectRatio;
	/**
	 * The vector on the view plane that indicates the upward direction.
	 */
	QVector3D up;
	/**
	 * The distance to the near depth clipping plane.
	 */
	qreal nearClippingPlaneDistance;
	/**
	 * The distance to the far depth clipping plane.
	 */
	qreal farClippingPlaneDistance;
};
} // namespace clockwork

#endif // CLOCKWORK_VIEW_FRUSTUM_HH
