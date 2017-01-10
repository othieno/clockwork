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
#ifndef CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH
#define CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH

#include "SceneObjectProperty.hh"


namespace clockwork {
/**
 * @see graphics/Mesh.hh.
 */
class Mesh;
/**
 *
 */
class SceneObjectAppearance : public SceneObjectProperty {
	friend class SceneObject;
public:
	/**
	 *
	 */
	SceneObjectAppearance(const SceneObjectAppearance&) = delete;
	/**
	 *
	 */
	SceneObjectAppearance(SceneObjectAppearance&&) = delete;
	/**
	 *
	 */
	SceneObjectAppearance& operator=(const SceneObjectAppearance&) = delete;
	/**
	 *
	 */
	SceneObjectAppearance& operator=(SceneObjectAppearance&&) = delete;
	/**
	 * Returns true if the property has a non-empty polygon mesh, false otherwise.
	 * A polygon mesh is considered empty if it has no faces and vertices.
	 */
	bool hasMesh() const;
	/**
	 * Returns the polygon mesh.
	 */
	const Mesh* getMesh() const;
	/**
	 * Sets the property's polygon mesh.
	 * @param mesh the polygon mesh to set.
	 */
	void setMesh(const Mesh& mesh);
	/**
	 * Sets the property's polygon mesh.
	 * @param filename a name of the file containing the polygon mesh.
	 */
	void setMesh(const QString& filename);
	/**
	 * Unsets the property's polygon mesh.
	 */
	void removeMesh();
private:
	/**
	 * Instantiates a SceneObjectAppearance object.
	 */
	SceneObjectAppearance();
	/**
	 * A polygon mesh.
	 */
	const Mesh* mesh_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH
