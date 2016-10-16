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
#include "GraphicsEngine.hh"
#include "Scene.hh"
#include "PointRenderer.hh"
#include "WireframeRenderer.hh"
#include "PolygonRenderer.hh"

using clockwork::GraphicsEngine;


GraphicsEngine::GraphicsEngine() :
framebuffer_(),
lineDrawingAlgorithm_(LineDrawingAlgorithm::Bresenham),
enableDepthTesting_(true) {}


GraphicsEngine::~GraphicsEngine() {}


clockwork::Framebuffer::Resolution
GraphicsEngine::getResolution() const {
	return framebuffer_.getResolution();
}


void
GraphicsEngine::setResolution(const Framebuffer::Resolution resolution) {
	framebuffer_.setResolution(resolution);
}


void
GraphicsEngine::clear() {
	framebuffer_.clear();
}


void
GraphicsEngine::render(const Scene& scene) {
	const auto* const viewer = scene.getViewer();
	if (viewer != nullptr) {
		RenderingContext context;

		const Matrix4& VIEW = viewer->getViewTransform();
		const Matrix4& PROJECTION = viewer->getProjectionTransform();
		const Matrix4& VIEWPROJECTION = viewer->getViewProjectionTransform();

		context.framebuffer = &framebuffer_;
		context.primitiveMode = viewer->getPrimitiveMode();
		context.lineDrawingAlgorithm = lineDrawingAlgorithm_;
		context.enableDepthTesting = enableDepthTesting_;
		context.viewportTransform = ViewportTransform(viewer->getViewport(), framebuffer_);
		context.uniforms.insert("PROJECTION", Uniform::create<const Matrix4>(PROJECTION));
		context.uniforms.insert("VIEW", Uniform::create<const Matrix4>(VIEW));
		context.uniforms.insert("viewpoint", Uniform::create<const Point3>(viewer->getPosition()));
		context.uniforms.insert("VIEWPROJECTION", Uniform::create<const Matrix4>(VIEWPROJECTION));

		const auto draw = getDrawFunction(viewer->getRenderingAlgorithm());

		for (const SceneObject* object : scene.getAllNodes<SceneObject>()) {
			if (object != nullptr && !object->isPruned() && viewer->isObjectVisible(*object)) {
				const auto* appearance = object->getAppearanceProperty();
				if (appearance != nullptr && appearance->hasMesh()) {
					const auto& MODEL = object->getModelTransform();
					const auto& MODELVIEW = VIEW * MODEL;
					const auto& MODELVIEWPROJECTION = VIEWPROJECTION * MODEL;
					const auto& INVERSE_MODEL = Matrix4::inverse(MODEL);
					const auto& NORMAL = Matrix4::transpose(Matrix4::inverse(MODELVIEW));

					context.uniforms.insert("MODEL", Uniform::create<const Matrix4>(MODEL));
					context.uniforms.insert("MODELVIEW", Uniform::create<const Matrix4>(MODELVIEW));
					context.uniforms.insert("MODELVIEWPROJECTION", Uniform::create<const Matrix4>(MODELVIEWPROJECTION));
					context.uniforms.insert("INVERSE_MODEL", Uniform::create<const Matrix4>(INVERSE_MODEL));
					context.uniforms.insert("NORMAL", Uniform::create<const Matrix4>(NORMAL));

					draw(context, *appearance->getMesh());
				}
			}
		}
	}
}


clockwork::Framebuffer&
GraphicsEngine::getFramebuffer() {
	return framebuffer_;
}


clockwork::LineDrawingAlgorithm
GraphicsEngine::getLineDrawingAlgorithm() const {
	return lineDrawingAlgorithm_;
}


void
GraphicsEngine::setLineDrawingAlgorithm(const LineDrawingAlgorithm algorithm) {
	lineDrawingAlgorithm_ = algorithm;
}


bool
GraphicsEngine::isDepthTestingEnabled() const {
	return enableDepthTesting_;
}


void
GraphicsEngine::enableDepthTesting(const bool enable) {
	enableDepthTesting_ = enable;
}


GraphicsEngine::DrawFunction
GraphicsEngine::getDrawFunction(const RenderingAlgorithm algorithm) {
	switch (algorithm) {
		case RenderingAlgorithm::Wireframe: return &WireframeRenderer::draw;
		case RenderingAlgorithm::RandomShading: return &RandomShadingRenderer::draw;
		case RenderingAlgorithm::FlatShading: return &FlatShadingRenderer::draw;
		case RenderingAlgorithm::GouraudShading: return &GouraudShadingRenderer::draw;
		case RenderingAlgorithm::PhongShading: return &PhongShadingRenderer::draw;
		case RenderingAlgorithm::CelShading: return &CelShadingRenderer::draw;
		case RenderingAlgorithm::DepthMapping: return &DepthMapRenderer::draw;
		case RenderingAlgorithm::NormalMapping: return &NormalMapRenderer::draw;
		case RenderingAlgorithm::BumpMapping: return &BumpMapRenderer::draw;
		case RenderingAlgorithm::TextureMapping: return &TextureMapRenderer::draw;
		case RenderingAlgorithm::Point: default: return &PointRenderer::draw;
	}
}
