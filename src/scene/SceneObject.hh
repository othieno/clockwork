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
#ifndef CLOCKWORK_SCENE_OBJECT_HH
#define CLOCKWORK_SCENE_OBJECT_HH

#include "SceneObjectAppearance.hh"
#include "Matrix4.hh"
#include "toString.hh"


namespace clockwork {
/**
 * A SceneObject is a special node in a scene with a position, orientation
 * and scale, as well as other properties.
 */
class SceneObject : public SceneNode {
public:
	/**
	 * Instantiates a named scene object.
	 * @param name the scene object's name.
	 */
	explicit SceneObject(const QString& name);
	/**
	 * Return the scene object's position in the scene.
	 */
	const Point3& getPosition() const;
	/**
	 * Set the scene object's position.
	 * @param position the position to set.
	 */
	void setPosition(const Point3& position);
	/**
	 * Set the scene object's position.
	 * @param x the scene object's position on the X axis.
	 * @param y the scene object's position on the Y axis.
	 * @param z the scene object's position on the Z axis.
	 */
	void setPosition(const double x, const double y, const double z);
	/**
	 * Return the scene object's rotation vector.
	 */
	const Vector3& getRotation() const;
	/**
	 * Set the scene object's rotation vector. The vector should contain
	 * angles (in degrees) for rotations around the X axis (pitch),
	 * Y axis (yaw) and Z axis (roll).
	 * @param rotation the rotation vector to set.
	 */
	void setRotation(const Vector3& rotation);
	/**
	 * Set the scene object's rotation angles (in degrees).
	 * @param pitch the scene object's pitch angle (rotation around the X axis).
	 * @param yaw the scene object's yaw angle  (rotation around the Y axis).
	 * @param roll the scene object's roll angle (rotation around the Z axis).
	 */
	void setRotation(const double pitch, const double yaw, const double roll);
	/**
	 * Return the scene object's scaling vector.
	 */
	const Vector3& getScale() const;
	/**
	 * Set the scene object's scale defined by a given scaling vector.
	 * The vector should contain scale factors for the X, Y and Z axes.
	 * @param scaling the vector containing the scaling factors to set.
	 */
	void setScale(const Vector3& scaling);
	/**
	 * Set the scene object's scale.
	 * @param x the scene object's scale factor on the X axis.
	 * @param y the scene object's scale factor on the Y axis.
	 * @param z the scene object's scale factor on the Z axis.
	 */
	void setScale(const double x, const double y, const double z);
	/**
	 * Returns the scene object's model transformation matrix.
	 */
	Matrix4 getModelTransform() const;
	/**
	 * Returns the scene object's cumulative (composite) model transformation matrix.
	 */
	const Matrix4& getCumulativeModelTransform() const;
	/**
	 * Updates the scene object's cumulative (composite) model transformation matrix.
	 */
	void updateCumulativeModelTransform();
	/**
	 * Returns the property with the specified type, if one exists.
	 * @param type the type of property to return.
	 */
	template<class Property> Property* getProperty(const SceneObjectProperty::Type type) {
		static_assert(std::is_base_of<SceneObjectProperty, Property>::value);
		return findChild<Property*>(toString(type), Qt::FindDirectChildrenOnly);
	}
	/**
	 * Returns the property with the specified type, if one exists.
	 * @param type the type of property to return.
	 */
	template<class Property> const Property* getProperty(const SceneObjectProperty::Type type) const {
		static_assert(std::is_base_of<SceneObjectProperty, Property>::value);
		return findChild<const Property*>(toString(type), Qt::FindDirectChildrenOnly);
	}
	/**
	 * Adds a property to the SceneObject and returns its instance.
	 * @param type the type of property to add to the object.
	 */
	template<class Property> Property& addProperty(const SceneObjectProperty::Type type) {
		Property* property = getProperty<Property>(type);
		if (property == nullptr) {
			switch (type) {
				case SceneObjectProperty::Type::Appearance:
					property = new SceneObjectAppearance(*this);
					break;
				default:
					qFatal("[SceneObject::addProperty] Undefined SceneObjectProperty::Type!");
			}
		}
		return *property;
	}
	/**
	 * Removes a property.
	 * @param type the type of the property to remove.
	 */
	void removeProperty(const SceneObjectProperty::Type type);
private:
	/**
	 * The scene object's position in the world.
	 */
	Point3 position_;
	/**
	 * The scene object's rotation vector holds rotation angles (in degrees) for the X, Y and Z axes.
	 */
	Vector3 rotation_;    //TODO Use quaternions
	/**
	 * The scene object's scaling vector.
	 */
	Vector3 scale_;
	/**
	 * The scene object's cumulative (composite) model transformation matrix. This is a concatenation
	 * of the model transformation matrices of this node's ancestors (parent, grand-parent, great
	 * grand-parent, great great grand-parent, ...), with its own transformation matrix.
	 */
	Matrix4 cumulativeModelTransform_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_HH
