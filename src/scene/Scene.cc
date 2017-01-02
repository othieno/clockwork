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
#include "Scene.hh"
#include "Suzanne.hh"
#include "Camera.hh"

using clockwork::Scene;


Scene::Scene() :
viewer_(nullptr) {
	//TODO Remove this when done debugging.
	setViewer(SceneViewer::Type::Camera);
	addNode(new asset::Suzanne());
}


clockwork::SceneNode*
Scene::getNode(const QString& name) {
	return findChild<SceneNode*>(name, Qt::FindDirectChildrenOnly);
}


void
Scene::addNode(SceneNode* const node) {
	if (node != nullptr && node->parent() != this) {
		node->setParent(this);
		connect(node, &SceneNode::nodeChanged, this, &Scene::update);
	}
}


void
Scene::removeNode(const QString&) {
	qFatal("[Scene::removeNode] Implement me!");
}


clockwork::SceneViewer*
Scene::getViewer() {
	return viewer_.get();
}


const clockwork::SceneViewer*
Scene::getViewer() const {
	return viewer_.get();
}


void
Scene::setViewer(const SceneViewer::Type type) {
	switch (type) {
		case SceneViewer::Type::Camera:
			viewer_.reset(new Camera("Default Camera"));
			break;
		default:
			qWarning("[Scene::setViewer] Unknown SceneViewer type!");
			viewer_.reset(nullptr);
			break;
	}
	emit viewerChanged(viewer_.get());
}


void
Scene::update() {
}
