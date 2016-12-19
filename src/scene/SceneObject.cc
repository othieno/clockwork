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
#include "SceneObject.hh"

using clockwork::SceneObject;


SceneObject::SceneObject(const QString& name) :
SceneNode(SceneNode::Type::Object, name),
scale_(1, 1, 1) {}


const QVector3D&
SceneObject::getPosition() const {
	return position_;
}


void
SceneObject::setPosition(const QVector3D& p) {
	position_ = p;
	emit positionChanged(position_);
}


void
SceneObject::setPosition(const qreal x, const qreal y, const qreal z) {
	position_ = QVector3D(x, y, z);
	emit positionChanged(position_);
}


const QQuaternion&
SceneObject::getRotation() const {
	return rotation_;
}


void
SceneObject::setRotation(const QQuaternion& r) {
	rotation_ = r;
	emit rotationChanged(rotation_);
}


void
SceneObject::setRotation(const float pitch, const float yaw, const float roll) {
	rotation_ = QQuaternion::fromEulerAngles(pitch, yaw, roll);
	emit rotationChanged(rotation_);
}


const QVector3D&
SceneObject::getScale() const {
	return scale_;
}


void
SceneObject::setScale(const QVector3D& s) {
	scale_ = s;
	emit scaleChanged(scale_);
}


void
SceneObject::setScale(const qreal x, const qreal y, const qreal z) {
	scale_ = QVector3D(x, y, z);
	emit scaleChanged(scale_);
}


QMatrix4x4
SceneObject::getModelTransform() const {
	QMatrix4x4 model;
	model.translate(position_);
	model.rotate(rotation_);
	model.scale(scale_);

	return model;
}


const QMatrix4x4&
SceneObject::getCumulativeModelTransform() const {
	return cumulativeModelTransform_;
}


void
SceneObject::updateCumulativeModelTransform() {
	cumulativeModelTransform_ = getModelTransform();
	const auto* const parentObject = static_cast<SceneObject*>(parent());
	if (parentObject != nullptr)
		cumulativeModelTransform_ = parentObject->getCumulativeModelTransform() * cumulativeModelTransform_;
}


void
SceneObject::removeProperty(const SceneObjectProperty::Type type) {
	auto* const property = getProperty<SceneObjectProperty>(type);
	if (property != nullptr) {
		property->setParent(nullptr);
		property->disconnect();
		property->deleteLater();
	}
}
