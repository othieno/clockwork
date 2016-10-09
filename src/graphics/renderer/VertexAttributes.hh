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
namespace {
/**
 *
 */
struct GenericVertexAttributes {
	/**
	 * The vertex's position in object space.
	 */
	const Point3& position;
protected:
	/**
	 * Instantiates a GenericVertexAttributes object with the specified vertex position.
	 * @param p the vertex's position.
	 */
	inline explicit GenericVertexAttributes(const Point3& p) : position(p) {}
};
} // namespace
/**
 *
 */
template<RenderingAlgorithm algorithm>
struct VertexAttributes : GenericVertexAttributes {
	/**
	 * Instantiates a VertexAttributes object with the specified vertex position.
	 * @param position the vertex's position.
	 */
	inline explicit VertexAttributes(const Point3& position = Point3()) :
	GenericVertexAttributes(position) {}
};
/**
 * Vertex attributes for the random shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::RandomShading> {};
/**
 * Vertex attributes for the flat shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::FlatShading> {};
/**
 * Vertex attributes for the Gouraud shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::GouraudShading> {};
/**
 * Vertex attributes for the Phong shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::PhongShading> {};
/**
 * Vertex attributes for the cel shading renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::CelShading> {};
/**
 * Vertex attributes for the depth mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::DepthMapping> {};
/**
 * Vertex attributes for the normal mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::NormalMapping> {
	/**
	 * The vertex's normal vector.
	 */
	math::Vector4d normal;
};
/**
 * Vertex attributes for the bump mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::BumpMapping> : VertexAttributes<RenderingAlgorithm::NormalMapping> {};
/**
 * Vertex attributes for the texture mapping renderer.
 */
template<>
struct VertexAttributes<RenderingAlgorithm::TextureMapping> : VertexAttributes<RenderingAlgorithm::BumpMapping> {
	/**
	 * The vertex's texture mapping coordinates.
	 */
	Point textureCoordinates;
};
} // namespace detail
} // namespace clockwork

#endif // CLOCKWORK_VERTEX_ATTRIBUTES_HH
