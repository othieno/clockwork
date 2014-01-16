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

#include "color.hh"
#include "texture.hh"


namespace clockwork {
namespace graphics {

struct Material
{
	/**
	 * The material's shininess.
	 */
	double shininess;
	/**
	 * The material's transparency.
	 */
	double transparency;
	/**
	 * The material's coefficient of reflection for ambient light.
	 */
	ColorRGBA Ka;
	/**
	 * The material's coefficient of reflection for diffuse light.
	 */
	ColorRGBA Kd;
	/**
	 * The material's coefficient of reflection for specular light.
	 */
	ColorRGBA Ks;
	/**
	 * The ambient map.
	 */
	const Texture* ambient;
	/**
	 * The diffuse map.
	 */
	const Texture* diffuse;
	/**
	 * The normal map.
	 */
	const Texture* normal;
	/**
	 * The specular map.
	 */
	const Texture* specular;
	/**
	 * Instantiate a material with given ambient, diffuse, normal and specular maps.
	 * @param ambient the material's ambient map.
	 * @param diffuse the material's diffuse map.
	 * @param normal the material's normal map.
	 * @param specular the material's specular map.
	 */
	Material
	(
		const Texture* ambient = nullptr,
		const Texture* diffuse = nullptr,
		const Texture* normal = nullptr,
		const Texture* specular = nullptr
	);
};

} // namespace graphics
} // namespace clockwork
