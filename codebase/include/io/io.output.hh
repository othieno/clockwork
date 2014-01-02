/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
 *
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
#pragma once

#include <iostream>
#include "error.hh"
#include "renderer.hh"
#include "projection.hh"
#include "image.filter.hh"
#include "texture.filter.hh"
#include "renderer.implementation.wireframe.hh"

namespace clockwork {

std::string toString(const clockwork::Error&);
std::string toString(const clockwork::graphics::Renderer::Type&);
std::string toString(const clockwork::graphics::Projection::Type&);
std::string toString(const clockwork::graphics::ImageFilter::Type&);
std::string toString(const clockwork::graphics::TextureFilter::Type&);
std::string toString(const clockwork::graphics::WireframeRenderer::LineAlgorithm&);

} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::Error&);
std::ostream& operator<<(std::ostream&, const clockwork::graphics::Renderer::Type&);
std::ostream& operator<<(std::ostream&, const clockwork::graphics::Projection::Type&);
std::ostream& operator<<(std::ostream&, const clockwork::graphics::ImageFilter::Type&);
std::ostream& operator<<(std::ostream&, const clockwork::graphics::TextureFilter::Type&);
std::ostream& operator<<(std::ostream&, const clockwork::graphics::WireframeRenderer::LineAlgorithm&);
