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
#include "ApplicationSettings.hh"
#include "Scene.hh"
#include "PointRenderer.hh"
#include "WireframeRenderer.hh"
#include "PolygonRenderer.hh"

using clockwork::GraphicsEngine;


clockwork::Error
GraphicsEngine::initialize(const ApplicationSettings& settings) {
	renderingContext_.lineDrawingAlgorithm = LineDrawingAlgorithm::Bresenham;
	renderingContext_.primitiveTopology = enum_traits<PrimitiveTopology>::enumerator(settings.getPrimitiveTopology());
	renderingContext_.enableClipping = settings.isClippingEnabled();
	renderingContext_.enableBackfaceCulling = settings.isBackfaceCullingEnabled();
	renderingContext_.enableScissorTest = settings.isScissorTestEnabled();
	renderingContext_.enableStencilTest = settings.isStencilTestEnabled();
	renderingContext_.enableDepthTest = settings.isDepthTestEnabled();
	renderingContext_.polygonMode = PolygonMode::Point;
	renderingContext_.shadeModel = ShadeModel::Flat;
	renderingContext_.framebuffer.setResolution(Framebuffer::Resolution::XGA);

	connect(&settings, &ApplicationSettings::primitiveTopologyChanged, this, &GraphicsEngine::setPrimitiveTopology);
	connect(&settings, &ApplicationSettings::clippingToggled, this, &GraphicsEngine::enableClipping);
	connect(&settings, &ApplicationSettings::backfaceCullingToggled, this, &GraphicsEngine::enableBackfaceCulling);
	connect(&settings, &ApplicationSettings::scissorTestChanged, this, &GraphicsEngine::enableScissorTest);
	connect(&settings, &ApplicationSettings::stencilTestChanged, this, &GraphicsEngine::enableStencilTest);
	connect(&settings, &ApplicationSettings::depthTestChanged, this, &GraphicsEngine::enableDepthTest);

	return Error::None;
}


clockwork::Framebuffer::Resolution
GraphicsEngine::getFramebufferResolution() const {
	return renderingContext_.framebuffer.getResolution();
}


void
GraphicsEngine::setFramebufferResolution(const Framebuffer::Resolution resolution) {
	renderingContext_.framebuffer.setResolution(resolution);
}


void
GraphicsEngine::clear() {
	renderingContext_.framebuffer.clear();
}


void
GraphicsEngine::render(const Scene& scene) {
	const auto* const viewer = scene.getViewer();
	if (viewer != nullptr) {
		const QMatrix4x4& VIEW = viewer->getViewTransform();
		const QMatrix4x4& PROJECTION = viewer->getProjectionTransform();
		const QMatrix4x4& VIEWPROJECTION = viewer->getViewProjectionTransform();

		renderingContext_.viewportTransform = viewer->getViewportTransform();

		renderingContext_.uniforms.insert("PROJECTION", Uniform::create<const QMatrix4x4>(PROJECTION));
		renderingContext_.uniforms.insert("VIEW", Uniform::create<const QMatrix4x4>(VIEW));
		renderingContext_.uniforms.insert("viewpoint", Uniform::create<const QVector3D>(viewer->getPosition()));
		renderingContext_.uniforms.insert("VIEWPROJECTION", Uniform::create<const QMatrix4x4>(VIEWPROJECTION));

		const auto draw = getDrawFunction(viewer->getRenderingAlgorithm());

		for (const SceneObject* object : scene.getNodes<SceneObject>()) {
			if (object != nullptr && !object->isPruned() && viewer->isObjectVisible(*object)) {
				const auto* appearance = object->getAppearance();
				if (appearance != nullptr && appearance->hasMesh()) {
					const auto& MODEL = object->getModelTransform();
					const auto& MODELVIEW = VIEW * MODEL;
					const auto& MODELVIEWPROJECTION = VIEWPROJECTION * MODEL;
					const auto& INVERSE_MODEL = MODEL.inverted();
					const auto& NORMAL = MODELVIEW.inverted().transposed();

					renderingContext_.uniforms.insert("MODEL", Uniform::create<const QMatrix4x4>(MODEL));
					renderingContext_.uniforms.insert("MODELVIEW", Uniform::create<const QMatrix4x4>(MODELVIEW));
					renderingContext_.uniforms.insert("MODELVIEWPROJECTION", Uniform::create<const QMatrix4x4>(MODELVIEWPROJECTION));
					renderingContext_.uniforms.insert("INVERSE_MODEL", Uniform::create<const QMatrix4x4>(INVERSE_MODEL));
					renderingContext_.uniforms.insert("NORMAL", Uniform::create<const QMatrix4x4>(NORMAL));

					draw(renderingContext_, *appearance->getMesh());
				}
			}
		}
	}
}


clockwork::Framebuffer&
GraphicsEngine::getFramebuffer() {
	return renderingContext_.framebuffer;
}


clockwork::PrimitiveTopology
GraphicsEngine::getPrimitiveTopology() const {
	return renderingContext_.primitiveTopology;
}


void
GraphicsEngine::setPrimitiveTopology(const clockwork::PrimitiveTopology topology) {
	renderingContext_.primitiveTopology = topology;
}


bool
GraphicsEngine::isClippingEnabled() const {
	return renderingContext_.enableClipping;
}


void
GraphicsEngine::enableClipping(const bool enable) {
	renderingContext_.enableClipping = enable;
}


bool
GraphicsEngine::isBackfaceCullingEnabled() const {
	return renderingContext_.enableBackfaceCulling;
}


void
GraphicsEngine::enableBackfaceCulling(const bool enable) {
	renderingContext_.enableBackfaceCulling = enable;
}


clockwork::LineDrawingAlgorithm
GraphicsEngine::getLineDrawingAlgorithm() const {
	return renderingContext_.lineDrawingAlgorithm;
}


void
GraphicsEngine::setLineDrawingAlgorithm(const LineDrawingAlgorithm algorithm) {
	renderingContext_.lineDrawingAlgorithm = algorithm;
}


bool
GraphicsEngine::isScissorTestEnabled() const {
	return renderingContext_.enableScissorTest;
}


void
GraphicsEngine::enableScissorTest(const bool enable) {
	renderingContext_.enableScissorTest = enable;
}


bool
GraphicsEngine::isStencilTestEnabled() const {
	return renderingContext_.enableStencilTest;
}


void
GraphicsEngine::enableStencilTest(const bool enable) {
	renderingContext_.enableStencilTest = enable;
}


bool
GraphicsEngine::isDepthTestEnabled() const {
	return renderingContext_.enableDepthTest;
}


void
GraphicsEngine::enableDepthTest(const bool enable) {
	renderingContext_.enableDepthTest = enable;
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
