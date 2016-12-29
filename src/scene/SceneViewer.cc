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
#include "SceneViewer.hh"

using clockwork::SceneViewer;


SceneViewer::SceneViewer(const Type type, const QString& name) :
SceneObject(name),
type_(type),
projection_(Projection::Perspective),
center_(0, 0, 0),
scissor_(QPointF(0.0f, 0.0f), QPointF(1.0f, 1.0f)),
renderingAlgorithm_(RenderingAlgorithm::NormalMapping),
primitiveMode_(Primitive::Triangle),
textureFilterIdentifier_(TextureFilter::Identifier::Bilinear) {
	updateViewTransform();
	updateProjectionTransform();
	updateViewProjectionTransform();
}


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
		updateProjectionTransform();
	}
}


const QMatrix4x4&
SceneViewer::getProjectionTransform() const {
	return projectionTransform_;
}


const QMatrix4x4&
SceneViewer::getViewTransform() const {
	return viewTransform_;
}


const QMatrix4x4&
SceneViewer::getViewProjectionTransform() const {
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


const QVector3D&
SceneViewer::getCenter() const {
	return center_;
}


void
SceneViewer::setCenter(const QVector3D& center) {
	if (center_ != center) {
		center_ = center;
		emit centerChanged(center_);
	}
}


const QRectF&
SceneViewer::getScissor() const {
	return scissor_;
}


void
SceneViewer::setScissor(const QRectF& scissor) {
	if (scissor_ != scissor) {
		scissor_ = scissor;
		emit scissorChanged(scissor_);
	}
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
		updateProjectionTransform();
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


bool
SceneViewer::isObjectVisible(const SceneObject&) const {
	//TODO Implement me.
	return true;
}


void
SceneViewer::updateViewTransform() {
	viewTransform_.setToIdentity();
	viewTransform_.lookAt(getPosition(), center_, QVector3D(0, 1, 0));
}


void
SceneViewer::updateProjectionTransform() {
	projectionTransform_.setToIdentity();
}


void
SceneViewer::updateViewProjectionTransform() {
	viewProjectionTransform_ = projectionTransform_ * viewTransform_;
}
