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

#include "task.hh"
#include "framebuffer.hh"
#include "scene.object.hh"
#include "image.filter.factory.hh"


namespace clockwork {
namespace concurrency {

class GraphicsUpdateTask : public Task
{
public:
	/**
	 * The default constructor.
	 */
	GraphicsUpdateTask();
	/**
	 * @see clockwork::concurrency::Task::onRun.
	 */
	virtual void onRun() override final;
};

/**
 * A task to update the scene geometry. More specifically, it updates the
 * model transformation matrix for each scene object.
 */
class GeometryUpdateTask : public Task
{
public:
	/**
	 * Instantiate an update task that will update a given node's model
	 * transformation matrix.
	 * @param object the scene object to update.
	 * @param CMTM the current model transformation matrix.
	 */
	GeometryUpdateTask(clockwork::scene::Object& object, const clockwork::Matrix4& CMTM);
	/**
	 * @see clockwork::concurrency::Task::onRun.
	 */
	virtual void onRun() override final;
private:
	/**
	 * The node that will be updated by this task.
	 */
	clockwork::scene::Object& _object;
	/**
	 * The current model transformation matrix that will be concatenated to the node's
	 * model transformation matrix.
	 */
	const clockwork::Matrix4& _CMTM;
};


/**
 * A task to apply an image filter to the framebuffer.
 */
class PostProcessingTask : public Task
{
public:
	/**
	 * Instantiate a post-processing task that applies a given image filter to
	 * the framebuffer.
	 * @param framebuffer the framebuffer to process.
	 * @param type the type of image filter to apply to the framebuffer.
	 */
	PostProcessingTask
	(
		clockwork::graphics::Framebuffer& framebuffer,
		const clockwork::graphics::ImageFilter::Type& type
	);
	/**
	 * @see clockwork::concurrency::Task::onRun.
	 */
	virtual void onRun() override final;
private:
	/**
	 * The framebuffer to modify.
	 */
	clockwork::graphics::Framebuffer& _framebuffer;
	/**
	 * The image filter to apply to the framebuffer.
	 */
	clockwork::graphics::ImageFilter* const _imageFilter;
};

} // namespace concurrency
} // namespace clockwork
