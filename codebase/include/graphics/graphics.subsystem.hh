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

#include "subsystem.hh"
#include "framebuffer.hh"
#include "image.filter.hh"
#include "ui.busy.indicator.hh"
#include "scene.object.hh"


namespace clockwork {
namespace graphics {

class GraphicsSubsystem : public clockwork::system::Subsystem
{
Q_OBJECT
friend clockwork::system::Services;
public:
	/**
	 * Return the framebuffer.
	 */
	clockwork::graphics::Framebuffer& getFramebuffer();
	/**
	 * Set the image filter to apply to the framebuffer during post-processing.
	 * @param type the type of the image filter to set.
	 */
	void setImageFilter(const clockwork::graphics::ImageFilter::Type& type);
	/**
	 * Return the type of the current image filter.
	 */
	const clockwork::graphics::ImageFilter::Type& getImageFilterType() const;
	/**
	 * Raise the 'updateComplete' signal.
	 */
	void signalUpdateComplete();
private:
	/**
	 * All subsystems are singletons. As such the default constructor is hidden,
	 * and the copy operator and constructor are deleted from the implementation.
	 */
	GraphicsSubsystem();
	GraphicsSubsystem(const GraphicsSubsystem&) = delete;
	GraphicsSubsystem& operator=(const GraphicsSubsystem&) = delete;
	/**
	 * The framebuffer.
	 */
	clockwork::graphics::Framebuffer _framebuffer;
	/**
	 * The image filter that is applied to the framebuffer during post-processing.
	 */
	clockwork::graphics::ImageFilter::Type _imageFilterType;
private slots:
	/**
	 * Update the subsystem.
	 */
	void update();
};

} // namespace graphics
} // namespace clockwork
