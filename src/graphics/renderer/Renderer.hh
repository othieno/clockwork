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
	 * Builds a list of geometric primitives.
	 * This function should be implemented in an explicit template specialization.
	 */
	static void primitiveAssembly(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void cull(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Removes vertex shader outputs that are not visible on the screen.
	 * This function should be implemented in an explicit template specialization.
	 */
	static void clip(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void toScreenSpace(const ViewportTransform& transform, VertexArray& vertices);
	/**
	 * Generates a list of fragments from the specified vertex array.
	 * This function should be implemented in an explicit template specialization.
	 */
	static FragmentArray rasterize(const RenderingContext& context, const VertexArray& vertices);
	/**
	 *
	 */
	static void fragmentProcessing(RenderingContext& context, const FragmentArray& fragments);
private:
	/**
	 * Returns true if the specified fragment passes all fragment tests, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPasses(const RenderingContext& context, const Fragment& fragment);
	/**
	 * Returns a default VertexAttributes object.
	 */
	static VertexAttributes createVertexAttributes(const Mesh::Face& face, const std::size_t i) {
		return i < face.length ? VertexAttributes(*face.positions[i]) : VertexAttributes();
	}
	/**
	 * Returns a dummy Varying object.
	 * This function should be implemented in an explicit template specialization.
	 */
	static Varying createVarying(const Mesh::Face&, const std::size_t) {
		return Varying();
	}
	/**
	 * Performs a basic per-vertex operation.
	 */
	static Vertex vertexShader(const Uniforms& uniforms, Varying&, const VertexAttributes& attributes) {
		const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const Matrix4>();

		Vertex output;
		output.position = MVP * Point4(attributes.position);

		return output;
	}
	/**
	 * Returns a pixel value.
	 * This function should be implemented in an explicit template specialization.
	 */
	static std::uint32_t fragmentShader(const Uniforms&, const Varying&, const Fragment&) {
		return 0xFFFFFFFF;
	}
};


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::draw(RenderingContext& context, const Mesh& mesh) {
	auto* const framebuffer = context.framebuffer;
	if (framebuffer == nullptr || mesh.faces.isEmpty()) {
		return;
	}
	for (const auto& face : mesh.faces) {
		VertexArray vertices = T::vertexProcessing(context, face);
		T::primitiveAssembly(context, vertices);
		T::cull(context, vertices);
		T::clip(context, vertices);
		if (vertices.isEmpty()) {
			continue;
		}
		T::toScreenSpace(context.viewportTransform, vertices);
		const auto& fragments = T::rasterize(context, vertices);
		T::fragmentProcessing(context, fragments);
	}
}


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::VertexArray
Renderer<A, T>::vertexProcessing(const RenderingContext& context, const Mesh::Face& face) {
	VertexArray vertices;
	for (std::size_t i = 0; i < face.length; ++i) {
		// Per-vertex operation.
		auto varying = T::createVarying(face, i);
		const auto& attributes = T::createVertexAttributes(face, i);
		auto vertex = T::vertexShader(context.uniforms, varying, attributes);

		// Attach the varying variables to the vertex shader's output for use by the
		// fragment shader later on.
		vertex.varying = std::move(varying);

		vertices.append(vertex);
	}
	return vertices;
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::primitiveAssembly(const RenderingContext&, VertexArray&) {}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::cull(const RenderingContext&, VertexArray&) {}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::clip(const RenderingContext&, VertexArray&) {}


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


template<RenderingAlgorithm A, class T> typename Renderer<A, T>::FragmentArray
Renderer<A, T>::rasterize(const RenderingContext&, const VertexArray&) {
	return FragmentArray();
}


template<RenderingAlgorithm A, class T> void
Renderer<A, T>::fragmentProcessing(RenderingContext& context, const FragmentArray& fragments) {
	auto* framebuffer = context.framebuffer;
	if (framebuffer == nullptr || fragments.isEmpty()) {
		return;
	}
	auto* const pbuffer = context.framebuffer->getPixelBuffer();
	auto* const zbuffer = context.framebuffer->getDepthBuffer();
	auto* const sbuffer = context.framebuffer->getStencilBuffer();
	for (const auto& f : fragments) {
		const int offset = framebuffer->getOffset(f.x, f.y);
		if (offset >= 0 && fragmentPasses(context, f)) {
			pbuffer[offset] = T::fragmentShader(context.uniforms, f.varying, f);
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
