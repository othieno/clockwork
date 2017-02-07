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


Framebuffer::Framebuffer(const Resolution resolutionIdentifier) :
resolutionIdentifier_(resolutionIdentifier),
resolution_(getResolution(resolutionIdentifier_)),
pixelBuffer_(nullptr),
pixelBufferClearValue_(0xFF000000),
depthBuffer_(nullptr),
depthBufferClearValue_(std::numeric_limits<double>::max()),
stencilBuffer_(nullptr),
stencilBufferClearValue_(0x00) {
	if (resolution_.isValid() && !resolution_.isNull()) {
		resize();
	}
}


Framebuffer::~Framebuffer() {}


Framebuffer::Resolution
Framebuffer::getResolutionIdentifier() const {
	return resolutionIdentifier_;
}


const QSize&
Framebuffer::getResolution() const {
	return resolution_;
}


std::uint32_t
Framebuffer::getWidth() const {
	return resolution_.isValid() ? resolution_.width() : 0;
}


std::uint32_t
Framebuffer::getHeight() const {
	return resolution_.isValid() ? resolution_.height() : 0;
}


void
Framebuffer::setResolution(const Resolution resolutionIdentifier) {
	if (resolutionIdentifier_ != resolutionIdentifier) {
		resolutionIdentifier_ = resolutionIdentifier;
		resolution_ = getResolution(resolutionIdentifier);
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
	if (resolutionIdentifier_ == Resolution::ZERO) {
		return;
	}
	const std::size_t size = resolution_.width() * resolution_.height();
	Q_ASSERT(size > 0);

	std::fill_n(pixelBuffer_.get(), size, pixelBufferClearValue_);
	std::fill_n(depthBuffer_.get(), size, depthBufferClearValue_);
	std::fill_n(stencilBuffer_.get(), size, stencilBufferClearValue_);
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
	const std::uint32_t w = resolution_.width();
	const std::uint32_t h = resolution_.height();
	if (x < w && y < h) {
		offset = x + (y * w);
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
Framebuffer::getResolution(const Resolution resolutionIdentifier) {
	switch (resolutionIdentifier) {
		case Resolution::ZERO:
			return QSize(0, 0);
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
		default:
			qFatal("[Framebuffer::getResolution] Unspecified resolution identifier!");
	}
}


void
Framebuffer::resize() {
	// Destroy the reference to the previous pixel buffer before the buffer itself is destroyed.
	pixelBufferImage_ = QImage();

	const std::uint32_t w = resolution_.width();
	const std::uint32_t h = resolution_.height();

	const std::size_t bufferSize = w * h;
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
	emit resized(resolution_);
}
