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
#ifndef CLOCKWORK_VERTEX_ATTRIBUTES_HH
#define CLOCKWORK_VERTEX_ATTRIBUTES_HH

#include "RenderingAlgorithm.hh"
#include "Point.hh"
#include "Point4.hh"
#include "Vector4.hh"


namespace clockwork {
namespace detail {
/**
 *
 */
template<RenderingAlgorithm algorithm> struct VertexAttributes {};
/**
 * Vertex attributes for the point renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Point> {
	/**
	 * The vertex's position.
	 */
	Point4 position;
};
/**
 * Vertex attributes for the Wireframe renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Wireframe> : VertexAttributes<RenderingAlgorithm::Point> {};
/**
 * Vertex attributes for the random shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Random> {};
/**
 * Vertex attributes for the depth mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Depth> {};
/**
 * Vertex attributes for the normal mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Normals> {
	/**
	 * The vertex's normal vector.
	 */
	math::Vector4d normal;
};
/**
 * Vertex attributes for the texture mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Texture> : VertexAttributes<RenderingAlgorithm::Normals> {
	/**
	 * The vertex's texture mapping coordinates.
	 */
	Point textureCoordinates;
};
/**
 * Vertex attributes for the constant (flat) shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Constant> {};
/**
 * Vertex attributes for the Phong shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Phong> {};
/**
 * Vertex attributes for the cel shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Cel> {};
/**
 * Vertex attributes for the bump mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Bump> {};
/**
 * Vertex attributes for the deferred renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::Deferred> {};
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_VERTEX_ATTRIBUTES_HH
