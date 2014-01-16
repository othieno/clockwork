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
#include "scene.node.hh"
#include "scene.hh"
#include <iostream> // Remove when done debugging.


clockwork::scene::Node::Node(const std::string& name) :
QObject(&clockwork::scene::Scene::getUniqueInstance()),
_isNameEditable(true),
_isPruned(false)
{
	setObjectName(QString(name.c_str()));
}


const QString
clockwork::scene::Node::getName() const
{
	return objectName();
}


void
clockwork::scene::Node::setName(const QString& name)
{
	setObjectName(name);
}


void
clockwork::scene::Node::addChild(clockwork::scene::Node* const node)
{
	if (node != nullptr)
		_children.insert(node);
}


void
clockwork::scene::Node::removeChild(clockwork::scene::Node* const node)
{
	if (node != nullptr)
	{
		std::cerr << "Implement clockwork::scene::Node::removeChild" << std::endl;
	}
}


const std::set<clockwork::scene::Node*>&
clockwork::scene::Node::getChildren() const
{
	return _children;
}


bool
clockwork::scene::Node::isPruned() const
{
	return _isPruned;
}


void
clockwork::scene::Node::setPruned(const bool pruned)
{
	_isPruned = pruned;
}


bool
clockwork::scene::Node::isNameEditable() const
{
	return _isNameEditable;
}


void
clockwork::scene::Node::setNameEditable(const bool editable)
{
	_isNameEditable = editable;
}


void
clockwork::scene::Node::updateGeometry(const clockwork::Matrix4& CMTM)
{
	if (!_isPruned)
	{
		for (auto* child : _children)
			child->updateGeometry(CMTM);
	}
}


void
clockwork::scene::Node::render(const clockwork::scene::Viewer& viewer) const
{
	if (!_isPruned)
	{
		for (auto* child : _children)
			child->render(viewer);
	}
}
