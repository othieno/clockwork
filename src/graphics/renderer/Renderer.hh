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
#include "Fragment.hh"
#include "Framebuffer.hh"
#include "Mesh.hh"
#include "VertexAttributes.hh"
#include "VertexShaderOutput.hh"


namespace clockwork {
/**
 *
 */
template<RenderingAlgorithm algorithm, class Implementation>
class Renderer {
public:
	using Fragment = detail::Fragment<algorithm>;
	using Fragments = QList<Fragment>;
	using Varying = detail::Varying<algorithm>;
	using VertexAttributes = detail::VertexAttributes<algorithm>;
	using VertexShaderOutput = detail::VertexShaderOutput<algorithm>;
	using VertexShaderOutputs = QList<VertexShaderOutput>;
	/**
	 * Renders the specified mesh in the given context.
	 * @param context the rendering context.
	 * @param mesh the polygon mesh to render.
	 */
	static void draw(RenderingContext& context, const Mesh& mesh) {
		auto* const framebuffer = context.framebuffer;
		if (framebuffer == nullptr || mesh.faces.isEmpty()) {
			return;
		}
		auto* const pixelBuffer = framebuffer->getPixelBuffer();
		auto* const depthBuffer = framebuffer->getDepthBuffer();
		auto* const stencilBuffer = framebuffer->getStencilBuffer();

		for (const auto& face : mesh.faces) {
			VertexShaderOutputs vertexShaderOutputs;
			for (std::size_t i = 0; i < face.length; ++i) {
				// Per-vertex operation.
				auto varying = Implementation::createVarying(face, i);
				const auto& attributes = Implementation::createVertexAttributes(face, i);
				auto output = Implementation::vertexShader(context.uniforms, varying, attributes);

				// Attach the varying variables to the vertex shader's output for use by the
				// fragment shader later on.
				output.varying = std::move(varying);

				vertexShaderOutputs.append(output);
			}
			// Primitive assembly.
			auto& primitives = Implementation::assemble(context.primitiveMode, vertexShaderOutputs);

			Implementation::clip(vertexShaderOutputs);

			for (auto& primitive : primitives) {
				// Perspective divide: Convert primitive positions from clipping
				// coordinate space to normalized device coordinate (NDC) space.
				auto& position = primitive.position;
				position.x /= position.w;
				position.y /= position.w;
				position.z /= position.w;
				position.w /= 1.0;

				// Convert the positions from NDC space to window (screen) space.
				position = position * context.viewportTransform;
			}

			// Rasterization.
			for (const auto& fragment : Implementation::rasterize(context, primitives)) {
				const int offset = context.framebuffer->getOffset(fragment.x, fragment.y);
				if (offset >= 0 && fragmentPasses(context, fragment)) {
					pixelBuffer[offset] = Implementation::fragmentShader(context.uniforms, fragment.varying, fragment);
					depthBuffer[offset] = fragment.z;
					stencilBuffer[offset] = fragment.stencil;
				}
			}
		}
	}
	/**
	 * Returns true if the specified fragment passes all fragment tests, false otherwise.
	 * @param context the rendering context.
	 * @param fragment the fragment to test.
	 */
	static bool fragmentPasses(const RenderingContext&, const Fragment&) {
		return true;
	}
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
	static VertexShaderOutput vertexShader(const Uniforms& uniforms, Varying&, const VertexAttributes& attributes) {
		const auto& MVP = uniforms["MODELVIEWPROJECTION"].as<const Matrix4>();

		VertexShaderOutput output;
		output.position = MVP * Point4(attributes.position);

		return output;
	}
	/**
	 * Returns a list of primitives.
	 * This function should be implemented in an explicit template specialization.
	 */
	static VertexShaderOutputs& assemble(const Primitive, VertexShaderOutputs& outputs) {
		return outputs;
	}
	/**
	 * Removes vertex shader outputs that are not visible on the screen.
	 * This function should be implemented in an explicit template specialization.
	 */
	static void clip(VertexShaderOutputs&) {}
	/**
	 * Returns an empty list of fragments.
	 * This function should be implemented in an explicit template specialization.
	 */
	static Fragments rasterize(const RenderingContext&, const VertexShaderOutputs&) {
		return Fragments();
	}
	/**
	 * Returns a pixel value.
	 * This function should be implemented in an explicit template specialization.
	 */
	static std::uint32_t fragmentShader(const Uniforms&, const Varying&, const Fragment&) {
		return 0xffffffff;
	}
};
} // namespace clockwork

#endif // CLOCKWORK_RENDERER_HH
