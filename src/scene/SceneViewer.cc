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


SceneViewer::SceneViewer(const Type type, const QString& name) :
SceneObject(name),
type_(type),
projection_(Projection::Perspective),
updateCachedViewTransform_(true),
updateCachedProjectionTransform_(true),
renderingAlgorithm_(RenderingAlgorithm::Point),
lineDrawingAlgorithm_(Renderer::LineDrawingAlgorithm::Bresenham),
primitiveMode_(Primitive::Triangle),
textureFilterIdentifier_(TextureFilter::Identifier::Bilinear) {}


SceneViewer::Type
SceneViewer::getType() const {
	return type_;
}


clockwork::Projection
SceneViewer::getProjection() const {
	return projection_;
}


void
SceneViewer::setProjection(const Projection projection) {
	if (projection_ != projection) {
		projection_ = projection;
		updateCachedProjectionTransform_ = true;
	}
}


const clockwork::Matrix4&
SceneViewer::getViewTransform() const {
	if (updateCachedViewTransform_) {
		updateCachedViewTransform_ = false;
		cachedViewTransform_ = calculateViewTransform();
	}
	return cachedViewTransform_;
}


const clockwork::Matrix4&
SceneViewer::getProjectionTransform() const {
	if (updateCachedProjectionTransform_) {
		updateCachedProjectionTransform_ = false;
		cachedProjectionTransform_ = calculateProjectionTransform();
	}
	return cachedProjectionTransform_;
}


const clockwork::Matrix4&
SceneViewer::getViewProjectionTransform() const {
	if (updateCachedViewTransform_ || updateCachedProjectionTransform_) {
		const auto& P = getProjectionTransform();
		const auto& V = getViewTransform();
		cachedViewProjectionTransform_ = P * V; // The order is important: PROJECTION * VIEW!
	}
	return cachedViewProjectionTransform_;
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
		updateCachedProjectionTransform_ = true;
//	}
}


clockwork::RenderingAlgorithm
SceneViewer::getRenderingAlgorithm() const {
	return renderingAlgorithm_;
}


void
SceneViewer::setRenderingAlgorithm(const RenderingAlgorithm algorithm) {
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


clockwork::Primitive
SceneViewer::getPrimitiveMode() const {
	return primitiveMode_;
}


void
SceneViewer::setPrimitiveMode(const Primitive primitive) {
	primitiveMode_ = primitive;
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
SceneViewer::calculateViewTransform() const {
	//TODO Implement me.
	return Matrix4();
}


clockwork::Matrix4
SceneViewer::calculateProjectionTransform() const {
	//TODO Implement me.
	return Matrix4();
}


bool
SceneViewer::isObjectVisible(const SceneObject&) const {
	//TODO Implement me.
	return true;
}
