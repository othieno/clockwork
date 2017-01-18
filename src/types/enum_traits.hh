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
#ifndef CLOCKWORK_ENUM_TRAITS_HH
#define CLOCKWORK_ENUM_TRAITS_HH

#include <initializer_list>
#include <type_traits>
#include <string>


namespace clockwork {
/**
 * Provides information about the enumeration E.
 */
template<class E>
struct enum_traits {
	static_assert(std::is_enum<E>::value);
	/**
	 * The integral type that serves as the enumeration's fixed underlying type.
	 */
	using Ordinal = typename std::underlying_type<E>::type;
	/**
	 * Returns the list of enumerators listed in the enumeration.
	 * This function must be specialized for each enumeration.
	 */
	static constexpr std::initializer_list<E> enumerators();
	/**
	 * Returns a human-readable name for the specified enumerator.
	 * This function must be specialized for each enumeration.
	 * @param enumerator the enumerator to query.
	 */
	template<class String = std::string> static String name(const E enumerator);
	/**
	 * Returns the specified enumerator's integral value.
	 */
	static constexpr Ordinal ordinal(const E enumerator) {
		return static_cast<Ordinal>(enumerator);
	}
	/**
	 * Returns the enumerator with the specified value.
	 * @param ordinal an enumerator's integral value.
	 */
	static constexpr E enumerator(const Ordinal ordinal) {
		//TODO Make sure the ordinal is actually valid.
		return static_cast<E>(ordinal);
	}
	/**
	 * Returns the number of enumerators listed in the enumeration.
	 */
	static constexpr std::size_t cardinality() {
		return enumerators().size();
	}
};
} // namespace clockwork

#endif // CLOCKWORK_ENUM_TRAITS_HH
