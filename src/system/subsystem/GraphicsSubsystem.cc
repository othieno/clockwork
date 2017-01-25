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
#include "GraphicsSubsystem.hh"
#include "ApplicationSettings.hh"
#include "Scene.hh"

using clockwork::GraphicsSubsystem;


clockwork::Error
GraphicsSubsystem::initialize(const ApplicationSettings& settings) {
	renderingContext_.shaderProgramIdentifier = settings.getShaderProgram();
	renderingContext_.primitiveTopology = settings.getPrimitiveTopology();
	renderingContext_.enableClipping = settings.isClippingEnabled();
	renderingContext_.enableBackfaceCulling = settings.isBackfaceCullingEnabled();
	renderingContext_.polygonMode = settings.getPolygonMode();
	renderingContext_.shadeModel = settings.getShadeModel();
	renderingContext_.enableLineAntiAliasing = settings.isLineAntiAliasingEnabled();
	renderingContext_.enableScissorTest = settings.isScissorTestEnabled();
	renderingContext_.enableStencilTest = settings.isStencilTestEnabled();
	renderingContext_.enableDepthTest = settings.isDepthTestEnabled();
	renderingContext_.framebuffer.setResolution(Framebuffer::Resolution::XGA);

	connect(&settings, &ApplicationSettings::shaderProgramChanged, this, &GraphicsSubsystem::setShaderProgram);
	connect(&settings, &ApplicationSettings::primitiveTopologyChanged, this, &GraphicsSubsystem::setPrimitiveTopology);
	connect(&settings, &ApplicationSettings::clippingToggled, this, &GraphicsSubsystem::enableClipping);
	connect(&settings, &ApplicationSettings::backfaceCullingToggled, this, &GraphicsSubsystem::enableBackfaceCulling);
	connect(&settings, &ApplicationSettings::polygonModeChanged, this, &GraphicsSubsystem::setPolygonMode);
	connect(&settings, &ApplicationSettings::shadeModelChanged, this, &GraphicsSubsystem::setShadeModel);
	connect(&settings, &ApplicationSettings::lineAntiAliasingToggled, this, &GraphicsSubsystem::enableLineAntiAliasing);
	connect(&settings, &ApplicationSettings::scissorTestChanged, this, &GraphicsSubsystem::enableScissorTest);
	connect(&settings, &ApplicationSettings::stencilTestChanged, this, &GraphicsSubsystem::enableStencilTest);
	connect(&settings, &ApplicationSettings::depthTestChanged, this, &GraphicsSubsystem::enableDepthTest);

	return Error::None;
}


clockwork::Framebuffer::Resolution
GraphicsSubsystem::getFramebufferResolution() const {
	return renderingContext_.framebuffer.getResolution();
}


void
GraphicsSubsystem::setFramebufferResolution(const Framebuffer::Resolution resolution) {
	renderingContext_.framebuffer.setResolution(resolution);
}


void
GraphicsSubsystem::clear() {
	renderingContext_.framebuffer.clear();
}


void
GraphicsSubsystem::render(const Scene& scene) {
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

		const auto draw = getDrawCommand();

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

					draw(renderingContext_, *appearance->getMesh(), renderingContext_.framebuffer);
				}
			}
		}
	}
}


clockwork::Framebuffer&
GraphicsSubsystem::getFramebuffer() {
	return renderingContext_.framebuffer;
}


clockwork::ShaderProgramIdentifier
GraphicsSubsystem::getShaderProgramIdentifier() const {
	return renderingContext_.shaderProgramIdentifier;
}


void
GraphicsSubsystem::setShaderProgram(const ShaderProgramIdentifier identifier) {
	renderingContext_.shaderProgramIdentifier = identifier;
}


clockwork::PrimitiveTopology
GraphicsSubsystem::getPrimitiveTopology() const {
	return renderingContext_.primitiveTopology;
}


void
GraphicsSubsystem::setPrimitiveTopology(const clockwork::PrimitiveTopology topology) {
	renderingContext_.primitiveTopology = topology;
}


bool
GraphicsSubsystem::isClippingEnabled() const {
	return renderingContext_.enableClipping;
}


void
GraphicsSubsystem::enableClipping(const bool enable) {
	renderingContext_.enableClipping = enable;
}


bool
GraphicsSubsystem::isBackfaceCullingEnabled() const {
	return renderingContext_.enableBackfaceCulling;
}


void
GraphicsSubsystem::enableBackfaceCulling(const bool enable) {
	renderingContext_.enableBackfaceCulling = enable;
}


clockwork::PolygonMode
GraphicsSubsystem::getPolygonMode() const {
	return renderingContext_.polygonMode;
}


void
GraphicsSubsystem::setPolygonMode(const PolygonMode mode) {
	renderingContext_.polygonMode = mode;
}


clockwork::ShadeModel
GraphicsSubsystem::getShadeModel() const {
	return renderingContext_.shadeModel;
}


void
GraphicsSubsystem::setShadeModel(const ShadeModel model) {
	renderingContext_.shadeModel = model;
}


bool
GraphicsSubsystem::isLineAntiAliasingEnabled() const {
	return renderingContext_.enableLineAntiAliasing;
}


void
GraphicsSubsystem::enableLineAntiAliasing(const bool enable) {
	renderingContext_.enableLineAntiAliasing = enable;
}


bool
GraphicsSubsystem::isScissorTestEnabled() const {
	return renderingContext_.enableScissorTest;
}


void
GraphicsSubsystem::enableScissorTest(const bool enable) {
	renderingContext_.enableScissorTest = enable;
}


bool
GraphicsSubsystem::isStencilTestEnabled() const {
	return renderingContext_.enableStencilTest;
}


void
GraphicsSubsystem::enableStencilTest(const bool enable) {
	renderingContext_.enableStencilTest = enable;
}


bool
GraphicsSubsystem::isDepthTestEnabled() const {
	return renderingContext_.enableDepthTest;
}


void
GraphicsSubsystem::enableDepthTest(const bool enable) {
	renderingContext_.enableDepthTest = enable;
}


void
(*GraphicsSubsystem::getDrawCommand())(const RenderingContext&, const Mesh&, Framebuffer&) {
	using Identifier = ShaderProgramIdentifier;
	switch (renderingContext_.shaderProgramIdentifier) {
		case Identifier::Minimal:
			return &Renderer<Identifier::Minimal>::draw;
		default:
			qFatal("[GraphicsSubsystem::getDrawCommand] Undefined draw command!");
	}
}
