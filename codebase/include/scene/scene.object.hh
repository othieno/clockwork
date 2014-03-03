/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
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

#include "scene.entity.hh"
#include "point3.hh"
#include "quaternion.hh"
#include "task.hh"


namespace clockwork {
namespace scene {

/**
 * Objects are scene entities that have a position, orientation (rotation) and scaling.
 */
class Object : public Entity
{
public:
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
    * Return the object's rotation.
    */
   const clockwork::Quaternion& getRotation() const;
   /**
    * Set the object's rotation.
    * @param rotation the rotation to set.
    */
   void setRotation(const clockwork::Quaternion& rotation);
   /**
    * Set the object's rotation angles (in degrees).
    * @param roll the roll angle to set.
    * @param yaw the yaw angle to set.
    * @param pitch the pitch angle to set.
    */
   void setRotation(const double roll, const double yaw, const double pitch);
   /**
    * Return the object's scaling vector.
    */
   const clockwork::Vector3& getScalingVector() const;
   /**
    * Set the object's scaling vector.
    * @param scaling the scaling vector to set.
    */
   void setScalingVector(const clockwork::Vector3& scaling);
   /**
    * @see clockwork::scene::Node::updateGeometry.
    */
   virtual void updateGeometry(const clockwork::Matrix4&) override final;
   /**
    * Return the node's model transformation matrix.
    */
   const clockwork::Matrix4& getModelMatrix() const;
   /**
    * Set the node's model transformation matrix.
    * @param model the model transformation matrix to set.
    */
   void setModelMatrix(const clockwork::Matrix4& model);
protected:
   /**
    * Instantiate a named object.
    * @param name the object's name.
    */
   Object(const std::string& name);
   /**
    * The object's position in the world.
    */
   clockwork::Point3 _position;
   /**
    * The object's rotation.
    */
   clockwork::Quaternion _rotation;
   /**
    * The object's scaling vector.
    */
   clockwork::Vector3 _scaling;
private:
   /**
    * The object's model transformation matrix.
    */
   clockwork::Matrix4 _modelMatrix;
   /**
    * The UpdateGeometryTask updates the model matrix of a given node and its children.
    */
   class UpdateGeometryTask : public concurrency::Task
   {
   public:
      /**
       * Instantiate a UpdateGeometryTask that will update the model matrix of a given
       * scene object and its children.
       * @param object the scene object to update.
       * @param CMTM the cumulative model transformation matrix.
       */
      UpdateGeometryTask(clockwork::scene::Object& object, const clockwork::Matrix4& CMTM);
      /**
       * @see clockwork::concurrency::Task::onRun.
       */
      virtual void onRun() override final;
   private:
      /**
       * A reference to the scene object that will be updated by this task.
       */
      clockwork::scene::Object& _object;
      /**
       * The cumulative model transformation matrix that will be concatenated to the object's
       * own model transformation matrix. This usually references the node's parent's model
       * transformation matrix.
       */
      const clockwork::Matrix4& _CMTM;
   };
};
} // namespace scene
} // namespace clockwork
