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
#ifndef CLOCKWORK_UNIFORM_HH
#define CLOCKWORK_UNIFORM_HH

#include "WeakVariant.hh"
#include "Color.hh"
#include <QVector3D>
#include <QMatrix4x4>
#include <QHash>


namespace clockwork {
namespace {
/**
 * Checks whether T is a valid Uniform value type.
 */
template<class T>
struct UniformValidator :
std::integral_constant<bool,
	std::is_base_of<Color, T>::value ||
	std::is_base_of<QVector3D, T>::value ||
	std::is_base_of<QMatrix2x3, T>::value ||
	std::is_base_of<QMatrix4x4, T>::value ||
	std::is_arithmetic<T>::value> {};
} // namespace
/**
 *
 */
using Uniform = WeakVariant<UniformValidator>;
/**
 * A collection of uniform variables.
 */
using Uniforms = QHash<QString, Uniform>;
} // namespace clockwork

#endif // CLOCKWORK_UNIFORM_HH
