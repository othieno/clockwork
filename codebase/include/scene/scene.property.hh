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


namespace clockwork {
namespace scene {

/**
 * @see scene.object.hh.
 */
class Object;

/**
 * TODO Explain me better.
 * A Property defines a characteristic of the Object that it is attached to. A
 * Property is unique to an Object, but different Properties of the same
 * behavior may have identical parameters.
 */
class Property : public QObject
{
public:
   /**
    * The Property identifier.
    */
   enum class Identifier : unsigned int
   {
      Appearance = 0,
      LightEmission = 1
   };
   /**
    * Return the object that holds this property.
    */
   Object& getProprietor();
   /**
    * Return the property's identifier.
    */
   const Property::Identifier& getIdentifier() const;
   /**
    * Return the property's name.
    */
   QString getName() const;
protected:
   /**
    * Instantiate a named Property with an assigned identifier, that is attached to
    * a given Object.
    * @param proprietor the scene object that holds this property.
    * @param name the property's name.
    * @param identifier the property's identifier.
    */
   Property(Object& proprietor, const QString& name, const Property::Identifier& identifier);
   /**
    * A property may not be copied.
    */
   Property(const Property&) = delete;
   Property& operator=(const Property&) = delete;
private:
   /**
    * The object that holds this property.
    */
   Object& _proprietor;
   /**
    * The property's identifier.
    */
   const Property::Identifier _identifier;
};

} // namespace scene
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::scene::Property::Identifier&);
