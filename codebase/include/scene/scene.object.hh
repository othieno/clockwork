/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
 *
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
#pragma once

#include <QObject>
#include <QUuid>
#include <QString>
#include <QSet>
#include <QHash>
#include "scene.property.hh"
#include "matrix4.hh"


namespace clockwork {
namespace scene {

/**
 * An Object is a node in the scene graph that has a set of one or more
 * properties, with a position, orientation (rotation) and scale at least.
 * They may be visible to a viewer if the right conditions are met, or
 * may be invisible.
 */
class Object : public QObject
{
public:
   /**
    * Instantiate a named object.
    * @param name the object's name.
    */
   Object(const QString& name);
   /**
    * Return the object's unique identifier.
    */
   const QUuid& getIdentifier() const;
   /**
    * Return the object's name.
    */
   QString getName() const;
   /**
    * Set the object's name.
    * @param name the object's new name.
    */
   void setName(const QString& name);
   /**
    * Return the object's position in the scene.
    */
   const clockwork::Point3& getPosition() const;
   /**
    * Set the object's position.
    * @param position the position to set.
    */
   void setPosition(const clockwork::Point3& position);
   /**
    * Set the object's position.
    * @param x the object's position on the X axis.
    * @param y the object's position on the Y axis.
    * @param z the object's position on the Z axis.
    */
   void setPosition(const double& x, const double& y, const double& z);
   /**
    * Return the object's rotation vector.
    */
   const clockwork::Vector3& getRotation() const;
   /**
    * Set the object's rotation vector. The vector should contain
    * angles (in degrees) for rotations around the X axis (pitch),
    * Y axis (yaw) and Z axis (roll).
    * @param rotation the rotation vector to set.
    */
   void setRotation(const clockwork::Vector3& rotation);
   /**
    * Set the object's rotation angles (in degrees).
    * @param pitch the object's pitch angle (rotation around the X axis).
    * @param yaw the object's yaw angle  (rotation around the Y axis).
    * @param roll the object's roll angle (rotation around the Z axis).
    */
   void setRotation(const double pitch, const double yaw, const double roll);
   /**
    * Return the object's scaling vector.
    */
   const clockwork::Vector3& getScale() const;
   /**
    * Set the object's scale defined by a given scaling vector.
    * The vector should contain scale factors for the X, Y and Z axes.
    * @param scaling the vector containing the scaling factors to set.
    */
   void setScale(const clockwork::Vector3& scaling);
   /**
    * Set the object's scale.
    * @param x the object's scale factor on the X axis.
    * @param y the object's scale factor on the Y axis.
    * @param z the object's scale factor on the Z axis.
    */
   void setScale(const double x, const double y, const double z);
   /**
    * Return the object's model transformation matrix.
    */
   const clockwork::Matrix4& getModelTransform();
   /**
    * Return the object's cumulative (composite) model transformation matrix (CMTM).
    */
   const clockwork::Matrix4& getCMTM() const;
   /**
    * Update the model's cumulative transformation matrix.
    */
   void updateCMTM();
   /**
    * Returns true if this object is pruned, false otherwise.
    */
   bool isPruned() const;
   /**
    * Prune this object.
    * @param pruned true if this node is to be pruned, false otherwise.
    */
   void setPruned(const bool pruned);
   /**
    * Add a child object.
    * @param object the child object to add.
    */
   void addChild(Object* const object);
   /**
    * Remove a child object.
    * @param object the child object to remove.
    */
   void removeChild(Object* const object);
   /**
    * Return the object's children.
    */
   const QSet<Object*>& getChildren() const;
   /**
    * Returns true if the object has at least one child, false otherwise.
    */
   bool hasChildren() const;
   /**
    * Add a property and return its instance.
    * @param identifier the property identifier.
    */
   Property& addProperty(const Property::Identifier& identifier);
   /**
    * Return the property with the specified identifier.
    * @param identifier the property identifier.
    */
   const Property* getProperty(const Property::Identifier& identifier) const;
   /**
    * Return true if the object has the specified property, false otherwise.
    * @param identifier the identifier of the property to query.
    */
   bool hasProperty(const Property::Identifier& identifier) const;
   /**
    * Remove a property.
    * @param identifier the identifier of the property to remove.
    */
   void removeProperty(const Property::Identifier& identifier);
   /**
    * Return the object's memory footprint in kibibytes (1 KiB = 1024 bytes).
    */
   //clockwork::u64 getMemoryFootprint();
private:
   /**
    * The object's unique identifier.
    */
   const QUuid _identifier;
   /**
    * True if this object is pruned, false otherwise.
    */
   bool _isPruned;
   /**
    * The object's position in the world.
    */
   clockwork::Point3 _position;
   /**
    * The object's rotation vector holds rotation angles (in degrees) for the X, Y and Z axes.
    */
   clockwork::Vector3 _rotation;    //TODO Use QQuaternion
   /**
    * The object's scaling vector.
    */
   clockwork::Vector3 _scale;
   /**
    * The object's model transformation matrix.
    */
   clockwork::Matrix4 _modelTransform;
   /**
    * When true, this signals that the model transformation matrix needs to be updated.
    */
   bool _doModelTransformUpdate;
   /**
    * The object's cumulative (composite) model transformation matrix. This is a
    * concatenation of the model transformation matrices of this node's parents.
    */
   clockwork::Matrix4 _CMTM;
   /**
    * The object's children.
    */
   QSet<Object*> _children;
   /**
    * The object's properties.
    */
   QHash<unsigned int, Property*> _properties;
};
} // namespace scene
} // namespace clockwork
