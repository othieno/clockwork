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
#include "FramebufferProvider.hh"
#include "Framebuffer.hh"
#include <QObject>

using clockwork::FramebufferProvider;


FramebufferProvider::FramebufferProvider(Framebuffer& framebuffer) :
QQuickImageProvider(QQmlImageProviderBase::Image, QQmlImageProviderBase::ForceAsynchronousImageLoading),
framebuffer_(framebuffer),
pixelBufferImage_(nullptr),
//depthBufferImageData_(nullptr),
depthBufferImage_(nullptr),
stencilBufferImage_(nullptr) {
	using std::placeholders::_1;

	onFramebufferResized(framebuffer.getResolutionSize());
	QObject::connect(&framebuffer, &Framebuffer::resized, std::bind(&FramebufferProvider::onFramebufferResized, this, _1));
}


QImage
FramebufferProvider::requestImage(const QString& id, QSize* const size, const QSize&)
{
	if (size != nullptr)
		*size = framebuffer_.getResolutionSize();

	if (id == "pixel" && pixelBufferImage_ != nullptr) {
		return *pixelBufferImage_;
	} else if (id == "depth" && depthBufferImage_ != nullptr) {
		return *depthBufferImage_;
	} else if (id == "stencil" && stencilBufferImage_ != nullptr) {
		return *stencilBufferImage_;
	} else {
		return QImage();
	}
}


void
FramebufferProvider::onFramebufferResized(const QSize& resolution) {
	const std::size_t w = resolution.width();
	const std::size_t h = resolution.height();

	uchar* const pb = reinterpret_cast<uchar*>(framebuffer_.getPixelBuffer());
	pixelBufferImage_.reset(new QImage(pb, w, h, QImage::Format_ARGB32));
/*
	depthBufferImageData_.reset(new std::uint32_t[size]);
	depthBufferImage_.reset(new QImage(reinterpret_cast<uchar*>(depthBufferImageData_.get()), width, height, QImage::Format_RGB32));
*/
	uchar* const sb = reinterpret_cast<uchar*>(framebuffer_.getStencilBuffer());
	stencilBufferImage_.reset(new QImage(sb, w, h, QImage::Format_Mono));
}
