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
#ifndef CLOCKWORK_RENDERER_HH
#define CLOCKWORK_RENDERER_HH

#include "RenderingContext.hh"
#include "Framebuffer.hh"
#include "Mesh.hh"
#include "ShaderProgram.hh"


namespace clockwork {
/**
 *
 */
template<RenderingAlgorithm algorithm, class Implementation>
class Renderer {
public:
	/**
	 *
	 */
	using ShaderProgram = detail::ShaderProgram<algorithm>;
	/**
	 *
	 */
	using Varying = typename ShaderProgram::Varying;
	/**
	 *
	 */
	struct Vertex : ShaderProgram::Vertex {
		/**
		 * Instantiates a Vertex object.
		 */
		Vertex() = default;
		/**
		 * Instantiates a Vertex object based on the specified ShaderProgram vertex.
		 */
		explicit Vertex(const typename ShaderProgram::Vertex&);
		/**
		 * Performs a linear interpolation to find the Vertex at a specified
		 * percentage between two Vertex instances.
		 */
		static Vertex lerp(const Vertex& from, const Vertex& to, const double percentage);
		/**
		 * The set of varying variables that accompany the vertex throughout
		 * the rendering pipeline.
		 */
		Varying varying;
	};
	static_assert(std::is_base_of<BaseVertex, Vertex>::value);
	/**
	 *
	 */
	using VertexArray = QList<Vertex>;
	/**
	 *
	 */
	using VertexAttributes = typename ShaderProgram::VertexAttributes;
	static_assert(std::is_base_of<BaseVertexAttributes, VertexAttributes>::value);
	/**
	 *
	 */
	struct Fragment : ShaderProgram::Fragment {
		/**
		 * Instantiates a Fragment object.
		 */
		Fragment() = default;
		/**
		 * Instantiates a Fragment object based on the specified ShaderProgram fragment.
		 */
		explicit Fragment(const typename ShaderProgram::Fragment&);
		/**
		 * Instantiates a Fragment object based on the specified Vertex object.
		 */
		explicit Fragment(const Vertex&);
		/**
		 * Performs a linear interpolation to find the Fragment at a specified
		 * percentage between two Fragment instances.
		 */
		static Fragment lerp(const Fragment& from, const Fragment& to, const double percentage);
		/**
		 * The set of varying variables that accompany the fragment throughout
		 * the rendering pipeline.
		 */
		Varying varying;
	};
	static_assert(std::is_base_of<BaseFragment, Fragment>::value);
	/**
	 * Renders the specified mesh in the given context.
	 * @param context the rendering context.
	 * @param mesh the polygon mesh to render.
	 */
	static void draw(RenderingContext& context, const Mesh& mesh);
protected:
	/**
	 *
	 */
	static VertexArray vertexProcessing(const RenderingContext& context, const Mesh::Face& face);
	/**
	 *
	 */
	static void cull(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void fragmentProcessing(const RenderingContext&, const Fragment&, Framebuffer&);
private:
	/**
	 * Rearranges the specified set of vertices into a collection of line primitives.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to rearrange.
	 */
	static void assembleLinePrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Rearranges the specified set of vertices into a collection of triangle primitives.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to rearrange.
	 */
	static void assembleTrianglePrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Returns true if a triangle primitive is not facing the viewer, false otherwise.
	 * @param context the rendering context.
	 * @param offset an iterator to the first element of the primitive to query.
	 */
	static bool isBackFacePrimitive(const RenderingContext& context, const typename VertexArray::iterator& offset);
	/**
	 * Rearranges the specified set of vertices into a collection of geometric primitives.
	 * @param topology the primitive topology that the vertices will be rearranged into.
	 * @param vertices the set of vertices to rearrange.
	 */
	static void primitiveAssembly(const PrimitiveTopology topology, VertexArray& vertices);
	/**
	 * Converts the coordinates for each of the specified vertices from clipping space to
	 * normalized device coordinate space to screen space.
	 * @param viewportTransform the viewport transformation matrix.
	 * @param vertices the collection of vertices to convert.
	 */
	static void toScreenSpace(const QMatrix2x3& viewportTransform, VertexArray& vertices);
	/**
	 * Tests whether the specified fragment can be written to the framebuffer. If
	 * the specified fragment passes all tests, the function will return a framebuffer
	 * offset indicating a location where the fragment data can be written to.
	 * If a fragment test fails, -1 will be returned.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static int fragmentPasses(const RenderingContext& context, const Fragment& fragment);
};


template<RenderingAlgorithm A, class T>
Renderer<A, T>::Vertex::Vertex(const typename ShaderProgram::Vertex& vertex) :
ShaderProgram::Vertex(vertex) {}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::Vertex
Renderer<A, T>::Vertex::lerp(const Vertex& from, const Vertex& to, const double p) {
	Vertex vertex(ShaderProgram::Vertex::lerp(from, to, p));
	vertex.varying = std::move(Varying::lerp(from.varying, to.varying, p));

	return vertex;
}


template<RenderingAlgorithm A, class T>
Renderer<A, T>::Fragment::Fragment(const typename ShaderProgram::Fragment& fragment) :
ShaderProgram::Fragment(fragment) {}


template<RenderingAlgorithm A, class T>
Renderer<A, T>::Fragment::Fragment(const Vertex& vertex) :
ShaderProgram::Fragment(vertex),
varying(vertex.varying) {}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::Fragment
Renderer<A, T>::Fragment::lerp(const Fragment& from, const Fragment& to, const double p) {
	Fragment fragment(ShaderProgram::Fragment::lerp(from, to, p));
	fragment.varying = std::move(Varying::lerp(from.varying, to.varying, p));

	return fragment;
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::draw(RenderingContext& context, const Mesh& mesh) {
	if (mesh.faces.isEmpty()) {
		return;
	}
	const auto& viewportTransform = context.uniforms["VIEWPORT"].as<const QMatrix2x3>();

	T::sanitizeRenderingContext(context);
	for (const auto& face : mesh.faces) {
		VertexArray vertices = vertexProcessing(context, face);

		switch (context.primitiveTopology) {
			case PrimitiveTopology::Line:
			case PrimitiveTopology::LineStrip:
			case PrimitiveTopology::LineLoop:
				assembleLinePrimitives(context, vertices);
				break;
			case PrimitiveTopology::Triangle:
			case PrimitiveTopology::TriangleStrip:
			case PrimitiveTopology::TriangleFan:
				assembleTrianglePrimitives(context, vertices);
				break;
			case PrimitiveTopology::Point:
			default:
				break;
		}

		cull(context, vertices);
		T::clip(context, vertices);
		if (vertices.isEmpty()) {
			continue;
		}
		toScreenSpace(viewportTransform, vertices);
		T::rasterize(context, vertices, context.framebuffer);
	}
}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::VertexArray
Renderer<A, T>::vertexProcessing(const RenderingContext& context, const Mesh::Face& face) {
	static VertexAttributes attributes;
	VertexArray vertices;
	for (std::size_t i = 0; i < face.length; ++i) {
		T::ShaderProgram::setVertexAttributes(attributes, face, i);

		Varying varying;
		Vertex vertex(T::ShaderProgram::vertexShader(context.uniforms, varying, attributes));
		vertex.varying = std::move(varying);

		vertices.append(vertex);
	}
	return vertices;
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::assembleLinePrimitives(const RenderingContext& context, VertexArray& vertices) {
	if (vertices.isEmpty()) {
		return;
	}
	// In the case of Line primitives, the number of vertices must be
	// even to prevent accessing data out of the vertex array. If the
	// number of vertices is odd, the last vertex is simply discared.
	if (context.primitiveTopology == PrimitiveTopology::Line) {
		if (vertices.size() & 1) {
			vertices.removeLast();
		}
	}
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::assembleTrianglePrimitives(const RenderingContext& context, VertexArray& vertices) {
	if (vertices.isEmpty()) {
		return;
	}

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

	//FIXME This implementation does not work for triangle strips and fans.

	for (auto it = vertices.begin(); it != vertices.end();) {
		const auto& from = it;
		const auto& to = it + 3;

		// Cull backfacing triangle primitives.
		if (isBackFacePrimitive(context, from)) {
			it = vertices.erase(from, to);
			continue;
		}

		// The scanline algorithm is used to fill polygons. It requires that triangle primitives
		// be a certain form which may require a tessellation step for some primitives.
		if (context.polygonMode == PolygonMode::Fill) {
			std::sort(from, to, lessThan); // Note: std::sort processes the range [first, last[.

			const auto& V0 = it[0];
			const auto& V1 = it[1];
			const auto& V2 = it[2];

			const auto& p0 = V0.position;
			const auto& p1 = V1.position;
			const auto& p2 = V2.position;

			// Tessellate the primitive, if need be.
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

				continue;
			}
		}
		it = to;
	}
}


template<RenderingAlgorithm A, class T> bool
Renderer<A, T>::isBackFacePrimitive(const RenderingContext& context, const typename VertexArray::iterator& from) {
	if (context.primitiveTopology == PrimitiveTopology::Triangle) {
		const QVector3D p0(from[0].position.toVector3DAffine());
		const QVector3D p1(from[1].position.toVector3DAffine());
		const QVector3D p2(from[2].position.toVector3DAffine());

		return QVector3D::crossProduct(p1 - p0, p2 - p1).z() <= 0;
	} else if (context.primitiveTopology == PrimitiveTopology::TriangleStrip) {
		qFatal("[isBackFacePrimitive] Implement me!");
	} else if (context.primitiveTopology == PrimitiveTopology::TriangleFan) {
		qFatal("[isBackFacePrimitive] Implement me!");
	}
	return false;
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::primitiveAssembly(const PrimitiveTopology topology, VertexArray& vertices) {
	if (vertices.isEmpty() ||
		topology == PrimitiveTopology::Point ||
		topology == PrimitiveTopology::LineStrip ||
		topology == PrimitiveTopology::LineLoop
	) {
		return;
	}

	if (topology == PrimitiveTopology::Line) {
		// In the case of Line primitives, the number of vertices must be
		// even to prevent accessing data out of the vertex array. If the
		// number of vertices is odd, the last vertex is simply discared.
		if (vertices.size() & 1) {
			vertices.removeLast();
		}
		return;
	}

	// Generate triangle primitives.
	// TODO Implement TriangleStrip and TriangleLoop assembly (if there's even a difference).
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
Renderer<A, T>::cull(const RenderingContext&, VertexArray&) {}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::toScreenSpace(const QMatrix2x3& transform, VertexArray& vertices) {
	const qreal Sx = transform(0, 0);
	const qreal Sy = transform(1, 0);
	const qreal Sz = transform(2, 0);

	const qreal Tx = transform(0, 1);
	const qreal Ty = transform(1, 1);
	const qreal Tz = transform(2, 1);

	for (auto& vertex : vertices) {
		auto& position = vertex.position;

		// Convert the vertex position from clipping space to normalized
		// device coordinate (NDC) space ...
		const qreal w = position.w();
		const qreal x = position.x() / w;
		const qreal y = position.y() / w;
		const qreal z = position.z() / w;

		// ... then to screen space.
		position.setX((x * Sx) + Tx);
		position.setY((y * Sy) + Ty);
		position.setZ((z * Sz) + Tz);
		position.setW(1.0);
	}
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::fragmentProcessing(
	const RenderingContext& context,
	const Fragment& fragment,
	Framebuffer& framebuffer
) {
	auto* const pbuffer = framebuffer.getPixelBuffer();
	auto* const zbuffer = framebuffer.getDepthBuffer();
	auto* const sbuffer = framebuffer.getStencilBuffer();

	const int offset = fragmentPasses(context, fragment);
	if (offset >= 0) {
		pbuffer[offset] = T::ShaderProgram::fragmentShader(context.uniforms, fragment.varying, fragment);
		zbuffer[offset] = fragment.z;
		sbuffer[offset] = 0xFF;
	}
}


template<RenderingAlgorithm A, class T> int
Renderer<A, T>::fragmentPasses(const RenderingContext& context, const Fragment& fragment) {
	const int offset = context.framebuffer.getOffset(fragment.x, fragment.y);
	if (offset >= 0) {
		if (context.enableDepthTest) {
			const double depthBufferValue = context.framebuffer.getDepthBuffer()[offset];
			if (qFuzzyCompare(1.0 + fragment.z, 1.0 + depthBufferValue) || fragment.z > depthBufferValue) {
				return -1;
			}
		}
		// TODO Implement more fragment tests.
		// @see https://www.opengl.org/wiki/Per-Sample_Processing
	}
	return offset;
}
} // namespace clockwork
#endif // CLOCKWORK_RENDERER_HH
