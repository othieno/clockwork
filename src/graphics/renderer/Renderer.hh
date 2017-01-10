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
	using Fragment = typename ShaderProgram::Fragment;
	static_assert(std::is_base_of<BaseFragment, Fragment>::value);
	/**
	 *
	 */
	struct PipelineFragment {
		/**
		 * Instantiates a PipelineFragment object.
		 */
		PipelineFragment() = default;
		/**
		 * Instantiates a PipelineFragment object based on the specified Vertex object.
		 */
		explicit PipelineFragment(const Vertex& vertex);
		/**
		 * Performs a linear interpolation to find the PipelineFragment at a specified
		 * percentage between two PipelineFragment instances.
		 */
		static PipelineFragment lerp(const PipelineFragment& from, const PipelineFragment& to, const double percentage);
		/**
		 * The actual fragment data.
		 */
		Fragment data;
		/**
		 * The set of varying variables that accompany the fragment throughout
		 * the rendering pipeline.
		 */
		Varying varying;
	};
	/**
	 *
	 */
	using FragmentArray = QList<PipelineFragment>;
	/**
	 * Renders the specified mesh in the given context.
	 * @param context the rendering context.
	 * @param mesh the polygon mesh to render.
	 */
	static void draw(RenderingContext& context, const Mesh& mesh);
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
	static void fragmentProcessing(const RenderingContext&, Framebuffer&, const FragmentArray&);
private:
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
Renderer<A, T>::PipelineFragment::PipelineFragment(const Vertex& vertex) :
data(vertex),
varying(vertex.varying) {}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::PipelineFragment
Renderer<A, T>::PipelineFragment::lerp(const PipelineFragment& from, const PipelineFragment& to, const double p) {
	PipelineFragment fragment;
	fragment.data = Fragment::lerp(from.data, to.data, p);
	fragment.varying = Varying::lerp(from.varying, to.varying, p);
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
		T::primitiveAssembly(context, vertices);
		cull(context, vertices);
		T::clip(context, vertices);
		if (vertices.isEmpty()) {
			continue;
		}
		toScreenSpace(viewportTransform, vertices);
		const auto& fragments = T::rasterize(context, vertices);
		fragmentProcessing(context, context.framebuffer, fragments);
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
Renderer<A, T>::fragmentProcessing(const RenderingContext& context, Framebuffer& framebuffer, const FragmentArray& fragments) {
	if (fragments.isEmpty()) {
		return;
	}
	auto* const pbuffer = framebuffer.getPixelBuffer();
	auto* const zbuffer = framebuffer.getDepthBuffer();
	auto* const sbuffer = framebuffer.getStencilBuffer();
	for (const auto& f : fragments) {
		const auto& fragment = f.data;
		const auto& varying = f.varying;
		const int offset = fragmentPasses(context, fragment);
		if (offset >= 0) {
			pbuffer[offset] = T::ShaderProgram::fragmentShader(context.uniforms, varying, fragment);
			zbuffer[offset] = fragment.z;
			sbuffer[offset] = 0xFF;
		}
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
