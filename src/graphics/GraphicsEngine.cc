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
		Renderer::PipelineContext context;

		const Matrix4& VIEW = viewer->getViewTransform();
		const Matrix4& PROJECTION = viewer->getProjectionTransform();
		const Matrix4& VIEWPROJECTION = viewer->getViewProjectionTransform();

		context.framebuffer = &framebuffer_;
		context.lineDrawingAlgorithm = viewer->getLineDrawingAlgorithm();
		context.primitiveMode = viewer->getPrimitiveMode();
		context.viewport = &viewer->getViewport();
		context.uniform.insert("PROJECTION", Renderer::Uniform::create<const Matrix4>(PROJECTION));
		context.uniform.insert("VIEW", Renderer::Uniform::create<const Matrix4>(VIEW));
		context.uniform.insert("viewpoint", Renderer::Uniform::create<const Point3>(viewer->getPosition()));
		context.uniform.insert("VIEWPROJECTION", Renderer::Uniform::create<const Matrix4>(VIEWPROJECTION));

		for (const SceneObject* object : scene.getAllNodes<SceneObject>()) {
			if (object != nullptr && !object->isPruned() && viewer->isObjectVisible(*object)) {
				const auto* appearance = object->getAppearanceProperty();
				if (appearance != nullptr && appearance->hasMesh()) {
					const auto& MODEL = object->getModelTransform();
					const auto& MODELVIEW = VIEW * MODEL;
					const auto& MODELVIEWPROJECTION = VIEWPROJECTION * MODEL;
					const auto& INVERSE_MODEL = Matrix4::inverse(MODEL);
					const auto& NORMAL = Matrix4::transpose(Matrix4::inverse(MODELVIEW));

					context.uniform.insert("MODEL", Renderer::Uniform::create<const Matrix4>(MODEL));
					context.uniform.insert("MODELVIEW", Renderer::Uniform::create<const Matrix4>(MODELVIEW));
					context.uniform.insert("MODELVIEWPROJECTION", Renderer::Uniform::create<const Matrix4>(MODELVIEWPROJECTION));
					context.uniform.insert("INVERSE_MODEL", Renderer::Uniform::create<const Matrix4>(INVERSE_MODEL));
					context.uniform.insert("NORMAL", Renderer::Uniform::create<const Matrix4>(NORMAL));

					Renderer::draw(context, *appearance->getMesh());
				}
			}
		}
	}
}


clockwork::Framebuffer&
GraphicsEngine::getFramebuffer() {
	return framebuffer_;
}
