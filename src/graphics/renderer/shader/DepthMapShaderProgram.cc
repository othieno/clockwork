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
#include "DepthMapShaderProgram.hh"

using clockwork::ShaderProgramIdentifier;
using ShaderProgram = clockwork::detail::ShaderProgram<ShaderProgramIdentifier::DepthMaps>;


template<> std::uint32_t
ShaderProgram::fragmentShader(const Uniforms&, const Varying&, const Fragment& fragment) {
	// The fragment's depth value is multiplied by a depth scale and then added to
	// a depth bias. The Color.merge function guarantees that this result is clamped to
	// the [0, 1] range.
	const double depthScale = 1.0;
	const double depthBias = 0.15;
	const double depth = (fragment.z * depthScale) + depthBias;

	return Color(depth, depth, depth);
}
