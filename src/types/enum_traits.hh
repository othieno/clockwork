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
#include <stdexcept>
#include <iterator>


namespace clockwork {
/**
 * Checks if enum_traits::enumerators is defined for the enumerator E.
 */
template<class E>
struct hasEnumeratorList {
	static_assert(std::is_enum<E>::value);
	static constexpr bool value = false;
};
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
	 * This function must be specialized for each enumeration or it will always
	 * return an empty initializer list.
	 */
	static constexpr std::initializer_list<E> enumerators() {
		return std::initializer_list<E>();
	}
	/**
	 * Returns a human-readable name for the specified enumerator.
	 * This function must be specialized for each enumeration.
	 * @param enumerator the enumerator to query.
	 */
	template<class String = const char*> static String name(const E enumerator);
	/**
	 * Returns the specified enumerator's integral value.
	 */
	static constexpr Ordinal ordinal(const E enumerator) {
		return static_cast<Ordinal>(enumerator);
	}
	/**
	 * Returns the enumerator with the specified integer value.
	 * @param ordinal an enumerator's integer value.
	 */
	template<typename T = E> static constexpr typename std::enable_if<hasEnumeratorList<T>::value, T>::type
	enumerator(const Ordinal ordinal) {
		static_assert(std::is_same<E, T>::value);
		for (const auto e : enumerators()) {
			if (enum_traits::ordinal(e) == ordinal) {
				return e;
			}
		}
		throw std::domain_error("Invalid integer value.");
	}
	/**
	 * Returns the enumerator with the specified integer value.
	 * Note that this implementation does not perform safety checks to make
	 * sure the integer value is actually assigned to an enumerator. In such cases,
	 * converting an integer to an enumerator is undefined behavior.
	 * @param ordinal an enumerator's integer value.
	 */
	template<typename T = E> static constexpr typename std::enable_if<!hasEnumeratorList<T>::value, E>::type
	enumerator(const Ordinal ordinal) {
		static_assert(std::is_same<E, T>::value);
		return static_cast<E>(ordinal);
	}
	/**
	 * Returns the number of enumerators listed in the enumeration.
	 */
	static constexpr std::size_t cardinality() {
		return enumerators().size();
	}
};
/**
 * Defines the enum_traits::enumerators member function for the enumeration E.
 * Furthermore, if the list of enumerators is not empty, it will set
 * hasEnumeratorList<E>::value to true, which enables safe conversions from
 * integers to enumerators (see enum_traits::enumerator for more info).
 */
#define DECLARE_ENUMERATOR_LIST(E, ...) \
template<> \
struct hasEnumeratorList<E> { \
	/* TODO: Replace the following with std::size(__VA_ARGS__) when you move to C++17. */ \
	static constexpr bool value = std::initializer_list<E>(__VA_ARGS__).size() > 0; \
}; \
\
template<> constexpr std::initializer_list<E> \
enum_traits<E>::enumerators() { \
	return __VA_ARGS__; \
};
} // namespace clockwork

#endif // CLOCKWORK_ENUM_TRAITS_HH
