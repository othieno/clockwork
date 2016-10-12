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
#ifndef CLOCKWORK_POLYGON_RENDERER_HH
#define CLOCKWORK_POLYGON_RENDERER_HH

#include "Renderer.hh"
#include <cmath>


namespace clockwork {
/**
 *
 */
template<RenderingAlgorithm algorithm, class Implementation>
class PolygonRenderer : public Renderer<algorithm, Implementation> {
public:
	using Fragment = typename Renderer<algorithm, Implementation>::Fragment;
	using FragmentArray = typename Renderer<algorithm, Implementation>::FragmentArray;
	using Varying = typename Renderer<algorithm, Implementation>::Varying;
	using Vertex = typename Renderer<algorithm, Implementation>::Vertex;
	using VertexArray = typename Renderer<algorithm, Implementation>::VertexArray;
	/**
	 *
	 */
	static void primitiveAssembly(const RenderingContext&, VertexArray&);
	/**
	 *
	 */
	static FragmentArray rasterize(const RenderingContext&, const VertexArray&);
};


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::primitiveAssembly(const RenderingContext&, VertexArray& vertices) {
	// TODO This will only generate triangle primitives. Implement TriangleStrip and
	// TriangleLoop generation.
	static const auto compare = [](const Vertex& a, const Vertex& b) {
		const auto& pa = a.position;
		const auto& pb = b.position;
		if (qFuzzyCompare(1.0 + pa.y, 1.0 + pb.y)) {
			if (qFuzzyCompare(1.0 + pa.x, 1.0 + pb.x)) {
				return pa.z < pb.z;
			} else {
				return pa.x < pb.x;
			}
		} else {
			return pa.y < pb.y;
		}
	};
	// If the triangle primitive is not correctly formed for the scanline algorithm,
	// then tessellate two triangle primitives that fit our needs.
	for (auto it = vertices.begin(); it != vertices.end();) {
		const auto& from = it;
		const auto& to = it + 3;

		std::sort(from, to, compare); // Note: std::sort process the range [first, last).

		// Tessellate the primitive, if need be.
		const auto& V0 = it[0];
		const auto& V1 = it[1];
		const auto& V2 = it[2];

		const auto& p0 = V0.position;
		const auto& p1 = V1.position;
		const auto& p2 = V2.position;

		//const bool tessellate = !qFuzzyCompare(1.0 + p0.y, 1.0 + p1.y) && !qFuzzyCompare(1.0 + p1.y, 1.0 + p2.y);
		const bool tessellate = !qFuzzyCompare(1.0 + p0.y, 1.0 + p1.y) && !qFuzzyCompare(1.0 + p1.y, 1.0 + p2.y);
		if (tessellate) {
			// Create a new output that will be used to create two new primitives.
			Vertex V = T::lerp(V0, V2, (p1.y - p0.y) / (p2.y - p0.y));
			V.position.y = p1.y;
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


template<RenderingAlgorithm A, class T> typename PolygonRenderer<A, T>::FragmentArray
PolygonRenderer<A, T>::rasterize(const RenderingContext&, const VertexArray& vertices) {
	FragmentArray fragments;
	for (auto it = vertices.begin(); it != vertices.end();) {
		const Fragment f0 = T::createFragment(*it++);
		const Fragment f1 = T::createFragment(*it++);
		const Fragment f2 = T::createFragment(*it++);
		fragments.append(f0);
		fragments.append(f1);
		fragments.append(f2);

		const Fragment* a = &f1;
		const Fragment* b = &f0;
		const Fragment* c = &f2;
		if (f0.y == f1.y) {
			a = &f0;
			b = &f2;
			c = &f1;
		}

		const double dys = int(b->y - a->y);
		const double dye = int(b->y - c->y);

		// Remember that the outputs are sorted in the primitive assemlby step so f0.y <= f2.y.
		for (std::uint32_t y = f0.y; y <= f2.y; ++y) {
			const double ps = int(y - a->y) / dys;
			const Fragment fs = T::lerp(*a, *b, ps);
			std::uint32_t xmin = std::round(((1.0 - ps) * a->x) + (ps * b->x));

			const double pe = int(y - c->y) / dye;
			const Fragment fe = T::lerp(*c, *b, pe);
			std::uint32_t xmax = std::round(((1.0 - pe) * c->x) + (pe * b->x));

			if (xmin > xmax) {
				std::swap(xmin, xmax);
			}
			for (std::uint32_t x = xmin; x <= xmax; ++x) {
				const double p = (x - fs.x) / double(fe.x - fs.x);
				Fragment f = T::lerp(fs, fe, p);
				f.x = x;
				f.y = y;
				fragments.append(f);
			}
		}
	}
	return fragments;
}
} // namespace clockwork

#endif // CLOCKWORK_POLYGON_RENDERER_HH
