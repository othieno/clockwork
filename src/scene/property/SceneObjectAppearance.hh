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
#ifndef CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH
#define CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH

#include "SceneObjectProperty.hh"


namespace clockwork {
/**
 *
 */
class Material;
/**
 *
 */
class Model3d;
/**
 *
 */
class SceneObjectAppearance : public SceneObjectProperty {
public:
	/**
	 * Instantiates a SceneObjectAppearance object attached to a given owner.
	 * @param owner the property's owner.
	 */
	explicit SceneObjectAppearance(SceneObject&);
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
	 * Returns the 3D model.
	 */
	const Model3d* getModel() const;
	/**
	 * Sets the property's 3D model.
	 * @param model the 3D model to set.
	 */
	void setModel(const Model3d& model);
	/**
	 * Sets the property's 3D model.
	 * @param filename a name of the file containing the 3D model.
	 */
	void setModel(const QString& filename);
	/**
	 * Unsets the property's 3D model.
	 */
	void removeModel();
	/**
	 * Returns the material.
	 */
	const Material* getMaterial() const;
	/**
	 * Sets the property's material.
	 * @param material the material to set.
	 */
	void setMaterial(const Material& material);
	/**
	 * Sets the property's material.
	 * @param filename a name of the file containing the material.
	 */
	void setMaterial(const QString& filename);
	/**
	 * Unsets the property's material.
	 */
	void removeMaterial();
private:
	/**
	 * A 3D model.
	 */
	const Model3d* model_;
	/**
	 * A material, i.e. the 3D model's look-and-feel.
	 */
	const Material* material_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_OBJECT_APPEARANCE_HH
