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
#ifndef CLOCKWORK_SCENE_OBJECT_PROPERTY_HH
#define CLOCKWORK_SCENE_OBJECT_PROPERTY_HH

#include "SceneNode.hh"
#include "enum_traits.hh"


namespace clockwork {
/**
 * @see SceneObject.hh
 */
class SceneObject;
/**
 * A SceneObjectProperty defines a characteristic or behavior of a SceneObject.
 * A SceneObject may have at most one property of a given type.
 */
class SceneObjectProperty : public SceneNode {
public:
	/**
	 * An enumeration of the available types of properties.
	 */
	enum class Type {
		Appearance,
		//LightEmission,
	};
	/**
	 *
	 */
	SceneObjectProperty(const SceneObjectProperty&) = delete;
	/**
	 *
	 */
	SceneObjectProperty(SceneObjectProperty&&) = delete;
	/**
	 *
	 */
	SceneObjectProperty& operator=(const SceneObjectProperty&) = delete;
	/**
	 *
	 */
	SceneObjectProperty& operator=(SceneObjectProperty&&) = delete;
	/**
	 * Returns the property's type.
	 */
	Type getType() const;
	/**
	 * Returns the property's owner.
	 */
	const SceneObject& getOwner() const;
protected:
	/**
	 * Instantiates a named SceneObjectProperty object attached to a given SceneObject instance.
	 * @param type the property's type.
	 */
	SceneObjectProperty(const Type type);
private:
	/**
	 * The property's type.
	 */
	const Type type_;
};
/**
 * Declares a list of all available scene object property types.
 */
DECLARE_ENUMERATOR_LIST(SceneObjectProperty::Type, {
	SceneObjectProperty::Type::Appearance,
})
/**
 * Returns the human-readable name of the specified scene object property type.
 * @param type the scene object property type to query.
 */
template<> template<class String> String
enum_traits<SceneObjectProperty::Type>::name(const SceneObjectProperty::Type type) {
	switch (type) {
		case SceneObjectProperty::Type::Appearance:
			return "Appearance";
		default:
			return "???";
	}
}
/**
 * Returns the specified scene object property type's hash.
 * @param type the scene object property type to hash.
 */
constexpr uint
qHash(SceneObjectProperty::Type type) {
	return ::qHash(enum_traits<SceneObjectProperty::Type>::ordinal(type));
}
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_PROPERTY_HH
