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
	// The Polygon renderer only draws triangle primitives so if the primitive topology
	// is not set to Triangle, TriangleStrip or TriangleFan, it will be set to TriangleStrip.
	auto& t = context.primitiveTopology;
	if (t != PrimitiveTopology::Triangle && t != PrimitiveTopology::TriangleStrip && t != PrimitiveTopology::TriangleFan) {
		t = PrimitiveTopology::TriangleStrip;
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

		const int ay = qRound(a->position.y());
		const int by = qRound(b->position.y());
//		const int cy = ay; // since a and c are colinear.
		const int dy = by - ay; // or by - cy.

		int ymin = ay;
		int ymax = by;
		if (ymax < ymin) {
			std::swap(ymin, ymax);
		}
		for (int y = ymin; y <= ymax; ++y) {
			const qreal p = (y - ay) / static_cast<qreal>(dy);
			const Vertex from(Vertex::lerp(*a, *b, p));
			const Vertex to(Vertex::lerp(*c, *b, p));

			const int Fx = qRound(from.position.x());
			const int Tx = qRound(to.position.x());
			const int dx = Tx - Fx;

			// If dx is equal to zero, the 'from' and 'to' vertices are
			// considered identical so there's no need to interpolate any
			// new vertices between them.
			if (dx == 0) {
				T::fragmentProcessing(context, Fragment(from), framebuffer);
			} else {
				int xmin = Fx;
				int xmax = Tx;
				if (xmax < xmin) {
					std::swap(xmin, xmax);
				}
				for (int x = xmin; x <= xmax; ++x) {
					const qreal p = (x - Fx) / static_cast<qreal>(dx);
					Fragment fragment(Vertex::lerp(from, to, p));
					fragment.x = x;
					fragment.y = y;
					T::fragmentProcessing(context, fragment, framebuffer);
				}
			}
		}
	}
}
} // namespace clockwork

#endif // CLOCKWORK_POLYGON_RENDERER_HH
