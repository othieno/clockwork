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
#include "RandomColoredSurfacesShaderProgram.hh"
#include "NormalMapsShaderProgram.hh"

using clockwork::GraphicsSubsystem;


clockwork::Error
GraphicsSubsystem::initialize(const ApplicationSettings& settings) {
	renderingContext_.shaderProgramIdentifier = settings.getShaderProgramIdentifier();
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
	renderingContext_.normalizedScissorBox.setRect(0.0, 0.0, 1.0, 1.0);
	renderingContext_.scissorBox.setRect(0, 0, renderingContext_.framebuffer.getWidth(), renderingContext_.framebuffer.getHeight());

	connect(this, &GraphicsSubsystem::shaderProgramChanged,        this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::primitiveTopologyChanged,    this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::clippingToggled,             this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::backfaceCullingToggled,      this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::polygonModeChanged,          this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::shadeModelChanged,           this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::lineAntiAliasingToggled,     this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::scissorTestToggled,          this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::stencilTestToggled,          this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::depthTestToggled,            this, &GraphicsSubsystem::renderingContextChanged);
	connect(this, &GraphicsSubsystem::normalizedScissorBoxChanged, this, &GraphicsSubsystem::renderingContextChanged);

	return Error::None;
}


const QSize&
GraphicsSubsystem::getFramebufferResolution() const {
	return renderingContext_.framebuffer.getResolution();
}


