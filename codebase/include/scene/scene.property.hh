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


namespace clockwork {
namespace scene {

/**
 * A Property defines the behaviors and characteristics of a given scene entity.
 */
template<typename EntityType>
class Property : public clockwork::scene::Entity
{
public:
	/**
	 * Return the entity that is characterised by this property.
	 */
	EntityType& getEntity()
	{
		return _entity;
	}
protected:
	/**
	 * Instantiate a named Property that is attached to a given entity.
	 * @param entity the entity that is characterised by this property.
	 * @param name the property's name.
	 */
	Property(const EntityType& entity, const std::string& name) :
	Leaf(name),
	_entity(entity)
	{
		//setNameEditable(false);
	}
private:
	/**
	 * The entity that is characterised by this property.
	 */
	const EntityType& _entity;
};
} // namespace scene
} // namespace clockwork

