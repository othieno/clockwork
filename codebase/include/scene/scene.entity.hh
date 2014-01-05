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

#include "uid.hh"
#include "scene.node.hh"


namespace clockwork {
namespace scene {

/**
 * A scene entity is everything that exists in a scene, visible or invisible.
 * Think of entities as abstract existences, in that we know they exist but we
 * may or may not be able to interact with them.
 */
class Entity : public clockwork::scene::Node
{
public:
	/**
	 * Return the entity's unique identifier.
	 */
	const clockwork::UID& getIdentifier() const;
protected:
	/**
	 * Instantiate a named entity.
	 * @param name the entity's name.
	 */
	Entity(const std::string& name);
private:
	/**
	 * The entity's universally unique identifier (UUID) which allows us to
	 * distinguish between entities even when their names are changed.
	 */
	const clockwork::UID _identifier;
};

} // namespace scene
} // namespace clockwork
