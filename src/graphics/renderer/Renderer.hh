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
	using ShaderProgram = detail::ShaderProgram<algorithm>;
	using Fragment = typename ShaderProgram::Fragment;
	using FragmentArray = QList<Fragment>;
	using Varying = typename ShaderProgram::Varying;
	using Vertex = typename ShaderProgram::Vertex;
	using VertexArray = QList<Vertex>;
	using VertexAttributes = typename ShaderProgram::VertexAttributes;
	static_assert(std::is_base_of<clockwork::Fragment, Fragment>::value);
	static_assert(std::is_base_of<clockwork::Vertex, Vertex>::value);
	static_assert(std::is_base_of<clockwork::VertexAttributes, VertexAttributes>::value);
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
	static void toScreenSpace(const ViewportTransform& transform, VertexArray& vertices);
	/**
	 *
	 */
	static void fragmentProcessing(const RenderingContext&, Framebuffer&, const FragmentArray&);
private:
	/**
	 * Returns true if the specified fragment passes all fragment tests, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPasses(const RenderingContext& context, const Fragment& fragment);
};


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::draw(RenderingContext& context, const Mesh& mesh) {
	auto* const framebuffer = context.framebuffer;
	if (framebuffer == nullptr || mesh.faces.isEmpty()) {
		return;
	}

	T::sanitizeContext(context);

	for (const auto& face : mesh.faces) {
		VertexArray vertices = vertexProcessing(context, face);
		T::primitiveAssembly(context, vertices);
		cull(context, vertices);
		T::clip(context, vertices);
		if (vertices.isEmpty()) {
			continue;
		}
		toScreenSpace(context.viewportTransform, vertices);
		const auto& fragments = T::rasterize(context, vertices);
		fragmentProcessing(context, *context.framebuffer, fragments);
	}
}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::VertexArray
Renderer<A, T>::vertexProcessing(const RenderingContext& context, const Mesh::Face& face) {
	static VertexAttributes attributes;
	static Varying varying;

	VertexArray vertices;
	for (std::size_t i = 0; i < face.length; ++i) {
		T::ShaderProgram::setVertexAttributes(attributes, face, i);
		T::ShaderProgram::setVarying(varying, face, i);

		// Perform the per-vertex operation, after which the set of varying variables is
		// attached to the output for use in later stages of the pipeline.
		auto vertex = T::ShaderProgram::vertexShader(context.uniforms, varying, attributes);
		vertex.varying = varying;

		vertices.append(vertex);
	}
	return vertices;
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::cull(const RenderingContext&, VertexArray&) {}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::toScreenSpace(const ViewportTransform& viewportTransform, VertexArray& vertices) {
	for (auto& vertex : vertices) {
		// Perspective divide: Convert the vertex position from clipping
		// coordinate space to normalized device coordinate (NDC) space.
		auto& position = vertex.position;
		position.x /= position.w;
		position.y /= position.w;
		position.z /= position.w;
		position.w /= 1.0;

		// Then convert the position from NDC space to screen space.
		position = position * viewportTransform;
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
		const int offset = framebuffer.getOffset(f.x, f.y);
		if (offset >= 0 && fragmentPasses(context, f)) {
			pbuffer[offset] = T::ShaderProgram::fragmentShader(context.uniforms, f.varying, f);
			zbuffer[offset] = f.z;
			sbuffer[offset] = f.stencil;
		}
	}
}


template<RenderingAlgorithm A, class T> bool
Renderer<A, T>::fragmentPasses(const RenderingContext&, const Fragment&) {
	return true;
}
} // namespace clockwork

#endif // CLOCKWORK_RENDERER_HH
