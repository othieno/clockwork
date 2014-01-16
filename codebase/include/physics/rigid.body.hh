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

#include "scene.object.hh"
#include "model3d.hh"


namespace clockwork {
namespace physics {

/**
 * A rigid body is a scene object that has a visual property, i.e. a 3D model.
 */
class RigidBody : public clockwork::scene::Object
{
public:
	/**
	 * Instantiate a named rigid body with a given 3D model.
	 * @param name the rigid body's name.
	 * @param model3D the rigid body's 3D model.
	 */
	RigidBody(const std::string& name, const clockwork::graphics::Model3D* model3D = nullptr);
	/**
	 * @see clockwork::scene::Node::render.
	 */
	virtual void render(const clockwork::scene::Viewer& viewer) const override final;
	/**
	 * Return the rigid body's 3D model.
	 */
	const clockwork::graphics::Model3D* getModel3D() const;
	/**
	 * Set the rigid body's 3D model.
	 * @param model3D the 3D model to set.
	 */
	void setModel3D(const clockwork::graphics::Model3D* model3D);
	/**
	 * Convert RigidBody data into string format.
	 * @param body the rigid body to convert.
	 */
	static std::string toString(const RigidBody& body);
private:
	/**
	 * The rigid body's 3D model.
	 */
	const clockwork::graphics::Model3D* _model3D;
};

/**
 * The Suzanne rigid body used for debugging.
 */
class SuzanneRigidBody : public RigidBody
{
public:
	/**
	 * The default constructor.
	 */
	SuzanneRigidBody();
};

} // namespace physics
} // namespace clockwork
