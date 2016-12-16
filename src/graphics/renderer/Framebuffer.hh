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
	 * Instantiates a Framebuffer object with the specified resolution.
	 * @param resolution the framebuffer's resolution.
	 */
	explicit Framebuffer(const Resolution resolution = Resolution::ZERO);
	/**
	 * Deleted copy constructor.
	 */
	Framebuffer(const Framebuffer&) = delete;
	/**
	 * Deleted move constructor.
	 */
	Framebuffer(Framebuffer&&) = delete;
	/**
	 * Destroys this Framebuffer instance.
	 */
	~Framebuffer();
	/**
	 * Deleted copy operator.
	 */
	Framebuffer& operator=(const Framebuffer&) = delete;
	/**
	 * Deleted move operator.
	 */
	Framebuffer& operator=(Framebuffer&&) = delete;
	/**
	 * Returns the framebuffer's resolution identifier.
	 */
	Resolution getResolution() const;
	/**
	 * Resizes the framebuffer to the specified resolution.
	 * @param resolution the framebuffer's new resolution.
	 */
	void setResolution(const Resolution resolution);
	/**
	 * Returns the framebuffer's actual width and height.
	 */
	inline QSize getResolutionSize() const {
		return Framebuffer::getResolutionSize(resolution_);
	}
	/**
	 * Returns the pixel buffer.
	 */
	std::uint32_t* getPixelBuffer();
	/**
	 * Returns the pixel buffer.
	 */
	const std::uint32_t* getPixelBuffer() const;
	/**
	 * Returns the pixel buffer's clear value.
	 */
	std::uint32_t getPixelBufferClearValue() const;
	/**
	 * Sets the pixel buffer's clear value.
	 * @param value the clear value to set.
	 */
	void setPixelBufferClearValue(const std::uint32_t value);
	/**
	 * Returns the depth buffer.
	 */
	double* getDepthBuffer();
	/**
	 * Returns the depth buffer.
	 */
	const double* getDepthBuffer() const;
	/**
	 * Returns the depth buffer's clear value.
	 */
	double getDepthBufferClearValue() const;
	/**
	 * Sets the depth buffer's clear value.
	 * @param value the clear value to set.
	 */
	void setDepthBufferClearValue(const double value);
	/**
	 * Returns the stencil buffer.
	 */
	std::uint8_t* getStencilBuffer();
	/**
	 * Returns the stencil buffer.
	 */
	const std::uint8_t* getStencilBuffer() const;
	/**
	 * Returns the stencil buffer's clear value.
	 */
	std::uint8_t getStencilBufferClearValue() const;
	/**
	 * Sets the stencil buffer's clear value.
	 * @param value the clear value to set.
	 */
	void setStencilBufferClearValue(const std::uint8_t value);
	/**
	 * Clears the framebuffer.
	 */
	void clear();
	/**
	 * Discards (clears) the framebuffer element at the specified <x, y> coordinate.
	 * @param x the buffer element's row position.
	 * @param y the buffer element's column position.
	 */
	void discard(const std::uint32_t x, const std::uint32_t y);
	/**
	 * Return the buffer offset for a given <x, y> coordinate. If the coordinate
	 * is out of the range <[0, width), [0, height)>, where width and height are the
	 * framebuffer's current width and height respectively, -1 is returned.
	 * @param x the buffer element's row position.
	 * @param y the buffer element's column position.
	 */
	int getOffset(const std::uint32_t x, const std::uint32_t y) const;
	/**
	 * Returns all available framebuffer resolutions.
	 */
	static QList<Resolution> getAvailableResolutions();
	/**
	 * Returns the specified resolution's actual size.
	 * @param resolution the resolution to query.
	 */
	static QSize getResolutionSize(const Resolution resolution);
private:
	/**
	 * Resizes the framebuffer's attachments to the current resolution.
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
} // namespace clockwork

#endif // CLOCKWORK_FRAMEBUFFER_HH
