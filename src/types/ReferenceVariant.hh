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
#ifndef CLOCKWORK_REFERENCE_VARIANT_HH
#define CLOCKWORK_REFERENCE_VARIANT_HH

#include <type_traits>


namespace clockwork {
/**
 * Checks whether Type is a valid reference value type.
 */
template<class Type>
struct ReferenceVariantValidator : std::integral_constant<bool, true> {};
/**
 * A ReferenceVariant is a data type that contains a non-owning reference to
 * any kind of object.
 */
template<template<class> class Validator = ReferenceVariantValidator>
class ReferenceVariant {
public:
	/**
	 * Returns the referenced value.
	 */
	template<class Type> Type& get();
	/**
	 * Returns the referenced value.
	 */
	template<class Type> const Type& get() const;
	/**
	 * Instantiates a ReferenceVariant object with the specified referenced value.
	 * @param value the referenced value.
	 */
	template<class Type> static ReferenceVariant<Validator> create(Type& value);
private:
	/**
	 * Instantiates a ReferenceVariant object with the specified value.
	 * @param the referenced value.
	 */
	inline explicit ReferenceVariant(void* const value);
	/**
	 * The referenced value.
	 */
	void* const value_;
};


template<template<class> class V>
ReferenceVariant<V>::ReferenceVariant(void* const value) :
value_(value) {}


template<template<class> class V> template<class T> T&
ReferenceVariant<V>::get() {
	static_assert(V<T>::value);
	return *static_cast<T*>(value_);
}


template<template<class> class V> template<class T> const T&
ReferenceVariant<V>::get() const {
	static_assert(V<T>::value);
	return *static_cast<const T*>(value_);
}


template<template<class> class V> template<class T> ReferenceVariant<V>
ReferenceVariant<V>::create(T& value) {
	static_assert(V<T>::value);
	return ReferenceVariant<V>(&value);
}
} // namespace clockwork

#endif // CLOCKWORK_REFERENCE_VARIANT_HH
