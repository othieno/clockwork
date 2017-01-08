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
#ifndef CLOCKWORK_SCENE_OBJECT_HH
#define CLOCKWORK_SCENE_OBJECT_HH

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "SceneObjectAppearance.hh"
#include "toString.hh"


namespace clockwork {
/**
 * A SceneObject is a special node in a scene with a position, orientation
 * and scale, as well as other properties.
 */
class SceneObject : public SceneNode {
	Q_OBJECT
	Q_PROPERTY(QVector3D position READ getPosition WRITE setPosition NOTIFY positionChanged)
	Q_PROPERTY(QQuaternion rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
	Q_PROPERTY(QVector3D scale READ getScale WRITE setScale NOTIFY scaleChanged)
public:
	/**
	 * Updates the scene object.
	 */
	void update() Q_DECL_OVERRIDE;
	/**
	 * Return the scene object's position in the scene.
	 */
	const QVector3D& getPosition() const;
	/**
	 * Set the scene object's position.
	 * @param position the position to set.
	 */
	Q_INVOKABLE void setPosition(const QVector3D& position);
	/**
	 * Set the scene object's position.
	 * @param x the scene object's position on the X axis.
	 * @param y the scene object's position on the Y axis.
	 * @param z the scene object's position on the Z axis.
	 */
	void setPosition(const qreal x, const qreal y, const qreal z);
	/**
	 * Return the scene object's rotation quaternion.
	 */
	const QQuaternion& getRotation() const;
	/**
	 * Set the scene object's rotation quaternion.
	 * @param rotation the rotation quaternion to set.
	 */
	void setRotation(const QQuaternion& rotation);
	/**
	 * Set the scene object's rotation quaternion based on the specified
	 * Euler angles in degrees.
	 * @param pitch the scene object's rotation around the X axis.
	 * @param yaw the scene object's rotation around the Y axis.
	 * @param roll the scene object's rotation around the Z axis.
	 */
	void setRotation(const float pitch, const float yaw, const float roll);
	/**
	 * Return the scene object's scaling vector.
	 */
	const QVector3D& getScale() const;
	/**
	 * Set the scene object's scale defined by a given scaling vector.
	 * The vector should contain scale factors for the X, Y and Z axes.
	 * @param scaling the vector containing the scaling factors to set.
	 */
	void setScale(const QVector3D& scaling);
	/**
	 * Set the scene object's scale.
	 * @param x the scene object's scale factor on the X axis.
	 * @param y the scene object's scale factor on the Y axis.
	 * @param z the scene object's scale factor on the Z axis.
	 */
	void setScale(const qreal x, const qreal y, const qreal z);
	/**
	 * Returns the scene object's model transformation matrix.
	 */
	QMatrix4x4 getModelTransform() const;
	/**
	 * Returns the scene object's cumulative (composite) model transformation matrix.
	 */
	const QMatrix4x4& getCumulativeModelTransform() const;
	/**
	 * Returns the property with the specified type, if one exists.
	 * @param type the type of property to return.
	 */
	template<class Property> Property* getProperty(const SceneObjectProperty::Type type) {
		static_assert(std::is_base_of<SceneObjectProperty, Property>::value);
		return getChild<Property>(toString(type));
	}
	/**
	 * Returns the property with the specified type, if one exists.
	 * @param type the type of property to return.
	 */
	template<class Property> const Property* getProperty(const SceneObjectProperty::Type type) const {
		static_assert(std::is_base_of<SceneObjectProperty, Property>::value);
		return getChild<const Property>(toString(type));
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
	/**
	 * Returns the object's appearance, if the property exists, nullptr otherwise.
	 */
	const SceneObjectAppearance* getAppearance() const;
protected:
	/**
	 * Instantiates a named scene object.
	 * @param name the scene object's name.
	 */
	explicit SceneObject(const QString& name);
private:
	/**
	 * Updates the scene object's cumulative (composite) model transformation matrix.
	 */
	void updateCumulativeModelTransform();
	/**
	 * The scene object's position in the world.
	 */
	QVector3D position_;
	/**
	 * The scene object's rotation.
	 */
	QQuaternion rotation_;
	/**
	 * The scene object's scaling vector.
	 */
	QVector3D scale_;
	/**
	 * The scene object's cumulative (composite) model transformation matrix. This is a concatenation
	 * of the model transformation matrices of this node's ancestors (parent, grand-parent, great
	 * grand-parent, great great grand-parent, ...), with its own transformation matrix.
	 */
	QMatrix4x4 cumulativeModelTransform_;
	/**
	 * A flag that signals whether or not the composite model transformation matrix needs to be
	 * recalculated before it can be used.
	 */
	bool isCumulativeModelTransformDirty_;
signals:
	/**
	 * A signal that is emitted when the scene object's position changes.
	 * @param position the scene object's new position.
	 */
	void positionChanged(const QVector3D& position);
	/**
	 * A signal that is emitted when the scene object's rotation changes.
	 * @param rotation the scene object's new rotation.
	 */
	void rotationChanged(const QQuaternion& rotation);
	/**
	 * A signal that is emitted when the scene object's scale changes.
	 * @param scale the scene object's new scale.
	 */
	void scaleChanged(const QVector3D& scale);
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_HH
