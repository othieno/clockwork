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
#ifndef CLOCKWORK_MATERIAL_HH
#define CLOCKWORK_MATERIAL_HH

#include "Color.hh"


namespace clockwork {
/**
 * @see Texture.hh.
 */
class Texture;
/**
 *
 */
struct Material {
	/**
	 * Instantiates a Material object.
	 */
	Material();
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
	Color Ka;
	/**
	 * The material's coefficient of reflection for diffuse light.
	 */
	Color Kd;
	/**
	 * The material's coefficient of reflection for specular light.
	 */
	Color Ks;
	/**
	 * The material's ambient map.
	 */
	const Texture* ambient;
	/**
	 * The material's diffuse map.
	 */
	const Texture* diffuse;
	/**
	 * The material's normal map.
	 */
	const Texture* normal;
	/**
	 * The material's specular map.
	 */
	const Texture* specular;
};
} // namespace clockwork

#endif // CLOCKWORK_MATERIAL_HH
