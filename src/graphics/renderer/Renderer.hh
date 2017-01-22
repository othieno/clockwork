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

#include "ShaderProgram.hh"


namespace clockwork {
/**
 * @see Framebuffer.hh.
 */
class Framebuffer;
/**
 * @see RenderingContext.hh.
 */
struct RenderingContext;
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
	static void fragmentProcessing(const RenderingContext&, const Fragment&, Framebuffer&);
private:
	/**
	 *
	 */
	static VertexArray vertexProcessing(const RenderingContext& context, const Mesh::Face& face);
	/**
	 *
	 */
	static void vertexPostProcessing(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void primitiveAssembly(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void rasterization(RenderingContext& context, VertexArray& vertices);
	/**
	 * Rremoves point primitves that are not in the view volume.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to clip.
	 */
	static void clipPointPrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Rremoves line primitves that are not in the view volume.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to clip.
	 */
	static void clipLinePrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Rremoves triangle primitves that are not in the view volume.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to clip.
	 */
	static void clipTrianglePrimitives(const RenderingContext& context, VertexArray& vertices);
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
	static bool isBackFacePrimitive(
		const RenderingContext& context,
		const typename VertexArray::iterator& offset
	);
	/**
	 * Converts a set of point primitives into fragments that are then written to a framebuffer.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to draw.
	 * @param framebuffer the framebuffer that the primitives will be drawn to.
	 */
	static void rasterizePointPrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Converts a set of line primitives into fragments that are then written to a framebuffer.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to draw.
	 * @param framebuffer the framebuffer that the primitives will be drawn to.
	 */
	static void rasterizeLinePrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Converts a set of triangle primitives into fragments that are then written to a framebuffer.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to draw.
	 * @param framebuffer the framebuffer that the primitives will be drawn to.
	 */
	static void rasterizeTrianglePrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
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
} // namespace clockwork

#include "Renderer.inl"

#endif // CLOCKWORK_RENDERER_HH
