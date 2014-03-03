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
#include "scene.object.hh"
#include "graphics.subsystem.hh"
#include "services.hh"

using clockwork::scene::Object;


Object::Object(const std::string& name) :
Entity(name),
_position(0.0, 0.0, 0.0),
_rotation(),
_scaling(1.0, 1.0, 1.0)
{}


Object::UpdateGeometryTask::UpdateGeometryTask(Object& object, const clockwork::Matrix4& CMTM) :
Task(static_cast<int>(clockwork::concurrency::TaskPriority::PhysicsUpdateGeometryTask)),
_object(object),
_CMTM(CMTM)
{}


void
Object::UpdateGeometryTask::onRun()
{
   const auto& position = _object.getPosition();
   const auto& rotation = _object.getRotation();
   const auto& scale = _object.getScale();

   const auto& newCMTM = _CMTM * clockwork::Matrix4::model(position, rotation, scale);
   _object.setModelMatrix(newCMTM);

   for (auto* const node : _object.getChildren())
      node->updateGeometry(newCMTM);
}


const clockwork::Matrix4&
Object::getModelMatrix() const
{
   return _modelMatrix;
}


void
Object::setModelMatrix(const clockwork::Matrix4& model)
{
   _modelMatrix = model;
}


void
Object::updateGeometry(const clockwork::Matrix4& CMTM)
{
   if (!isPruned())
      clockwork::system::Services::Concurrency.submitTask(new UpdateGeometryTask(*this, CMTM));
}


const clockwork::Point3&
Object::getPosition() const
{
   return _position;
}


void
Object::setPosition(const clockwork::Point3& position)
{
   _position = position;
}


const clockwork::Vector3&
Object::getRotation() const
{
   return _rotation;
}


void
Object::setRotation(const clockwork::Vector3& rotation)
{
   _rotation = rotation;
}


void
Object::setRotation(const double roll, const double yaw, const double pitch)
{
   _rotation.i = roll;
   _rotation.j = yaw;
   _rotation.k = pitch;
}


const clockwork::Vector3&
Object::getScale() const
{
   return _scaling;
}


void
Object::setScale(const clockwork::Vector3& scaling)
{
   _scaling = scaling;
}


void
Object::setScale(const double x, const double y, const double z)
{
   _scaling.i = x;
   _scaling.j = y;
   _scaling.k = z;
}
