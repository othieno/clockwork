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
#include "toString.hh"


QString
clockwork::toString(const Framebuffer::Resolution resolution) {
	switch (resolution) {
		case Framebuffer::Resolution::ZERO:
			return "ZERO (0 x 0)";
		case Framebuffer::Resolution::VGA:
			return "VGA (640 x 480)";
		case Framebuffer::Resolution::SVGA:
			return "SVGA (800 x 600)";
		case Framebuffer::Resolution::XGA:
			return "XGA (1024 x 768)";
		case Framebuffer::Resolution::SXGA:
			return "SXGA (1280 x 1024)";
		case Framebuffer::Resolution::FHD:
			return "FHD (1920 x 1080)";
		case Framebuffer::Resolution::QSXGA:
			return "QSXGA (2560 x 2048)";
		case Framebuffer::Resolution::UHD8K:
			return "UHD8K (7680 x 4320)";
		default:
			return "???";
	}
}


QString
clockwork::toString(const Language language) {
	switch (language) {
		case Language::English:
			return "English";
		default:
			return "???";
	}
}


QString
clockwork::toString(const SceneObjectProperty::Type type) {
	switch (type) {
		case SceneObjectProperty::Type::Appearance:
			return "Appearance";
		default:
			return "???";
	}
}
