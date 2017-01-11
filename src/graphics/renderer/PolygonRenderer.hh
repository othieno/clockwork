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
#ifndef CLOCKWORK_POLYGON_RENDERER_HH
#define CLOCKWORK_POLYGON_RENDERER_HH

#include "Renderer.hh"
#include "RandomShadingShaderProgram.hh"
#include "FlatShadingShaderProgram.hh"
#include "GouraudShadingShaderProgram.hh"
#include "PhongShadingShaderProgram.hh"
#include "CelShadingShaderProgram.hh"
#include "DepthMapShaderProgram.hh"
#include "NormalMapShaderProgram.hh"
#include "BumpMapShaderProgram.hh"
#include "TextureMapShaderProgram.hh"


namespace clockwork {
/**
 *
 */
template<RenderingAlgorithm algorithm, class Implementation>
class PolygonRenderer : public Renderer<algorithm, Implementation> {
public:
	using Fragment = typename Renderer<algorithm, Implementation>::Fragment;
	using Varying = typename Renderer<algorithm, Implementation>::Varying;
	using Vertex = typename Renderer<algorithm, Implementation>::Vertex;
	using VertexArray = typename Renderer<algorithm, Implementation>::VertexArray;
	/**
	 * Sanitizes the rendering context and makes sure it is compatible with this renderer.
	 */
	static void sanitizeRenderingContext(RenderingContext&);
	/**
	 * Rearranges the specified set of vertices into a collection of geometric primitives.
	 */
	static void primitiveAssembly(const RenderingContext&, VertexArray&);
	/**
	 * Removes vertices that are not visible on the screen.
	 */
	static void clip(const RenderingContext&, VertexArray&);
	/**
	 * Converts the specified vertices into fragments that are written to the given framebuffer.
	 * @param context the rendering context.
	 * @param vertices the vertices to convert.
	 * @param framebuffer the framebuffer where fragments will be written to.
	 */
	static void rasterize(
		const RenderingContext& context,
		const VertexArray& vertices,
		Framebuffer& framebuffer
	);
};
/**
 *
 */
class RandomShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::RandomShading, RandomShadingRenderer> {};
/**
 *
 */
class FlatShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::FlatShading, FlatShadingRenderer> {};
/**
 *
 */
class GouraudShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::GouraudShading, GouraudShadingRenderer> {};
/**
 *
 */
class PhongShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::PhongShading, PhongShadingRenderer> {};
/**
 *
 */
class CelShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::CelShading, CelShadingRenderer> {};
/**
 *
 */
class DepthMapRenderer :
public PolygonRenderer<RenderingAlgorithm::DepthMapping, DepthMapRenderer> {};
/**
 *
 */
class NormalMapRenderer :
public PolygonRenderer<RenderingAlgorithm::NormalMapping, NormalMapRenderer> {};
/**
 *
 */
class BumpMapRenderer :
public PolygonRenderer<RenderingAlgorithm::BumpMapping, BumpMapRenderer> {};
/**
 *
 */
class TextureMapRenderer :
public PolygonRenderer<RenderingAlgorithm::TextureMapping, TextureMapRenderer> {};


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::sanitizeRenderingContext(RenderingContext& context) {
	// The Polygon renderer only draws triangle primitives so if the primitive mode
	// is not set to Triangle, TriangleStrip or TriangleFan, it will be set to TriangleStrip.
	auto& mode = context.primitiveMode;
	if (mode != Primitive::Triangle && mode != Primitive::TriangleStrip && mode != Primitive::TriangleFan) {
		mode = Primitive::TriangleStrip;
	}
}


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::primitiveAssembly(const RenderingContext&, VertexArray& vertices) {
	// TODO This will only generate triangle primitives. Implement TriangleStrip and
	// TriangleLoop generation.
	static const auto lessThan = [](const Vertex& a, const Vertex& b) {
		const auto& pa = a.position;
		const auto& pb = b.position;
		if (qFuzzyCompare(1.0 + pa.y(), 1.0 + pb.y())) {
			if (qFuzzyCompare(1.0 + pa.x(), 1.0 + pb.x())) {
				return pa.z() < pb.z();
			} else {
				return pa.x() < pb.x();
			}
		} else {
			return pa.y() < pb.y();
		}
	};
	// If the triangle primitive is not correctly formed for the scanline algorithm,
	// then tessellate two triangle primitives that fit our needs.
	for (auto it = vertices.begin(); it != vertices.end();) {
		const auto& from = it;
		const auto& to = it + 3;

		std::sort(from, to, lessThan); // Note: std::sort processes the range [first, last[.

		// Tessellate the primitive, if need be.
		const auto& V0 = it[0];
		const auto& V1 = it[1];
		const auto& V2 = it[2];

		const auto& p0 = V0.position;
		const auto& p1 = V1.position;
		const auto& p2 = V2.position;

		const bool tessellate = !qFuzzyCompare(1.0 + p0.y(), 1.0 + p1.y()) && !qFuzzyCompare(1.0 + p1.y(), 1.0 + p2.y());
		if (tessellate) {
			// Create a new output that will be used to create two new primitives.
			auto V = Vertex::lerp(V0, V2, (p1.y() - p0.y()) / (p2.y() - p0.y()));
			V.position.setY(p1.y());
			//V.position.z = 0; //FIXME Depth needs to be interpolated between V1 and O3.

			// Create two new triangle primitives: {V0, V1, V} and {V1, V, V2}. Since the
			// original array of outputs is {V0, V1, V2}, it becomes {V0, V1, V, V1, V, V2}.
			it = vertices.insert(it + 2, V);
			it = vertices.insert(it + 1, V1);
			it = vertices.insert(it + 1, V);
			it = std::next(it, 2);
		} else {
			it = to;
		}
	}
}


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::clip(const RenderingContext&, VertexArray&) {}


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::rasterize(
	const RenderingContext& context,
	const VertexArray& vertices,
	Framebuffer& framebuffer
) {
	for (auto it = vertices.begin(); it != vertices.end(); it += 3) {
		const auto* a = &it[1];
		const auto* b = &it[0];
		const auto* c = &it[2];
		if (qFuzzyCompare(1.0 + a->position.y(), 1.0 + b->position.y())) {
			a = &it[0];
			b = &it[2];
			c = &it[1];
		}

		const double ay = std::round(a->position.y());
		const double by = std::round(b->position.y());
		//const double cy = ay; // since a and c are colinear.
		const double dy = by - ay; // or by - cy.

		// If the dy is relatively small, all 3 points are considered colinear.
		constexpr double EPSILON = 1e-5;
		if (std::abs(dy) < EPSILON) {
			// TODO Handle cases where all 3 vertices are colinear.
		} else {
			auto ymin = static_cast<std::uint32_t>(ay);
			auto ymax = static_cast<std::uint32_t>(by);
			if (ymin > ymax) {
				std::swap(ymin, ymax);
			}
			for (auto y = ymin; y <= ymax; ++y) {
				const double p = (y - ay) / dy;
				const auto from = Vertex::lerp(*a, *b, p);
				const auto to = Vertex::lerp(*c, *b, p);

				const double Fx = std::round(from.position.x());
				const double Tx = std::round(to.position.x());
				const double dx = Tx - Fx;

				// If dx is relatively small, the 'from' and 'to' vertices are
				// considered identical so there's no need to interpolate any
				// new vertices between them.
				if (std::abs(dx) < EPSILON) {
					T::fragmentProcessing(context, Fragment(from), framebuffer);
				} else {
					auto xmin = static_cast<std::uint32_t>(Fx);
					auto xmax = static_cast<std::uint32_t>(Tx);
					if (xmin > xmax) {
						std::swap(xmin, xmax);
					}
					for (auto x = xmin; x <= xmax; ++x) {
						const double p = (x - Fx) / dx;
						const auto vertex = Vertex::lerp(from, to, p);
						Fragment fragment(vertex);
						fragment.x = x;
						fragment.y = y;
						T::fragmentProcessing(context, fragment, framebuffer);
					}
				}
			}
		}
	}
}
} // namespace clockwork

#endif // CLOCKWORK_POLYGON_RENDERER_HH
