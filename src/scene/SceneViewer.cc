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
#include "Service.hh"

using clockwork::SceneViewer;


SceneViewer::SceneViewer(const Type type, const QString& name) :
SceneObject(name),
type_(type),
projection_(Projection::Perspective),
isProjectionTransformDirty_(true),
isViewTransformDirty_(true),
isViewProjectionTransformDirty_(true),
isViewportTransformDirty_(true),
textureFilterIdentifier_(TextureFilter::Identifier::Bilinear) {
	setPosition(0, 0, 3);

	const auto& markViewTransformDirty = [this]() { isViewTransformDirty_ = true; };
	const auto& markViewportTransformDirty = [this]() { isViewportTransformDirty_ = true; };

	connect(this, &SceneObject::positionChanged, markViewTransformDirty);
	connect(this, &SceneObject::rotationChanged, markViewTransformDirty);
	connect(&Service::Graphics.getFramebuffer(), &Framebuffer::resized, markViewportTransformDirty);
}


void
SceneViewer::update() {
	updateViewTransform();
	updateProjectionTransform();
	updateViewProjectionTransform();
	updateViewportTransform();

	SceneObject::update(); // Update CMTM and children.
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
		isProjectionTransformDirty_ = true;
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


const QMatrix2x3&
SceneViewer::getViewportTransform() const {
	return viewportTransform_;
}


const clockwork::Viewport&
SceneViewer::getViewport() const {
	return viewport_;
}


void
SceneViewer::setViewport(const Viewport& viewport) {
	//if (viewport_ != viewport) { // FIXME Implement comparison operator for the Viewport class.
	if (true) {
		viewport_ = viewport;
		isViewportTransformDirty_ = true;
		emit viewportChanged(viewport_);
	}
}


const QVector3D&
SceneViewer::getCenter() const {
	return viewFrustum_.center;
}


void
SceneViewer::setCenter(const QVector3D& center) {
	if (viewFrustum_.center != center) {
		viewFrustum_.center = center;
		isViewTransformDirty_ = true;
		emit centerChanged(viewFrustum_.center);
	}
}


const clockwork::ViewFrustum&
SceneViewer::getViewFrustum() const {
	return viewFrustum_;
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
	if (isViewTransformDirty_) {
		isViewTransformDirty_ = false;
		isViewProjectionTransformDirty_ = true;

		viewTransform_.setToIdentity();
		viewTransform_.lookAt(
			getPosition(),
			viewFrustum_.center,
			viewFrustum_.up
		);
	}
}


void
SceneViewer::updateProjectionTransform() {
	if (isProjectionTransformDirty_) {
		isProjectionTransformDirty_ = false;
		isViewProjectionTransformDirty_ = true;

		projectionTransform_.setToIdentity();
		projectionTransform_.perspective(
			viewFrustum_.fieldOfView,
			viewFrustum_.aspectRatio,
			viewFrustum_.nearClippingPlaneDistance,
			viewFrustum_.farClippingPlaneDistance
		);
	}
}


void
SceneViewer::updateViewProjectionTransform() {
	if (isViewProjectionTransformDirty_) {
		isViewProjectionTransformDirty_ = false;
		viewProjectionTransform_ = projectionTransform_ * viewTransform_;
	}
}


void
SceneViewer::updateViewportTransform() {
	if (isViewportTransformDirty_) {
		isViewportTransformDirty_ = false;

		const QSize& resolution = Service::Graphics.getFramebuffer().getResolution();

		const qreal x = viewport_.x * resolution.width();
		const qreal y = viewport_.y * resolution.height();
		const qreal w = viewport_.width * resolution.width();
		const qreal h = viewport_.height * resolution.height();
		const qreal n = viewFrustum_.nearClippingPlaneDistance;
		const qreal f = viewFrustum_.farClippingPlaneDistance;

		// The viewport transformation is defined as:
		// P'  = (scale                                 P)    + (translate)
		// x_w = (viewport_width / 2)                 * x_ndc + (viewport_x + (viewport_width / 2))
		// y_w = (viewport_height / 2)                * y_ndc + (viewport_y + (viewport_height / 2))
		// z_w = ((viewport_far - viewport_near) / 2) * z_ndc + ((viewport_near + viewport_far) / 2)
		// where the 3D point <x_ndc, y_ndc and z_ndc> is in the normalized device
		// coordinate (NDC) space.

		// The first column vector contains the scaling factor.
		viewportTransform_(0, 0) = 0.5 * w;
		viewportTransform_(1, 0) = 0.5 * h;
		viewportTransform_(2, 0) = 0.5 * (f - n);

		// The second contains the translation factor.
		viewportTransform_(0, 1) = x + (0.5 * w);
		viewportTransform_(1, 1) = y + (0.5 * h);
		viewportTransform_(2, 1) = 0.5 * (f + n);
	}
}
