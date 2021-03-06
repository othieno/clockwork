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

#include "BaseRenderer.hh"
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
template<ShaderProgramIdentifier identifier>
class Renderer : public BaseRenderer {
public:
	/**
	 *
	 */
	using ShaderProgram = detail::ShaderProgram<identifier>;
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
	 * Renders the specified mesh in the given context to the the specified framebuffer.
	 * @param context the rendering context.
	 * @param mesh the polygon mesh to render.
	 * @param framebuffer the framebuffer where the mesh is rendered to.
	 */
	static void draw(const RenderingContext& context, const Mesh& mesh, Framebuffer& framebuffer);
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
	 * Rearranges the specified set of vertices into a collection of geometric primitives.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to rearrange.
	 */
	static void primitiveAssembly(const RenderingContext& context, VertexArray& vertices);
	/**
	 *
	 */
	static void rasterization(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Removes point primitves that are not in the view volume.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to clip.
	 */
	static void clipPointPrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Removes line primitves that are not in the view volume.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to clip.
	 */
	static void clipLinePrimitives(const RenderingContext& context, VertexArray& vertices);
	/**
	 * Removes triangle primitves that are not in the view volume.
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
	 * @param vertices the set of vertices to convert into fragments.
	 * @param framebuffer the framebuffer where fragments be drawn to.
	 */
	static void rasterizePointPrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Converts a set of line primitives into fragments that are then written to a framebuffer.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to convert into fragments.
	 * @param framebuffer the framebuffer where fragments be drawn to.
	 */
	static void rasterizeLinePrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Converts a set of triangle primitives into fragments that are then written to a framebuffer.
	 * @param context the rendering context.
	 * @param vertices the set of vertices to convert into fragments.
	 * @param framebuffer the framebuffer where fragments be drawn to.
	 */
	static void rasterizeTrianglePrimitives(
		const RenderingContext& context,
		VertexArray& vertices,
		Framebuffer& framebuffer
	);
	/**
	 * Draws a line from one fragment to another.
	 * Note that this approach will use the Bresenham algorithm.
	 * @param context the rendering context.
	 * @param from the fragment containing the position from which the line begins.
	 * @param to the fragment containing the position at which the line ends.
	 */
	static void drawLine(
		const RenderingContext& context,
		const Fragment& from,
		const Fragment& to,
		Framebuffer& framebuffer
	);
	/**
	 * Draws a smooth line from one fragment to another.
	 * Note that this approach will use the Xiaolin-Wu algorithm.
	 * @param context the rendering context.
	 * @param from the fragment containing the position from which the line begins.
	 * @param to the fragment containing the position at which the line ends.
	 */
	static void drawSmoothLine(
		const RenderingContext& context,
		const Fragment& from,
		const Fragment& to,
		Framebuffer& framebuffer
	);
	/**
	 *
	 */
	static void fragmentProcessing(const RenderingContext&, const Fragment&, Framebuffer&);
};
} // namespace clockwork

#include "Renderer.inl"

#endif // CLOCKWORK_RENDERER_HH
