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
#include "SceneViewer.hh"

using clockwork::SceneViewer;


SceneViewer::SceneViewer(const QString& name) :
SceneObject(name),
projection_(Projection::Perspective),
updateViewTransform_(true),
updateProjectionTransform_(true),
renderingAlgorithm_(Renderer::RenderingAlgorithm::Point),
lineDrawingAlgorithm_(Renderer::LineDrawingAlgorithm::Bresenham),
primitiveAssemblyMode_(Renderer::PrimitiveAssemblyMode::Triangles),
textureFilterIdentifier_(TextureFilter::Identifier::Bilinear) {}


clockwork::Projection
SceneViewer::getProjection() const {
	return projection_;
}


void
SceneViewer::setProjection(const Projection projection) {
	if (projection_ != projection) {
		projection_ = projection;
		updateProjectionTransform_ = true;
	}
}


const clockwork::Matrix4&
SceneViewer::getViewTransform() {
	if (updateViewTransform_) {
		updateViewTransform_ = false;
		viewTransform_ = calculateViewTransform();
	}
	return viewTransform_;
}


const clockwork::Matrix4&
SceneViewer::getProjectionTransform() {
	if (updateProjectionTransform_) {
		updateProjectionTransform_ = false;
		projectionTransform_ = calculateProjectionTransform();
	}
	return projectionTransform_;
}


const clockwork::Matrix4&
SceneViewer::getViewProjectionTransform() {
	if (updateViewTransform_ || updateProjectionTransform_) {
		const auto& P = getProjectionTransform();
		const auto& V = getViewTransform();
		viewProjectionTransform_ = P * V; // The order is important: PROJECTION * VIEW!
	}
	return viewProjectionTransform_;
}


const clockwork::Viewport&
SceneViewer::getViewport() const {
	return viewport_;
}


void
SceneViewer::setViewport(const Viewport& viewport) {
	viewport_ = viewport;
}


const clockwork::Frustum&
SceneViewer::getViewFrustum() const {
	return viewFrustum_;
}


void
SceneViewer::setViewFrustum(const Frustum& viewFrustum) {
//TODO Implement the comparison operator.
//	if (viewFrustum_ != viewFrustum) {
		viewFrustum_ = viewFrustum;
		updateProjectionTransform_ = true;
//	}
}


clockwork::Renderer::RenderingAlgorithm
SceneViewer::getRenderingAlgorithm() const {
	return renderingAlgorithm_;
}


void
SceneViewer::setRenderingAlgorithm(const Renderer::RenderingAlgorithm algorithm) {
	renderingAlgorithm_ = algorithm;
}


clockwork::Renderer::LineDrawingAlgorithm
SceneViewer::getLineDrawingAlgorithm() const {
	return lineDrawingAlgorithm_;
}


void
SceneViewer::setLineDrawingAlgorithm(const Renderer::LineDrawingAlgorithm algorithm) {
	lineDrawingAlgorithm_ = algorithm;
}


clockwork::Renderer::PrimitiveAssemblyMode
SceneViewer::getPrimitiveAssemblyMode() const {
	return primitiveAssemblyMode_;
}


void
SceneViewer::setPrimitiveAssemblyMode(const Renderer::PrimitiveAssemblyMode mode) {
	primitiveAssemblyMode_ = mode;
}


clockwork::TextureFilter::Identifier
SceneViewer::getTextureFilter() const {
	return textureFilterIdentifier_;
}


void
SceneViewer::setTextureFilter(const clockwork::TextureFilter::Identifier id) {
	textureFilterIdentifier_ = id;
}


const QList<clockwork::ImageFilter::Identifier>&
SceneViewer::getImageFilters() const {
	return imageFilterIdentifiers_;
}


void
SceneViewer::addImageFilter(const ImageFilter::Identifier identifier) {
	imageFilterIdentifiers_.append(identifier);
}


void
SceneViewer::removeImageFilter(const ImageFilter::Identifier identifier) {
	imageFilterIdentifiers_.removeAll(identifier);
}


void
SceneViewer::removeAllImageFilters() {
	imageFilterIdentifiers_.clear();
}


clockwork::Matrix4
SceneViewer::calculateViewTransform() {
	//TODO Implement me.
	return Matrix4();
}


clockwork::Matrix4
SceneViewer::calculateProjectionTransform() {
	//TODO Implement me.
	return Matrix4();
}