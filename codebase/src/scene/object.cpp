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
#include "scene.hh"
#include "services.hh"
#include <cassert>

using clockwork::scene::Object;


Object::Object(const QString& name) :
_identifier(QUuid::createUuid()),
_isPruned(false),
_position(0, 0, 0),
_rotation(0, 0, 0),
_scale(1, 1, 1),
_doModelTransformUpdate(true)
{
   setObjectName(name);
}


const QUuid&
Object::getIdentifier() const
{
   return _identifier;
}


QString
Object::getName() const
{
   return objectName();
}


void
Object::setName(const QString& name)
{
   setObjectName(name);
}


const clockwork::Point3&
Object::getPosition() const
{
   return _position;
}


void
Object::setPosition(const clockwork::Point3& p)
{
   setPosition(p.x, p.y, p.z);
}


void
Object::setPosition(const double& x, const double& y, const double& z)
{
   _position.x = x;
   _position.y = y;
   _position.z = z;
   _doModelTransformUpdate = true;
}


const clockwork::Vector3&
Object::getRotation() const
{
   return _rotation;
}


void
Object::setRotation(const clockwork::Vector3& r)
{
   setRotation(r.i, r.j, r.k);
}


void
Object::setRotation(const double pitch, const double yaw, const double roll)
{
   _rotation.i = pitch;
   _rotation.j = yaw;
   _rotation.k = roll;
   _doModelTransformUpdate = true;
}


const clockwork::Vector3&
Object::getScale() const
{
   return _scale;
}


void
Object::setScale(const clockwork::Vector3& s)
{
   setScale(s.i, s.j, s.k);
}


void
Object::setScale(const double x, const double y, const double z)
{
   _scale.i = x;
   _scale.j = y;
   _scale.k = z;
   _doModelTransformUpdate = true;
}


const clockwork::Matrix4&
Object::getModelTransform()
{
   if (_doModelTransformUpdate)
   {
      _modelTransform = clockwork::Matrix4::model(_position, _rotation, _scale);
      _doModelTransformUpdate = false;
   }
   return _modelTransform;
}


const clockwork::Matrix4&
Object::getCMTM() const
{
   return _CMTM;
}


void
Object::updateCMTM()
{
   const auto* const parentObject = static_cast<const clockwork::scene::Object*>(parent());

   // Update the CMTM. Note that instead of directy accessing the _modelTransform variable,
   // getModelTransform() is used to update a possibly "dirty" transformation matrix.
   const auto& modelTransform = getModelTransform();

   _CMTM = parentObject != nullptr ? parentObject->getCMTM() * modelTransform : modelTransform;
}


bool
Object::isPruned() const
{
   return _isPruned;
}


void
Object::setPruned(const bool pruned)
{
   _isPruned = pruned;
}


void
Object::addChild(Object* const child)
{
   if (child != nullptr)
   {
      _children << child;
      child->setParent(this);
   }
}


void
Object::removeChild(Object* const child)
{
   if (child != nullptr)
   {
      _children.remove(child);
      setParent(nullptr);
      child->deleteLater();
   }
}


const QSet<Object*>&
Object::getChildren() const
{
   return _children;
}


bool
Object::hasChildren() const
{
   return !_children.empty();
}


clockwork::scene::Property&
Object::addProperty(const Property::Identifier& identifier)
{
   const auto key = static_cast<unsigned int>(identifier);
   Property* property = nullptr;

   switch (identifier)
   {
      case Property::Identifier::Appearance:
         property = new Appearance(*this);
         break;
      default:
         assert(false);
         break;
   }
   assert(property != nullptr);
   _properties.insert(key, property);

   return *property;
}


const clockwork::scene::Property*
Object::getProperty(const Property::Identifier& identifier) const
{
   const auto key = static_cast<unsigned int>(identifier);

   return _properties.contains(key) ? _properties.value(key) : nullptr;
}


bool
Object::hasProperty(const Property::Identifier& identifier) const
{
   const auto* const property = getProperty(identifier);
   if (property != nullptr)
   {
      switch (identifier)
      {
         case Property::Identifier::Appearance:
         {
            const auto* const model = static_cast<const Appearance*>(property)->getModel3D();
            return model != nullptr && !model->isEmpty();
         }
         default:
            assert(false);
            break;
      }
   }
   return false;
}


void
Object::removeProperty(const Property::Identifier& identifier)
{
   const auto key = static_cast<unsigned int>(identifier);
   if (_properties.contains(key))
      assert(_properties.remove(key) > 0);
}
