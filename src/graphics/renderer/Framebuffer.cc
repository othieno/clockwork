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
#include "Framebuffer.hh"

using clockwork::Framebuffer;


Framebuffer::Framebuffer(const Resolution resolution) :
resolution_(resolution),
pixelBuffer_(nullptr),
pixelBufferClearValue_(0xFF000000),
depthBuffer_(nullptr),
depthBufferClearValue_(std::numeric_limits<double>::max()),
stencilBuffer_(nullptr),
stencilBufferClearValue_(0x00) {}


Framebuffer::~Framebuffer() {}


Framebuffer::Resolution
Framebuffer::getResolution() const {
	return resolution_;
}


void
Framebuffer::setResolution(const Resolution resolution) {
	if (resolution_ != resolution) {
		resolution_ = resolution;
		resize();
	}
}


std::uint32_t*
Framebuffer::getPixelBuffer() {
	return pixelBuffer_.get();
}


const std::uint32_t*
Framebuffer::getPixelBuffer() const {
	return pixelBuffer_.get();
}


const QImage&
Framebuffer::getPixelBufferImage() const {
	return pixelBufferImage_;
}


std::uint32_t
Framebuffer::getPixelBufferClearValue() const {
	return pixelBufferClearValue_;
}


void
Framebuffer::setPixelBufferClearValue(const std::uint32_t value) {
	pixelBufferClearValue_ = value;
}


double*
Framebuffer::getDepthBuffer() {
	return depthBuffer_.get();
}


const double*
Framebuffer::getDepthBuffer() const {
	return depthBuffer_.get();
}


double
Framebuffer::getDepthBufferClearValue() const {
	return depthBufferClearValue_;
}


void
Framebuffer::setDepthBufferClearValue(const double value) {
	depthBufferClearValue_ = value;
}


std::uint8_t*
Framebuffer::getStencilBuffer() {
	return stencilBuffer_.get();
}


const std::uint8_t*
Framebuffer::getStencilBuffer() const {
	return stencilBuffer_.get();
}


std::uint8_t
Framebuffer::getStencilBufferClearValue() const {
	return stencilBufferClearValue_;
}


void
Framebuffer::setStencilBufferClearValue(const std::uint8_t value) {
	stencilBufferClearValue_ = value;
}


void
Framebuffer::clear() {
	const auto& resolution = getResolutionSize();
	if (!resolution.isValid()) {
		return;
	}
	const std::size_t bufferSize = resolution.width() * resolution.height();
	if (bufferSize > 0) {
		auto* a = pixelBuffer_.get();
		auto* b = depthBuffer_.get();
		auto* c = stencilBuffer_.get();

		for (std::size_t i = 0; i < bufferSize; ++i) {
			*a++ = pixelBufferClearValue_;
			*b++ = depthBufferClearValue_;
			*c++ = stencilBufferClearValue_;
		}
	}
}


void
Framebuffer::discard(const std::uint32_t x, const std::uint32_t y) {
	const int offset = getOffset(x, y);
	if (offset >= 0) {
		pixelBuffer_[offset] = pixelBufferClearValue_;
		depthBuffer_[offset] = depthBufferClearValue_;
		stencilBuffer_[offset] = stencilBufferClearValue_;
	}
}


int
Framebuffer::getOffset(const std::uint32_t x, const std::uint32_t y) const {
	int offset = -1;
	const auto& resolution = getResolutionSize();
	if (resolution.isValid()) {
		const std::uint32_t w = resolution.width();
		const std::uint32_t h = resolution.height();
		if (x < w && y < h) {
			offset = x + (y * w);
		}
	}
	return offset;
}


QList<Framebuffer::Resolution>
Framebuffer::getAvailableResolutions() {
	return {
		Framebuffer::Resolution::ZERO,
		Framebuffer::Resolution::VGA,
		Framebuffer::Resolution::SVGA,
		Framebuffer::Resolution::XGA,
		Framebuffer::Resolution::SXGA,
		Framebuffer::Resolution::FHD,
		Framebuffer::Resolution::QSXGA,
		Framebuffer::Resolution::UHD8K
	};
}


QSize
Framebuffer::getResolutionSize(const Resolution resolution) {
	switch (resolution) {
		case Resolution::VGA:
			return QSize(640, 480);
		case Resolution::SVGA:
			return QSize(800, 600);
		case Resolution::XGA:
			return QSize(1024, 768);
		case Resolution::SXGA:
			return QSize(1280, 1024);
		case Resolution::FHD:
			return QSize(1920, 1080);
		case Resolution::QSXGA:
			return QSize(2560, 2048);
		case Resolution::UHD8K:
			return QSize(7680, 4320);
		case Resolution::ZERO:
		default:
			return QSize(0, 0);
	}
}


void
Framebuffer::resize() {
	const QSize& resolution = getResolutionSize();
	const auto w = resolution.width();
	const auto h = resolution.height();
	const auto bufferSize = w * h;

	// Destroy the reference to the previous pixel buffer before the buffer itself is destroyed.
	pixelBufferImage_ = QImage();

	if (bufferSize == 0) {
		pixelBuffer_.reset(nullptr);
		depthBuffer_.reset(nullptr);
		stencilBuffer_.reset(nullptr);
	} else {
		pixelBuffer_.reset(new std::uint32_t[bufferSize]);
		depthBuffer_.reset(new double[bufferSize]);
		stencilBuffer_.reset(new std::uint8_t[bufferSize]);
		pixelBufferImage_ = QImage(reinterpret_cast<uchar*>(pixelBuffer_.get()), w, h, QImage::Format_ARGB32);
	}

	clear();
	emit resized(resolution);
}
