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
#include "SceneNode.hh"

using clockwork::SceneNode;


SceneNode::SceneNode(const Type type, SceneNode* const parent, const QString& name) :
QObject(parent),
identifier_(QUuid::createUuid()),
type_(type),
isPruned_(false) {
	setObjectName(name);

	connect(this, &QObject::objectNameChanged, this, &SceneNode::nodeChanged);
	connect(this, &SceneNode::nodePruned,      this, &SceneNode::nodeChanged);
}


const QUuid&
SceneNode::getUniqueIdentifier() const {
	return identifier_;
}


SceneNode::Type
SceneNode::getNodeType() const {
	return type_;
}


bool
SceneNode::hasParent() const {
	return QObject::parent() != nullptr;
}


const SceneNode*
SceneNode::getParent() const {
	return static_cast<const SceneNode*>(parent());
}


QString
SceneNode::getName() const {
	return objectName();
}


void
SceneNode::setName(const QString& name) {
	setObjectName(name);
}


bool
SceneNode::isPruned() const {
    return isPruned_;
}


void
SceneNode::setPruned(const bool pruned) {
	if (isPruned_ != pruned) {
		isPruned_ = pruned;
		emit nodePruned(isPruned_);
	}
}


void
SceneNode::update() {
	for (SceneNode* const node : getChildren<SceneNode>()) {
		node->update();
	}
}


void
SceneNode::addChild(SceneNode* const node) {
	if (node != nullptr) {
		node->setParent(this);
	}
}


void
SceneNode::removeChild(SceneNode* const node) {
	if (isChild(node)) {
		node->removeParent();
		node->deleteLater();
	}
}


bool
SceneNode::isChild(const SceneNode* const node) const {
	return node != nullptr && node->parent() == this;
}


void
SceneNode::removeParent() {
	if (hasParent()) {
		QObject::setParent(nullptr);
		disconnect();
	}
}
