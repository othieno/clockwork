/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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

#include "task.hh"
#include "framebuffer.hh"
#include "image.filter.hh"


namespace clockwork {
namespace graphics {

/**
 * A task to apply one or more post-processing filters to a given
 * framebuffer, after rendering is complete.
 */
class PostProcessTask : public clockwork::concurrency::Task
{
public:
   /**
    * Instantiate a PostProcessTask that will apply a filter to a framebuffer.
    * @param framebuffer the framebuffer that the filter is applied to.
    * @param type the type of post-processing filter to apply to the framebuffer.
    */
   PostProcessTask(Framebuffer& framebuffer, const ImageFilter::Type& type);
   /**
    * @see clockwork::concurrency::Task::onRun.
    */
   virtual void onRun() override final;
private:
   /**
    * The framebuffer where the rendered scene's information will be stored.
    */
   Framebuffer& _framebuffer;
   /**
    * The queue of post-processing filters to apply when drawing is completed.
    */
   const ImageFilter* const _imageFilter;
};

} // namespace graphics
} // namespace clockwork
