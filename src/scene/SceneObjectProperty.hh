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
#ifndef CLOCKWORK_SCENE_OBJECT_PROPERTY_HH
#define CLOCKWORK_SCENE_OBJECT_PROPERTY_HH

#include "SceneNode.hh"


namespace clockwork {
/**
 * @see SceneObject.hh
 */
class SceneObject;
/**
 * A SceneObjectProperty defines a characteristic or behavior of a SceneObject.
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
	 * Returns the property's owner.
	 */
	SceneObject& getOwner();
	/**
	 * Returns the property's type.
	 */
	Type getType() const;
protected:
	/**
	 * Instantiates a named SceneObjectProperty object attached to a given SceneObject instance.
	 * @param owner the scene object that is characterized by this property.
	 * @param type the property's internal type.
	 * @param name the property's human-readable name.
	 */
	SceneObjectProperty(SceneObject& owner, const Type type, const QString& name);
private:
	/**
	 * The property's owner, i.e. the object that is characterized by this property.
	 */
	SceneObject& owner_;
	/**
	 * The property's type.
	 */
	const Type type_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_PROPERTY_HH
