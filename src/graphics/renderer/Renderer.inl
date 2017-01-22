/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
#ifndef CLOCKWORK_RENDERER_INL
#define CLOCKWORK_RENDERER_INL

#include "RenderingContext.hh"
#include "Framebuffer.hh"


namespace clockwork {

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
Renderer<A, T>::draw(const RenderingContext& context, const Mesh& mesh, Framebuffer& framebuffer) {
	if (mesh.faces.isEmpty()) {
		return;
	}
	for (const auto& face : mesh.faces) {
		VertexArray vertices = vertexProcessing(context, face);

		vertexPostProcessing(context, vertices);
		primitiveAssembly(context, vertices);
		rasterization(context, vertices, framebuffer);
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
Renderer<A, T>::vertexPostProcessing(const RenderingContext& context, VertexArray& vertices) {
	if (vertices.isEmpty()) {
		return;
	}
	if (context.enableClipping) {
		switch (context.primitiveTopology) {
			case PrimitiveTopology::Point:
				clipPointPrimitives(context, vertices);
				break;
			case PrimitiveTopology::Line:
			case PrimitiveTopology::LineStrip:
			case PrimitiveTopology::LineLoop:
				clipLinePrimitives(context, vertices);
				break;
			case PrimitiveTopology::Triangle:
			case PrimitiveTopology::TriangleStrip:
			case PrimitiveTopology::TriangleFan:
				clipTrianglePrimitives(context, vertices);
				break;
			default:
				break;
		}
	}

	// Convert the vertex positions from clip space to screen (window) space.
	const qreal Sx = context.viewportTransform(0, 0);
	const qreal Sy = context.viewportTransform(1, 0);
	const qreal Sz = context.viewportTransform(2, 0);

	const qreal Tx = context.viewportTransform(0, 1);
	const qreal Ty = context.viewportTransform(1, 1);
	const qreal Tz = context.viewportTransform(2, 1);

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
Renderer<A, T>::primitiveAssembly(const RenderingContext& context, VertexArray& vertices) {
	if (vertices.isEmpty()) {
		return;
	}
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
		default:
			break;
	}
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::rasterization(const RenderingContext& context, VertexArray& vertices, Framebuffer& framebuffer) {
	if (vertices.isEmpty()) {
		return;
	}
	switch (context.primitiveTopology) {
		case PrimitiveTopology::Point:
			rasterizePointPrimitives(context, vertices, framebuffer);
			break;
		case PrimitiveTopology::Line:
		case PrimitiveTopology::LineStrip:
		case PrimitiveTopology::LineLoop:
			rasterizeLinePrimitives(context, vertices, framebuffer);
			break;
		case PrimitiveTopology::Triangle:
		case PrimitiveTopology::TriangleStrip:
		case PrimitiveTopology::TriangleFan:
			rasterizeTrianglePrimitives(context, vertices, framebuffer);
			break;
		default:
			break;
	}
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::clipPointPrimitives(const RenderingContext&, VertexArray& vertices) {
	if (vertices.isEmpty()) {
		return;
	}
	static const auto& filter = [](const Vertex& vertex) {
		// Use a normalized 2D viewing volume: [-1, 1] x [-1, 1].
		constexpr double xmin = -1.0;
		constexpr double xmax =  1.0;
		constexpr double ymin = -1.0;
		constexpr double ymax =  1.0;

		const auto& p = vertex.position;
		return p.x() < xmin || p.x() > xmax || p.y() < ymin || p.y() > ymax;
	};
	const auto& begin = vertices.begin();
	const auto& end = vertices.end();

	vertices.erase(std::remove_if(begin, end, filter), end);
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::clipLinePrimitives(const RenderingContext& context, VertexArray& vertices) {
	Q_UNUSED(context);
	Q_UNUSED(vertices);
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::clipTrianglePrimitives(const RenderingContext& context, VertexArray& vertices) {
	Q_UNUSED(context);
	Q_UNUSED(vertices);
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
		if (context.enableBackfaceCulling && isBackFacePrimitive(context, from)) {
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
Renderer<A, T>::rasterizePointPrimitives(
	const RenderingContext& context,
	VertexArray& vertices,
	Framebuffer& framebuffer
) {
	for (const auto& vertex : vertices) {
		fragmentProcessing(context, Fragment(vertex), framebuffer);
	}
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::rasterizeLinePrimitives(
	const RenderingContext& context,
	VertexArray& vertices,
	Framebuffer& framebuffer
) {
	Q_UNUSED(context);
	Q_UNUSED(vertices);
	Q_UNUSED(framebuffer);
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::rasterizeTrianglePrimitives(
	const RenderingContext& context,
	VertexArray& vertices,
	Framebuffer& framebuffer
) {
	Q_UNUSED(context);
	Q_UNUSED(vertices);
	Q_UNUSED(framebuffer);
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

#endif // CLOCKWORK_RENDERER_INL
