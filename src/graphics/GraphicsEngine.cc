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
#include "GraphicsEngine.hh"
#include "Scene.hh"
#include "PointRenderer.hh"
#include "WireframeRenderer.hh"

using clockwork::GraphicsEngine;


GraphicsEngine::GraphicsEngine() :
framebuffer_() {}


GraphicsEngine::~GraphicsEngine() {}


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
		context.viewport = &viewer->getViewport();
		context.uniforms.insert("PROJECTION", Uniform::create<const Matrix4>(PROJECTION));
		context.uniforms.insert("VIEW", Uniform::create<const Matrix4>(VIEW));
		context.uniforms.insert("viewpoint", Uniform::create<const Point3>(viewer->getPosition()));
		context.uniforms.insert("VIEWPROJECTION", Uniform::create<const Matrix4>(VIEWPROJECTION));

		std::function<void(RenderingContext&, const Mesh&)> draw = PointRenderer::draw;
		switch (viewer->getRenderingAlgorithm()) {
			case RenderingAlgorithm::Wireframe:
				draw = WireframeRenderer::draw;
				break;
			case RenderingAlgorithm::Random:
				//draw = &RandomShadingRenderer::draw;
				break;
			case RenderingAlgorithm::Depth:
				//draw = &DepthMapRenderer::draw;
				break;
			case RenderingAlgorithm::Normals:
				//draw = &NormalMapRenderer::draw;
				break;
			case RenderingAlgorithm::Texture:
				//draw = &TextureMapRenderer::draw;
				break;
			case RenderingAlgorithm::Constant:
				//draw = &ConstantShadingRenderer::draw;
				break;
			case RenderingAlgorithm::Phong:
				//draw = &PhongShadingRenderer::draw;
				break;
			case RenderingAlgorithm::Cel:
				//draw = &CelShadingRenderer::draw;
				break;
			case RenderingAlgorithm::Bump:
				//draw = &BumpMapRenderer::draw;
				break;
			case RenderingAlgorithm::Deferred:
				//draw = &DeferredRenderer::draw;
				break;
			default:
				break;
		}
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
