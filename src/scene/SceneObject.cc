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
#include "SceneObject.hh"
#include "SceneObjectAppearance.hh"
#include "toString.hh"

using clockwork::SceneObject;


SceneObject::SceneObject(const QString& name) :
SceneNode(SceneNode::Type::Object, name),
position_(0, 0, 0),
rotation_(0, 0, 0),
scale_(1, 1, 1) {}


const clockwork::Point3&
SceneObject::getPosition() const {
	return position_;
}


void
SceneObject::setPosition(const clockwork::Point3& p) {
	setPosition(p.x, p.y, p.z);
}


void
SceneObject::setPosition(const double x, const double y, const double z) {
	position_.x = x;
	position_.y = y;
	position_.z = z;
}


const clockwork::Vector3&
SceneObject::getRotation() const {
	return rotation_;
}


void
SceneObject::setRotation(const clockwork::Vector3& r) {
	setRotation(r.i, r.j, r.k);
}


void
SceneObject::setRotation(const double pitch, const double yaw, const double roll) {
	rotation_.i = pitch;
	rotation_.j = yaw;
	rotation_.k = roll;
}


const clockwork::Vector3&
SceneObject::getScale() const {
	return scale_;
}


void
SceneObject::setScale(const clockwork::Vector3& s) {
	setScale(s.i, s.j, s.k);
}


void
SceneObject::setScale(const double x, const double y, const double z) {
	scale_.i = x;
	scale_.j = y;
	scale_.k = z;
}


clockwork::Matrix4
SceneObject::getModelTransform() const {
	return Matrix4::model(position_, rotation_, scale_);
}


const clockwork::Matrix4&
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


template<class Property> Property*
SceneObject::getProperty(const SceneObjectProperty::Type type) {
	static_assert(std::is_base_of<Property, SceneObjectProperty>::value);
	return findChild<Property>(toString(type), Qt::FindDirectChildrenOnly);
}


template<class Property> Property&
SceneObject::addProperty(const SceneObjectProperty::Type type) {
	Property* property = getProperty<Property>(type);
	if (property == nullptr) {
		switch (type) {
			case SceneObjectProperty::Type::Appearance:
				property = new SceneObjectAppearance(*this);
				break;
			default:
				qFatal("[SceneObject::addProperty] Undefined SceneObjectProperty::Type!");
				break;
		}
	}
	return *property;
}


void
SceneObject::removeProperty(const SceneObjectProperty::Type) {
	qFatal("[SceneObject::removeProperty] Implement me!");
}
