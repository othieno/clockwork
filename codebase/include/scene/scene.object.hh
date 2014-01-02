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


namespace clockwork {
namespace scene {

/**
 * Objects are entities that have a position, orientation and scale in the scene.
 */
class Object : public clockwork::scene::Entity
{
public:
	/**
	 * Return the object's position in the scene.
	 */
	const clockwork::Point3& getPosition() const;
	/**
	 * Return the object's rotation.
	 */
	const clockwork::Point3& getRotation() const;
	/**
	 * Return the object's scale.
	 */
	const clockwork::Point3& getScale() const;
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
	clockwork::Point3 _rotation;
	/**
	 * The object's scale.
	 */
	clockwork::Point3 _scale;
private:
	/**
	 * The object's model transformation matrix.
	 */
	clockwork::Matrix4 _modelMatrix;
};
} // namespace scene
} // namespace clockwork
