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
#ifndef CLOCKWORK_ERROR_HH
#define CLOCKWORK_ERROR_HH

#include "enumeration.hh"


namespace clockwork {
/**
 * An enumeration of available system errors.
 */
enum class Error {
	None,
	FileNotAccessible,
	InvalidQmlContext,
	Unknown,
};
/**
 * Returns a list of all available system errors.
 */
template<> constexpr std::initializer_list<Error>
enumeration<Error>::enumerators() {
	return {
		Error::None,
		Error::FileNotAccessible,
		Error::InvalidQmlContext,
		Error::Unknown,
	};
}
/**
 * Returns the human-readable name of the specified system error.
 * @param error the system error to query.
 */
template<> template<class String> String
enumeration<Error>::name(const Error error) {
	switch (error) {
		case Error::None:
			return "None";
		case Error::FileNotAccessible:
			return "File not accessible";
		case Error::InvalidQmlContext:
			return "Invalid QML context";
		case Error::Unknown:
			return "Unknown system error";
		default:
			return "???";
	}
}
} // namespace clockwork

#endif // CLOCKWORK_ERROR_HH
