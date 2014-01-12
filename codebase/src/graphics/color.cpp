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
#include "color.hh"
#include <algorithm>


clockwork::graphics::ColorRGB::ColorRGB(const double& r, const double& g, const double& b) :
red(r),
green(g),
blue(b)
{}


clockwork::graphics::ColorARGB::ColorARGB(const double& a, const double& r, const double& g, const double& b) :
alpha(a),
red(r),
green(g),
blue(b)
{}


uint32_t
clockwork::graphics::mergeColorChannels(const double& a, const double& r, const double& g, const double& b)
{
	uint32_t output = 0;

	// Convert the channels to integer values.
	const auto A = static_cast<uint32_t>(std::round(std::max(0.0, a) * 255.0));
	const auto R = static_cast<uint32_t>(std::round(std::max(0.0, r) * 255.0));
	const auto G = static_cast<uint32_t>(std::round(std::max(0.0, g) * 255.0));
	const auto B = static_cast<uint32_t>(std::round(std::max(0.0, b) * 255.0));

	if (A > 0)
		output = std::min(255U, A) << 24;
	if (R > 0)
		output |= std::min(255U, R) << 16;
	if (G > 0)
		output |= std::min(255U, G) <<  8;
	if (B > 0)
		output |= std::min(255U, B);

	return output;
}


clockwork::graphics::ColorRGB
clockwork::graphics::ColorRGB::getRandom()
{
	static std::random_device device;
	static std::mt19937 gen(device());
	static std::uniform_real_distribution<double> distribution(0, 1);

	return ColorRGB(distribution(gen), distribution(gen), distribution(gen));
}


clockwork::graphics::ColorARGB
clockwork::graphics::ColorARGB::getRandom()
{
	static std::random_device device;
	static std::mt19937 gen(device());
	static std::uniform_real_distribution<double> distribution(0, 1);

	return ColorARGB(1.0, distribution(gen), distribution(gen), distribution(gen));
}
