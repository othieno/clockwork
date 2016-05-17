/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
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
pixelBufferImage_(nullptr),
depthBuffer_(nullptr),
depthBufferClearValue_(std::numeric_limits<double>::max()),
depthBufferImageData_(nullptr),
depthBufferImage_(nullptr),
stencilBuffer_(nullptr),
stencilBufferClearValue_(0x00),
stencilBufferImage_(nullptr)
{
    resize();
}


Framebuffer::~Framebuffer()
{}


QSize
Framebuffer::getResolution() const
{
    switch (resolution_)
    {
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
            return QSize();
    }
}


void
Framebuffer::setResolution(const Resolution resolution)
{
    if (resolution_ != resolution)
    {
        resolution_ = resolution;
        resize();
    }
}


std::uint32_t*
Framebuffer::getPixelBuffer()
{
    return pixelBuffer_.get();
}


const QImage&
Framebuffer::getPixelBufferImage() const
{
    return *pixelBufferImage_;
}


double*
Framebuffer::getDepthBuffer()
{
   return depthBuffer_.get();
}


const QImage&
Framebuffer::getDepthBufferImage() const
{
    return *depthBufferImage_;
}


std::uint8_t*
Framebuffer::getStencilBuffer()
{
    return stencilBuffer_.get();
}


const QImage&
Framebuffer::getStencilBufferImage() const
{
    return *stencilBufferImage_;
}


void
Framebuffer::clear()
{
    const auto& resolution = getResolution();
    if (!resolution.isValid())
        return;

    auto* a = pixelBuffer_.get();
    auto* b = depthBuffer_.get();
    auto* c = depthBufferImageData_.get();
    auto* d = stencilBuffer_.get();

    for (std::size_t i = 0; i < std::size_t(resolution.width() * resolution.height()); ++i)
    {
        *a++ = pixelBufferClearValue_;
        *b++ = depthBufferClearValue_;
        *c++ = std::numeric_limits<std::uint32_t>::max();
        *d++ = stencilBufferClearValue_;
    }
}


void
Framebuffer::discard(const unsigned int, const unsigned int)
{}


void
Framebuffer::resize()
{
    // Make sure the resolution size is valid. A size is invalid when both its width and
    // height are negative values. This can happen when getResolution cannot determine a
    // size for a given resolution identifier.
    const auto& resolution = getResolution();
    if (!resolution.isValid())
        throw std::domain_error("The framebuffer resolution has not been initialized yet.");

    const auto width = resolution.width();
    const auto height = resolution.height();
    const std::size_t size = width * height;

    pixelBuffer_.reset(new std::uint32_t[size]);
    pixelBufferImage_.reset(new QImage(reinterpret_cast<uchar*>(pixelBuffer_.get()), width, height, QImage::Format_ARGB32));

    depthBuffer_.reset(new double[size]);
    depthBufferImageData_.reset(new std::uint32_t[size]);
    depthBufferImage_.reset(new QImage(reinterpret_cast<uchar*>(depthBufferImageData_.get()), width, height, QImage::Format_RGB32));

    stencilBuffer_.reset(new std::uint8_t[size]);
    stencilBufferImage_.reset(new QImage(reinterpret_cast<uchar*>(stencilBuffer_.get()), width, height, QImage::Format_Mono));

    clear();
}


QList<Framebuffer::Resolution> getAvailableResolutions()
{
    return
    {
        Framebuffer::Resolution::VGA,
        Framebuffer::Resolution::SVGA,
        Framebuffer::Resolution::XGA,
        Framebuffer::Resolution::SXGA,
        Framebuffer::Resolution::FHD,
        Framebuffer::Resolution::QSXGA,
        Framebuffer::Resolution::UHD8K
    };
}
