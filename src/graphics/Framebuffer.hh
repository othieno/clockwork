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


namespace clockwork {

class Framebuffer final : public QObject
{
public:
   /**
    * Available framebuffer resolutions.
    */
    enum class Resolution
    {
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
    explicit Framebuffer(const Framebuffer::Resolution resolution);
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
     * Returns the framebuffer's width and height.
     */
    QSize getResolution() const;
    /**
     * Sets the framebuffer's resolution.
     */
    void setResolution(const Framebuffer::Resolution resolution);
    /**
     * Returns the pixel buffer.
     */
    std::uint32_t* getPixelBuffer();
    /**
     * Returns an image representation of the pixel buffer.
     */
    const QImage& getPixelBufferImage() const;
    /**
     * Returns the depth buffer.
     */
    std::int32_t* getDepthStencilBuffer();
    /**
     * Returns an image representation of the depth buffer.
     */
    const QImage& getDepthStencilBufferImage() const;
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
     * The framebuffer's resolution.
     */
    Framebuffer::Resolution resolution_;
    /**
     * The framebuffer's pixel buffer attachment.
     */
    std::uint32_t* pixelBuffer_;
    /**
     * The framebuffer's pixel buffer image.
     */
    QImage* pixelBufferImage_;
    /**
     * The framebuffer's depth-stencil buffer attachment.
     */
    std::int32_t* depthStencilBuffer_;
    /**
     * The framebuffer's depth-stencil buffer image.
     */
    QImage* depthStencilBufferImage_;
    /**
     * Resizes the framebuffer's attachments.
     */
    void resize();
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
