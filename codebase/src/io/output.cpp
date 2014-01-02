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
#include "io.output.hh"


std::ostream&
operator<<(std::ostream& os, const clockwork::Error& error)
{
	os << "Error: " << clockwork::toString(error);
	return os;
}


std::ostream&
operator<<(std::ostream& os, const clockwork::graphics::Renderer::Type& type)
{
	os << clockwork::toString(type);
	return os;
}


std::ostream&
operator<<(std::ostream& os, const clockwork::graphics::Projection::Type& type)
{
	os << clockwork::toString(type);
	return os;
}


std::ostream&
operator<<(std::ostream& os, const clockwork::graphics::ImageFilter::Type& type)
{
	os << clockwork::toString(type);
	return os;
}


std::ostream&
operator<<(std::ostream& os, const clockwork::graphics::TextureFilter::Type& type)
{
	os << clockwork::toString(type);
	return os;
}


std::ostream&
operator<<(std::ostream& os, const clockwork::graphics::WireframeRenderer::LineAlgorithm& algorithm)
{
	os << clockwork::toString(algorithm);
	return os;
}


std::string
clockwork::toString(const clockwork::Error& error)
{
	switch (error)
	{
		case clockwork::Error::None:
			return "None.";
		case clockwork::Error::Unknown:
		default:
			return "???";
	}
}


std::string
clockwork::toString(const clockwork::graphics::Renderer::Type& type)
{
	switch (type)
	{
		case clockwork::graphics::Renderer::Type::Point:
			return "Points";
		case clockwork::graphics::Renderer::Type::Wireframe:
			return "Wireframe";
		case clockwork::graphics::Renderer::Type::Random:
			return "Random shading";
		case clockwork::graphics::Renderer::Type::Depth:
			return "Depth shading";
		case clockwork::graphics::Renderer::Type::Normals:
			return "Normals shading";
		case clockwork::graphics::Renderer::Type::Texture:
			return "Texture mapping";
		case clockwork::graphics::Renderer::Type::Constant:
			return "Constant shading";
		case clockwork::graphics::Renderer::Type::Phong:
			return "Phong shading";
		case clockwork::graphics::Renderer::Type::Cel:
			return "Cel shading";
		case clockwork::graphics::Renderer::Type::Bump:
			return "Bump mapping";
		case clockwork::graphics::Renderer::Type::Deferred:
			return "Deferred shading";
		default:
			return "Unknown renderer";
	}
}


std::string
clockwork::toString(const clockwork::graphics::Projection::Type& type)
{
	switch (type)
	{
		case clockwork::graphics::Projection::Type::Orthographic:
			return "Orthographic";
		case clockwork::graphics::Projection::Type::Cabinet:
			return "Cabinet";
		case clockwork::graphics::Projection::Type::Cavalier:
			return "Cavalier";
		case clockwork::graphics::Projection::Type::Perspective:
			return "Perspective";
		default:
			return "Unknown projection";
	}
}


std::string
clockwork::toString(const clockwork::graphics::ImageFilter::Type& type)
{
	switch (type)
	{
		case clockwork::graphics::ImageFilter::Type::None:
			return "None";
		case clockwork::graphics::ImageFilter::Type::BlackAndWhite:
			return "Black & White";
		case clockwork::graphics::ImageFilter::Type::Grayscale:
			return "Grayscale";
		default:
			return "Unknown image filter";
	}
}


std::string
clockwork::toString(const clockwork::graphics::TextureFilter::Type& type)
{
	switch (type)
	{
		case clockwork::graphics::TextureFilter::Type::None:
			return "None";
		case clockwork::graphics::TextureFilter::Type::Bilinear:
			return "Bilinear";
		case clockwork::graphics::TextureFilter::Type::Trilinear:
			return "Trilinear";
		case clockwork::graphics::TextureFilter::Type::Anisotropic:
			return "Anisotropic";
		default:
			return "Unknown texture filter";
	}
}


std::string
clockwork::toString(const clockwork::graphics::WireframeRenderer::LineAlgorithm& algorithm)
{
	switch (algorithm)
	{
		case clockwork::graphics::WireframeRenderer::LineAlgorithm::Bresenham:
			return "Bresenham";
		case clockwork::graphics::WireframeRenderer::LineAlgorithm::XiaolinWu:
			return "Xiaolin Wu";
		default:
			return "Unknown line algorithm";
	}
}
