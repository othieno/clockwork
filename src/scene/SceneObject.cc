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


SceneObject::SceneObject(SceneNode& parent, const QString& name) :
SceneNode(SceneNode::Type::Object, &parent, name),
scale_(1, 1, 1),
isCumulativeModelTransformDirty_(true) {
	connect(this, &SceneObject::positionChanged, this, &SceneObject::nodeChanged);
	connect(this, &SceneObject::rotationChanged, this, &SceneObject::nodeChanged);
	connect(this, &SceneObject::scaleChanged,    this, &SceneObject::nodeChanged);
}


void
SceneObject::update() {
	updateCumulativeModelTransform();
	SceneNode::update(); // Update the node's children.
}


const QVector3D&
SceneObject::getPosition() const {
	return position_;
}


void
SceneObject::setPosition(const QVector3D& p) {
	if (position_ != p) {
		position_ = p;
		isCumulativeModelTransformDirty_ = true;
		emit positionChanged(position_);
	}
}


void
SceneObject::setPosition(const qreal x, const qreal y, const qreal z) {
	setPosition(QVector3D(x, y, z));
}


const QQuaternion&
SceneObject::getRotation() const {
	return rotation_;
}


void
SceneObject::setRotation(const QQuaternion& r) {
	if (rotation_ != r) {
		rotation_ = r;
		isCumulativeModelTransformDirty_ = true;
		emit rotationChanged(rotation_);
	}
}


void
SceneObject::setRotation(const float pitch, const float yaw, const float roll) {
	setRotation(QQuaternion::fromEulerAngles(pitch, yaw, roll));
}


const QVector3D&
SceneObject::getScale() const {
	return scale_;
}


void
SceneObject::setScale(const QVector3D& s) {
	if (scale_ != s) {
		scale_ = s;
		isCumulativeModelTransformDirty_ = true;
		emit scaleChanged(scale_);
	}
}


void
SceneObject::setScale(const qreal x, const qreal y, const qreal z) {
	setScale(QVector3D(x, y, z));
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
SceneObject::removeProperty(const SceneObjectProperty::Type type) {
	auto* const property = getProperty<SceneObjectProperty>(type);
	if (property != nullptr) {
		property->setParent(nullptr);
		property->disconnect();
		property->deleteLater();
	}
}


const clockwork::SceneObjectAppearance*
SceneObject::getAppearance() const {
	return getProperty<const SceneObjectAppearance>(SceneObjectProperty::Type::Appearance);
}


void
SceneObject::updateCumulativeModelTransform() {
	if (isCumulativeModelTransformDirty_) {
		isCumulativeModelTransformDirty_ = false;

		cumulativeModelTransform_ = getModelTransform();

		const SceneNode* const parent = getParent();
		if (parent != nullptr && parent->getNodeType() == SceneNode::Type::Object) {
			const auto& parentCMTM = static_cast<const SceneObject*>(parent)->getCumulativeModelTransform();
			cumulativeModelTransform_ = parentCMTM * cumulativeModelTransform_;
		}
	}
}
