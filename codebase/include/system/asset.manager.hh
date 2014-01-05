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

#include "rigid.body.hh"


namespace clockwork {
namespace system {

class AssetManager
{
friend class Services;
public:
	/**
	 * Load a 3D model from a given file and store its mesh and material
	 * data in a rigid body data structure. If a 3D model has already been
	 * loaded, then no load operations are performed and the 3D model in
	 * memory is returned. This behavior can be changed if the 'forceReload' flag
	 * is set to true.
	 * @param filename the name of the file containing the 3D model.
	 * @param body the rigid body container where the mesh and material data will be stored.
	 * @param forceReload true to reload mesh and material data, false otherwise.
	 */
	void load3DModel
	(
		const std::string& filename,
		clockwork::physics::RigidBody& body,
		const bool forceReload = false
	);
private:
	/**
	 * The AssetManager is a singleton object so only a single instance of this
	 * class should be created. To prevent copying and accidental instantiation,
	 * the constructor is hidden (accessible only by the Services class),
	 * and its copy constructor and operator are deleted.
	 */
	AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;
};

} // namespace system
} // namespace clockwork
