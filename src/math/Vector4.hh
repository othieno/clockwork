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
#ifndef CLOCKWORK_VECTOR4_HH
#define CLOCKWORK_VECTOR4_HH

#include <type_traits>


namespace clockwork {
namespace math {
/**
 * @see below.
 */
template<class Type> struct Vector4;
/**
 * Vector4 shorthands.
 */
using Vector4i = Vector4<int>;
using Vector4u = Vector4<unsigned>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;
/**
 * A 4D vector.
 */
template<class Type>
struct Vector4 {
	static_assert(std::is_arithmetic<Type>::value, "Type argument must be an int, float or double.");
	/**
	 * Instantiates a Vector4 object with the specified components.
	 * @param i the vector's i component.
	 * @param j the vector's j component.
	 * @param k the vector's k component.
	 * @param l the vector's l component.
	 */
	Vector4(const Type i = 0, const Type j = 0, const Type k = 0, const Type l = 0);
	/**
	 * The vector's i component.
	 */
	Type i;
	/**
	 * The vector's j component.
	 */
	Type j;
	/**
	 * The vector's k component.
	 */
	Type k;
	/**
	 * The vector's l component.
	 */
	Type l;
};


template<class T>
Vector4<T>::Vector4(const T I, const T J, const T K, const T L) :
i(I),
j(J),
k(K),
l(L) {}
} // namespace math
} // namespace clockwork

#endif // CLOCKWORK_VECTOR4_HH
