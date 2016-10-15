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
#ifndef CLOCKWORK_POINT4_HH
#define CLOCKWORK_POINT4_HH


#include "Point3.hh"


namespace clockwork {
/*
 * @see graphics/Viewport.hh.
 */
struct ViewportTransform;
/**
 *
 */
struct Point4 {
	/**
	 * The point's x coordinate.
	 */
	double x;
	/**
	 * The point's y coordinate.
	 */
	double y;
	/**
	 * The point's z coordinate.
	 */
	double z;
	/**
	 * The point's w coordinate.
	 */
	double w;
	/**
	 * Instantiate a 3D homogeneous point from a set of X, Y, Z, and W coordinates.
	 * @param x the point's X coordinate.
	 * @param y the point's Y coordinate.
	 * @param z the point's Z coordinate.
	 * @param w the point's W coordinate.
	 */
	Point4(const double x = 0, const double y = 0, const double z = 0, const double w = 1);
	/**
	 * Instantiate a 3D homogeneous point from a 3D affine point.
	 * @param p the affine point.
	 */
	explicit Point4(const Point3& p);
	/**
	 * Convert the homogeneous point into its affine representation.
	 */
	operator Point3() const;
    /**
     * Multiplies this point by a viewport transform.
     */
    Point4& operator*(const ViewportTransform&);
};
} // namespace clockwork

#endif // CLOCKWORK_POINT4_HH
