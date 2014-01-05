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
#include "mesh.hh"
#include "material.hh"


namespace clockwork {
namespace physics {

/**
 * A rigid body is a scene object that has a visual property.
 */
class RigidBody : public scene::Object
{
public:
	/**
	 * Instantiate a named rigid body with a given mesh and material.
	 * @param name the rigid body's name.
	 * @param mesh the rigid body's mesh data.
	 * @param material the rigid body's material data.
	 */
	RigidBody
	(
		const std::string& name,
		const clockwork::graphics::Mesh* mesh = nullptr,
		const clockwork::graphics::Material& material = nullptr
	);
	/**
	 * @see clockwork::scene::Node::render.
	 */
	virtual void render
	(
		clockwork::graphics::Renderer& renderer,
		const clockwork::scene::Viewer& viewer
	) const override final;
	/**
	 * Return the rigid body's mesh data.
	 */
	const clockwork::graphics::Mesh* getMesh() const;
	/**
	 * Set the rigid body's mesh data.
	 * @param mesh the mesh data to set.
	 */
	void setMesh(const clockwork::graphics::Mesh* mesh);
	/**
	 * Return the rigid body's material.
	 */
	const clockwork::graphics::Material& getMaterial() const;
	/**
	 * Set the rigid body's material.
	 * @param material the material to set.
	 */
	void setMaterial(const clockwork::graphics::Material& material);
	/**
	 * Convert RigidBody data into string format.
	 * @param body the rigid body to convert.
	 */
	static std::string toString(const RigidBody& body);
private:
	/**
	 * The rigid body's polygon mesh, i.e. its shape.
	 */
	const clockwork::graphics::Mesh* _mesh;
	/**
	 * The rigid body's material, i.e. its look and feel.
	 */
	clockwork::graphics::Material _material;
};

/**
 * The Suzanne rigid body used for debugging.
 */
class SuzanneRigidBody : public clockwork::physics::RigidBody
{
public:
	/**
	 * The default constructor.
	 */
	SuzanneRigidBody();
};

} // namespace physics
} // namespace clockwork
