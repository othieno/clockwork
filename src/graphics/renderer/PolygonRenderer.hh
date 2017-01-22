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
#ifndef CLOCKWORK_POLYGON_RENDERER_HH
#define CLOCKWORK_POLYGON_RENDERER_HH

#include "Renderer.hh"
#include "RandomShadingShaderProgram.hh"
#include "FlatShadingShaderProgram.hh"
#include "GouraudShadingShaderProgram.hh"
#include "PhongShadingShaderProgram.hh"
#include "CelShadingShaderProgram.hh"
#include "DepthMapShaderProgram.hh"
#include "NormalMapShaderProgram.hh"
#include "BumpMapShaderProgram.hh"
#include "TextureMapShaderProgram.hh"


namespace clockwork {
/**
 *
 */
template<RenderingAlgorithm algorithm, class Implementation>
class PolygonRenderer : public Renderer<algorithm, Implementation> {
public:
	using Fragment = typename Renderer<algorithm, Implementation>::Fragment;
	using Varying = typename Renderer<algorithm, Implementation>::Varying;
	using Vertex = typename Renderer<algorithm, Implementation>::Vertex;
	using VertexArray = typename Renderer<algorithm, Implementation>::VertexArray;
	/**
	 * Removes vertices that are not visible on the screen.
	 */
	static void clip(const RenderingContext&, VertexArray&);
};
/**
 *
 */
class RandomShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::RandomShading, RandomShadingRenderer> {};
/**
 *
 */
class FlatShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::FlatShading, FlatShadingRenderer> {};
/**
 *
 */
class GouraudShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::GouraudShading, GouraudShadingRenderer> {};
/**
 *
 */
class PhongShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::PhongShading, PhongShadingRenderer> {};
/**
 *
 */
class CelShadingRenderer :
public PolygonRenderer<RenderingAlgorithm::CelShading, CelShadingRenderer> {};
/**
 *
 */
class DepthMapRenderer :
public PolygonRenderer<RenderingAlgorithm::DepthMapping, DepthMapRenderer> {};
/**
 *
 */
class NormalMapRenderer :
public PolygonRenderer<RenderingAlgorithm::NormalMapping, NormalMapRenderer> {};
/**
 *
 */
class BumpMapRenderer :
public PolygonRenderer<RenderingAlgorithm::BumpMapping, BumpMapRenderer> {};
/**
 *
 */
class TextureMapRenderer :
public PolygonRenderer<RenderingAlgorithm::TextureMapping, TextureMapRenderer> {};


template<RenderingAlgorithm A, class T> void
PolygonRenderer<A, T>::clip(const RenderingContext&, VertexArray&) {}
} // namespace clockwork

#endif // CLOCKWORK_POLYGON_RENDERER_HH
