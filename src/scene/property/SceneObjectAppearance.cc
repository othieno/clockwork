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
#include "SceneObjectAppearance.hh"

using clockwork::SceneObjectAppearance;


SceneObjectAppearance::SceneObjectAppearance(SceneObject& owner) :
SceneObjectProperty(owner, SceneObjectProperty::Type::Appearance, QString()),
model_(nullptr),
material_(nullptr) {}



const clockwork::Model3d*
SceneObjectAppearance::getModel() const {
	return model_;
}


void
SceneObjectAppearance::setModel(const Model3d& model) {
	model_ = &model;
}


void
SceneObjectAppearance::setModel(const QString& filename) {
	Q_UNUSED(filename);
	qFatal("[SceneObjectAppearance::setModel] Implement me!");
	//model_ = ResourceManager::loadModel3d(filename);
}


void
SceneObjectAppearance::removeModel() {
	model_ = nullptr;
}


const clockwork::Material*
SceneObjectAppearance::getMaterial() const {
	return material_;
}


void
SceneObjectAppearance::setMaterial(const Material& material) {
	material_ = &material;
}


void
SceneObjectAppearance::setMaterial(const QString& filename) {
	Q_UNUSED(filename);
	qFatal("[SceneObjectAppearance::setMaterial] Implement me!");
	//material_ = ResourceManager::loadMaterial(filename);
}


void
SceneObjectAppearance::removeMaterial() {
	material_ = nullptr;
}
