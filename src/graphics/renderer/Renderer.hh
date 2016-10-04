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

#include "WeakVariant.hh"
#include "Primitive.hh"
#include "Point.hh"
#include "Point3.hh"
#include "Point4.hh"
#include "Vector3.hh"
#include "Vector4.hh"
#include "Matrix4.hh"
#include "ColorARGB.hh"
#include <QHash>


namespace clockwork {
/**
 * @see graphics/Framebuffer.hh.
 */
class Framebuffer;
/**
 * @see graphics/Mesh.hh.
 */
class Mesh;
/**
 * @see graphics/Viewport.hh.
 */
struct Viewport;
/**
 *
 */
class Renderer {
public:
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
	using Uniform = WeakVariant<UniformValidator>;
	/**
	 * Checks whether T is a valid Varying value type. Varying attributes are
	 * restricted to arithmetic types, as well as Point, Point3, Point4,
	 * Vector3, Vector4, Matrix4 or ColorARGB.
	 */
	template<class T>
	struct VaryingValidator :
	std::integral_constant<bool,
		std::is_arithmetic<T>::value ||
		std::is_base_of<Point, T>::value ||
		std::is_base_of<Point3, T>::value ||
		std::is_base_of<Point4, T>::value ||
		std::is_base_of<Vector3, T>::value ||
		std::is_base_of<math::Vector4i, T>::value ||
		std::is_base_of<math::Vector4u, T>::value ||
		std::is_base_of<math::Vector4f, T>::value ||
		std::is_base_of<math::Vector4d, T>::value ||
		std::is_base_of<Matrix4, T>::value ||
		std::is_base_of<ColorARGB, T>::value> {};
	/**
	 *
	 */
	using Varying = WeakVariant<VaryingValidator>;
	/**
	 *
	 */
	struct PipelineContext {
		/**
		 * The framebuffer.
		 */
		Framebuffer* framebuffer;
		/**
		 * The primitive mode.
		 */
		Primitive primitiveMode;
		/**
		 * The viewport.
		 */
		const Viewport* viewport;
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
