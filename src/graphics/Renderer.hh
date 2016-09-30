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

#include "ReferenceVariant.hh"
#include <QHash>


namespace clockwork {
/**
 * @see graphics/Mesh.hh.
 */
class Mesh;
/**
 *
 */
class Renderer {
public:
	/**
	 * An enumeration of available line-drawing algorithms.
	 */
	enum class LineDrawingAlgorithm {
		Bresenham,
		XiaolinWu
	};
	/**
	 * An enumeration of available primitives.
	 */
	enum class Primitive {
		Point,
		Line,
		LineStrip,
		LineLoop,
		Triangle,
		TriangleStrip,
		TriangleFan
	};
	/**
	 * An enumeration of available rendering algorithms.
	 */
	enum class RenderingAlgorithm {
		Point,
		Wireframe,
		Random,
		Depth,
		Normals,
		Texture,
		Constant,
		Phong,
		Cel,
		Bump,
		Deferred
	};
	/**
	 * Checks whether T is a valid Uniform value type.
	 */
	template<class T>
	struct UniformValidator :
	std::integral_constant<bool, true> {};
	/**
	 *
	 */
	using Uniform = ReferenceVariant<UniformValidator>;
	/**
	 * Checks whether T is a valid Varying value type.
	 */
	template<class T>
	struct VaryingValidator :
	std::integral_constant<bool, true> {};
	/**
	 *
	 */
	using Varying = ReferenceVariant<VaryingValidator>;
	/**
	 *
	 */
	struct PipelineContext {
		/**
		 * The primitive mode.
		 */
		Primitive primitiveMode;
		/**
		 * The set of uniform variables.
		 */
		QHash<QString, Uniform> uniform;
		/**
		 * The set of varying variables.
		 */
		QHash<QString, Varying> varying;
	};
	/**
	 * Renders the specified mesh in the given state.
	 * @param context the rendering pipeline context.
	 * @param mesh the polygon mesh to render.
	 */
	static void draw(PipelineContext& context, const Mesh& mesh);
};
} // namespace clockwork

#endif // CLOCKWORK_RENDERER_HH
