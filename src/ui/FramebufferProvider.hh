/*
 * This file is part of Clockwork.
 * https://github.com/othieno/clockwork.
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
#ifndef CLOCKWORK_FRAMEBUFFER_PROVIDER_HH
#define CLOCKWORK_FRAMEBUFFER_PROVIDER_HH

#include <QQuickImageProvider>
#include <memory>


namespace clockwork {
/**
 *
 */
class Framebuffer;
/**
 *
 */
class FramebufferProvider final : public QQuickImageProvider {
public:
	/**
	 *
	 */
	explicit FramebufferProvider(Framebuffer& framebuffer);
	/**
	 *
	 */
	QImage requestImage(const QString& id, QSize* const size, const QSize&) override;
private:
	/**
	 * A function that is called when the framebuffer is resized.
	 * @param resolution the framebuffer's new resolution.
	 */
	void onFramebufferResized(const QSize& resolution);
	/**
	 *
	 */
	Framebuffer& framebuffer_;
	/**
	 * An image representation of the framebuffer's pixel buffer attachment.
	 */
	std::unique_ptr<QImage> pixelBufferImage_;
	/**
	 * An integer representation of the depth buffer's data.
	 */
//    std::unique_ptr<std::uint32_t[]> depthBufferImageData_;
	/**
	 * An image representation of the framebuffer's depth buffer attachment.
	 */
	std::unique_ptr<QImage> depthBufferImage_;
	/**
	 * An image representation of the framebuffer's stencil buffer attachment.
	 */
	std::unique_ptr<QImage> stencilBufferImage_;
};
} // namespace clockwork

#endif // CLOCKWORK_FRAMEBUFFER_PROVIDER_HH
