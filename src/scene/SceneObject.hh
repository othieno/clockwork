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

#include <QObject>
#include <QUuid>
#include <QString>
#include <QSet>
#include <QHash>
#include "Matrix4.hh"
/*
#include "SceneProperty.hh"
*/


namespace clockwork {

/**
 * An Object is a node in the scene graph that has a set of one or more
 * properties, with a position, orientation (rotation) and scale at least.
 * They may be visible to a viewer if the right conditions are met, or
 * may be invisible.
 */
class SceneObject : public QObject
{
public:
    /**
     * Instantiates a named scene object.
     * @param name the scene object's name.
     */
    SceneObject(const QString& name);
    /**
     * Retursn the scene object's unique identifier.
     */
    const QUuid& getIdentifier() const;
    /**
     * Returns the scene object's name.
     */
    QString getName() const;
    /**
     * Sets the scene object's name.
     * @param name the scene object's name.
     */
    void setName(const QString& name);
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
     * Returns true if this object is pruned, false otherwise.
     */
    bool isPruned() const;
    /**
     * Prune this object.
     * @param pruned true if this node is to be pruned, false otherwise.
     */
    void setPruned(const bool pruned);
private:
    /**
     * The scene object's unique identifier.
     */
    const QUuid identifier_;
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
     * If set to true, this object will be skipped by certain operations performed on
     * nodes in the scene graph that this object belongs to. For example, if this object is out of
     * view, it is pruned so that the rendering process does not waste time on an otherwise
     * invisible object.
     */
    bool isPruned_;
};

} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_HH