void
GraphicsSubsystem::setFramebufferResolution(const Framebuffer::Resolution resolutionIdentifier) {
	if (renderingContext_.framebuffer.getResolutionIdentifier() != resolutionIdentifier) {
		renderingContext_.framebuffer.setResolution(resolutionIdentifier);
		updateScissorBox();
	}
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


bool
GraphicsSubsystem::isFpsCounterEnabled() const {
	return false;
}


void
GraphicsSubsystem::enableFpsCounter(const bool enable) {
	Q_UNUSED(enable);
}


clockwork::ShaderProgramIdentifier
GraphicsSubsystem::getShaderProgramIdentifier() const {
	return renderingContext_.shaderProgramIdentifier;
}


void
GraphicsSubsystem::setShaderProgram(const ShaderProgramIdentifier identifier) {
	if (renderingContext_.shaderProgramIdentifier != identifier) {
		renderingContext_.shaderProgramIdentifier = identifier;
		emit shaderProgramChanged(identifier);
		emit shaderProgramChanged_(enum_traits<ShaderProgramIdentifier>::ordinal(identifier));
	}
}


clockwork::PrimitiveTopology
GraphicsSubsystem::getPrimitiveTopology() const {
	return renderingContext_.primitiveTopology;
}


void
GraphicsSubsystem::setPrimitiveTopology(const PrimitiveTopology topology) {
	if (renderingContext_.primitiveTopology != topology) {
		renderingContext_.primitiveTopology = topology;
		emit primitiveTopologyChanged(topology);
		emit primitiveTopologyChanged_(enum_traits<PrimitiveTopology>::ordinal(topology));
	}
}


bool
GraphicsSubsystem::isClippingEnabled() const {
	return renderingContext_.enableClipping;
}


void
GraphicsSubsystem::enableClipping(const bool enable) {
	if (renderingContext_.enableClipping != enable) {
		renderingContext_.enableClipping = enable;
		emit clippingToggled(enable);
	}
}


bool
GraphicsSubsystem::isBackfaceCullingEnabled() const {
	return renderingContext_.enableBackfaceCulling;
}


void
GraphicsSubsystem::enableBackfaceCulling(const bool enable) {
	if (renderingContext_.enableBackfaceCulling != enable) {
		renderingContext_.enableBackfaceCulling = enable;
		emit backfaceCullingToggled(enable);
	}
}


clockwork::PolygonMode
GraphicsSubsystem::getPolygonMode() const {
	return renderingContext_.polygonMode;
}


void
GraphicsSubsystem::setPolygonMode(const PolygonMode mode) {
	if (renderingContext_.polygonMode != mode) {
		renderingContext_.polygonMode = mode;
		emit polygonModeChanged(mode);
		emit polygonModeChanged_(enum_traits<PolygonMode>::ordinal(mode));
	}
}


clockwork::ShadeModel
GraphicsSubsystem::getShadeModel() const {
	return renderingContext_.shadeModel;
}


void
GraphicsSubsystem::setShadeModel(const ShadeModel model) {
	if (renderingContext_.shadeModel != model) {
		renderingContext_.shadeModel = model;
		emit shadeModelChanged(model);
		emit shadeModelChanged_(enum_traits<ShadeModel>::ordinal(model));
	}
}


bool
GraphicsSubsystem::isLineAntiAliasingEnabled() const {
	return renderingContext_.enableLineAntiAliasing;
}


void
GraphicsSubsystem::enableLineAntiAliasing(const bool enable) {
	if (renderingContext_.enableLineAntiAliasing != enable) {
		renderingContext_.enableLineAntiAliasing = enable;
		emit lineAntiAliasingToggled(enable);
	}
}


bool
GraphicsSubsystem::isScissorTestEnabled() const {
	return renderingContext_.enableScissorTest;
}


void
GraphicsSubsystem::enableScissorTest(const bool enable) {
	if (renderingContext_.enableScissorTest != enable) {
		renderingContext_.enableScissorTest = enable;
		emit scissorTestToggled(enable);
	}
}


bool
GraphicsSubsystem::isStencilTestEnabled() const {
	return renderingContext_.enableStencilTest;
}


void
GraphicsSubsystem::enableStencilTest(const bool enable) {
	if (renderingContext_.enableStencilTest != enable) {
		renderingContext_.enableStencilTest = enable;
		emit stencilTestToggled(enable);
	}
}


bool
GraphicsSubsystem::isDepthTestEnabled() const {
	return renderingContext_.enableDepthTest;
}


void
GraphicsSubsystem::enableDepthTest(const bool enable) {
	if (renderingContext_.enableDepthTest != enable) {
		renderingContext_.enableDepthTest = enable;
		emit depthTestToggled(enable);
	}
}


const QRectF&
GraphicsSubsystem::getNormalizedScissorBox() const {
	return renderingContext_.normalizedScissorBox;
}


void
GraphicsSubsystem::setNormalizedScissorBox(const QRectF& normalizedScissorBox) {
	if (renderingContext_.normalizedScissorBox != normalizedScissorBox) {
		renderingContext_.normalizedScissorBox = normalizedScissorBox;
		updateScissorBox();
		emit normalizedScissorBoxChanged(normalizedScissorBox);
	}
}


void
(*GraphicsSubsystem::getDrawCommand())(const RenderingContext&, const Mesh&, Framebuffer&) {
	using Identifier = ShaderProgramIdentifier;
	switch (renderingContext_.shaderProgramIdentifier) {
		case Identifier::Minimal:
			return &Renderer<Identifier::Minimal>::draw;
		case Identifier::RandomColoredSurfaces:
			return &Renderer<Identifier::RandomColoredSurfaces>::draw;
		case Identifier::DepthMaps:
			return &Renderer<Identifier::DepthMaps>::draw;
		case Identifier::NormalMaps:
			return &Renderer<Identifier::NormalMaps>::draw;
		case Identifier::BumpMaps:
			return &Renderer<Identifier::BumpMaps>::draw;
		case Identifier::TextureMaps:
			return &Renderer<Identifier::TextureMaps>::draw;
		default:
			qFatal("[GraphicsSubsystem::getDrawCommand] Undefined draw command!");
	}
}


void
GraphicsSubsystem::updateScissorBox() {
	const int w = renderingContext_.framebuffer.getWidth();
	const int h = renderingContext_.framebuffer.getHeight();

	const int t = qRound(h * renderingContext_.normalizedScissorBox.top());
	const int b = qRound(h * renderingContext_.normalizedScissorBox.bottom());
	const int l = qRound(w * renderingContext_.normalizedScissorBox.left());
	const int r = qRound(w * renderingContext_.normalizedScissorBox.right());

	renderingContext_.scissorBox.setRect(l, t, r - l, b - t);
}
