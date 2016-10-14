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
#ifndef CLOCKWORK_LERP_HH
#define CLOCKWORK_LERP_HH

#include "Point.hh"
#include "Point3.hh"
#include "Point4.hh"
#include "Vector3.hh"
#include "Vector4.hh"
#include "Color.hh"


namespace clockwork {
/**
 * Performs a linear interpolation to find a value at a specified
 * percentage between two other values.
 */
double lerp(const double from, const double to, const double percentage);
/**
 * Performs a linear interpolation to find the Point at a specified
 * percentage between two Point instances.
 */
Point lerp(const Point& from, const Point& to, const double percentage);
/**
 * Performs a linear interpolation to find the Point3 at a specified
 * percentage between two Point3 instances.
 */
Point3 lerp(const Point3& from, const Point3& to, const double percentage);
/**
 * Performs a linear interpolation to find the Point4 at a specified
 * percentage between two Point4 instances.
 */
Point4 lerp(const Point4& from, const Point4& to, const double percentage);
/**
 * Performs a linear interpolation to find the Vector3 at a specified
 * percentage between two Vector3 instances.
 */
Vector3 lerp(const Vector3& from, const Vector3& to, const double percentage);
/**
 * Performs a linear interpolation to find the Vector4d at a specified
 * percentage between two Vector4d instances.
 */
math::Vector4d lerp(const math::Vector4d& from, const math::Vector4d& to, const double percentage);
/**
 * Performs a linear interpolation to find the Color at a specified
 * percentage between two Color instances.
 */
Color lerp(const Color& from, const Color& to, const double percentage);
} // namespace clockwork

#endif // CLOCKWORK_LERP_HH
