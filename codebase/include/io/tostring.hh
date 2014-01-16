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

#include <QString>
#include "error.hh"
#include "projection.hh"
#include "wireframe.render.parameters.hh"
#include "texture.filter.factory.hh"
#include "image.filter.hh"
#include "texture.filter.hh"
#include "fragment.hh"
#include "framebuffer.hh"


namespace clockwork {

QString toString(const clockwork::Error&);
QString toString(const clockwork::graphics::Fragment&);
QString toString(const clockwork::graphics::Framebuffer&);
QString toString(const clockwork::graphics::Framebuffer::Resolution&);
QString toString(const clockwork::graphics::Projection::Type&);
QString toString(const clockwork::graphics::ImageFilter::Type&);
QString toString(const clockwork::graphics::TextureFilter::Type&);
QString toString(const clockwork::graphics::RenderParameters::Type&);
QString toString(const clockwork::graphics::WireframeRenderParameters::LineAlgorithm&);

} // namespace clockwork
