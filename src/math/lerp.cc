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
#include "lerp.hh"


qreal
clockwork::lerp(const qreal from, const qreal to, const qreal p) {
	return ((1.0 - p) * from) + (p * to);
}


QPointF
clockwork::lerp(const QPointF& from, const QPointF& to, const qreal p) {
	const qreal pp = 1.0 - p;
	return QPointF(
		(pp * from.x()) + (p * to.x()),
		(pp * from.y()) + (p * to.y())
	);
}


QVector3D
clockwork::lerp(const QVector3D& from, const QVector3D& to, const qreal p) {
	const qreal pp = 1.0 - p;
	return QVector3D(
		(pp * from.x()) + (p * to.x()),
		(pp * from.y()) + (p * to.y()),
		(pp * from.z()) + (p * to.z())
	);
}


QVector4D
clockwork::lerp(const QVector4D& from, const QVector4D& to, const qreal p) {
	const qreal pp = 1.0 - p;
	return QVector4D(
		(pp * from.x()) + (p * to.x()),
		(pp * from.y()) + (p * to.y()),
		(pp * from.z()) + (p * to.z()),
		(pp * from.w()) + (p * to.w())
	);
}


clockwork::Color
clockwork::lerp(const Color& from, const Color& to, const qreal p) {
	const qreal pp = 1.0 - p;
	return Color(
		(pp * from.red)   + (p * to.red),
		(pp * from.green) + (p * to.green),
		(pp * from.blue)  + (p * to.blue),
		(pp * from.alpha) + (p * to.alpha)
	);
}
