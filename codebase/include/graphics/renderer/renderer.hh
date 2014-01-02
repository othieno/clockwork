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


namespace clockwork {
namespace graphics {


class Renderer
{
public:
	/**
	 * Types of renderers.
	 */
	enum class Type
	{
		Point,
		Wireframe,
		Random,
		Depth,
		Normals,
		Texture,
		Constant,
		Phong,
		Cel,
		Bump,
		Deferred
	};
	/**
	 * Return the renderer's type.
	 */
	const Renderer::Type& getType() const;
protected:
	/**
	 * Instantiate a renderer with a given type.
	 */
	Renderer(const Renderer::Type& type);
private:
	/**
	 * This renderer's type.
	 */
	const Renderer::Type _type;
	/**
	 * Apply this render function to a render task.
	 * @param task the task containing the render function's input.
	 */
	void process() const;
};

} // namespace graphics
} // namespace clockwork
