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
SceneNode(SceneNode::Type::Root, nullptr, "Default Scene") {
	connect(this, &Scene::nodeChanged, this, &Scene::update);
}


void
Scene::update() {
	SceneNode::update();
	emit updated();
}


clockwork::SceneNode*
Scene::getNode(const QString& name) {
	return getChild<SceneNode>(name);
}


void
Scene::removeNode(const QString& name) {
	SceneNode* const node = getNode(name);
	if (node != nullptr) {
		removeChild(node);
	}
}


clockwork::SceneViewer*
Scene::getViewer() {
	return getChild<SceneViewer>(QString());
}


const clockwork::SceneViewer*
Scene::getViewer() const {
	return getChild<const SceneViewer>(QString());
}


void
Scene::setViewer(const SceneViewer::Type type, const QString& name) {
	SceneViewer* const oldViewer = getViewer();
	if (oldViewer != nullptr) {
		if (oldViewer->getType() == type) {
			oldViewer->setName(name);
			viewerChanged(oldViewer);
			return;
		}
		removeChild(oldViewer);
	}

	SceneViewer* newViewer = nullptr;
	switch (type) {
		case SceneViewer::Type::Camera:
			newViewer = addNode<Camera>(name);
			break;
		default:
			qFatal("[Scene::setViewer] Unknown SceneViewer type!");
	}

	emit viewerChanged(newViewer);
}


void
Scene::load(const QString&) {
	// When a child is added to a node, the nodeChanged signal is emitted and
	// depending on how many nodes a scene has, this could generate quite a
	// number of redundant signals. So we block all signals while the scene
	// is being populated, reenable them when the process is done, and emit a
	// single nodeChanged signal, effectively coalescing all ignored signals.
	{
		QSignalBlocker signalBlocker(*this);

		//TODO Implement me.
		setViewer(SceneViewer::Type::Camera, "Default Camera");
		addNode<asset::Suzanne>();
	} // signalBlocker is destroyed (we've left its scope) so signals are restored.

	emit nodeChanged();
}
