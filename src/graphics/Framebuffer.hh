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
#ifndef CLOCKWORK_FRAMEBUFFER_HH
#define CLOCKWORK_FRAMEBUFFER_HH

#include <QObject>
#include <QSize>
#include <memory>


namespace clockwork {
/**
 *
 */
class Framebuffer final : public QObject {
	Q_OBJECT
public:
	/**
	 * Available framebuffer resolutions.
	 */
	enum class Resolution {
		ZERO,    //    0 x 0
		VGA,     //  640 x 480
		SVGA,    //  800 x 600
		XGA,     // 1024 x 768
		SXGA,    // 1280 x 1024
		FHD,     // 1920 x 1080
		QSXGA,   // 2560 x 2048
		UHD8K    // 7680 x 4320
	};
	/**
	 *
	 */
	Framebuffer();
	/**
	 *
	 */
	Framebuffer(const Framebuffer&) = delete;
	/**
	 *
	 */
	Framebuffer(Framebuffer&&) = delete;
	/**
	 *
	 */
	~Framebuffer();
	/**
	 *
	 */
	Framebuffer& operator=(const Framebuffer&) = delete;
	/**
	 *
	 */
	Framebuffer& operator=(Framebuffer&&) = delete;
	/**
	 * Returns the framebuffer's resolution identifier.
	 */
	Resolution getResolution() const;
	/**
	 * Sets the framebuffer's resolution.
	 */
	void setResolution(const Framebuffer::Resolution resolution);
	/**
	 * Returns the framebuffer's width and height.
	 */
	QSize getResolutionSize() const;
	/**
	 * Returns the pixel buffer.
	 */
	std::uint32_t* getPixelBuffer();
	/**
	 * Returns the depth buffer.
	 */
	double* getDepthBuffer();
	/**
	 * Returns the stencil buffer.
	 */
	std::uint8_t* getStencilBuffer();
	/**
	 * Clears the framebuffer.
	 */
	void clear();
	/**
	 * Discards the fragment at the specified <x, y> coordinate.
	 */
	void discard(const unsigned int x, const unsigned int y);
private:
	/**
	 * Resizes the framebuffer's attachments.
	 */
	void resize();
	/**
	 * The framebuffer's resolution.
	 */
	Framebuffer::Resolution resolution_;
	/**
	 * The framebuffer's pixel buffer attachment.
	 */
	std::unique_ptr<std::uint32_t[]> pixelBuffer_;
	/**
	 * The pixel buffer's clear value.
	 */
	std::uint32_t pixelBufferClearValue_;
	/**
	 * The framebuffer's depth buffer attachment.
	 */
	std::unique_ptr<double[]> depthBuffer_;
	/**
	 * The pixel buffer's clear value.
	 */
	double depthBufferClearValue_;
	/**
	 * The framebuffer's stencil buffer attachment.
	 */
	std::unique_ptr<std::uint8_t[]> stencilBuffer_;
	/**
	 * The stencil buffer's clear value.
	 */
	std::uint8_t stencilBufferClearValue_;
signals:
	/**
	 * A signal that is raised when the framebuffer is resized.
	 * @param resolution the framebuffer's new resolution.
	 */
	void resized(const QSize& resolution);
};
/**
 * Returns all available framebuffer resolutions.
 */
QList<Framebuffer::Resolution> getFramebufferResolutions();
/**
 * Returns the human-readable name of the specified framebuffer resolution.
 */
QString toString(const Framebuffer::Resolution);
} // namespace clockwork

#endif // CLOCKWORK_FRAMEBUFFER_HH
