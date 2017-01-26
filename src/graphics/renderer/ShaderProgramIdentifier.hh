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
#ifndef CLOCKWORK_SHADER_PROGRAM_IDENTIFIER_HH
#define CLOCKWORK_SHADER_PROGRAM_IDENTIFIER_HH

#include "enum_traits.hh"


namespace clockwork {
/**
 * An enumeration of available shader programs.
 */
enum class ShaderProgramIdentifier {
	Minimal,
	RandomColoredSurfaces,
	NormalMaps,
};
/**
 * Declares a list of all available shader program identifiers.
 */
DECLARE_ENUMERATOR_LIST(ShaderProgramIdentifier, {
	ShaderProgramIdentifier::Minimal,
	ShaderProgramIdentifier::RandomColoredSurfaces,
	ShaderProgramIdentifier::NormalMaps,
})
/**
 * Returns the human-readable name of the specified shader program identifier.
 * @param identifier the shader program identifier to query.
 */
template<> template<class String> String
enum_traits<ShaderProgramIdentifier>::name(const ShaderProgramIdentifier identifier) {
	switch (identifier) {
		case ShaderProgramIdentifier::Minimal:
			return "Minimal";
		case ShaderProgramIdentifier::RandomColoredSurfaces:
			return "Random colored surfaces";
		case ShaderProgramIdentifier::NormalMaps:
			return "Normal maps";
		default:
			return "???";
	}
}
} // namespace clockwork

#endif // CLOCKWORK_SHADER_PROGRAM_IDENTIFIER_HH
