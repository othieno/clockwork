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
#ifndef CLOCKWORK_SCENE_NODE_HH
#define CLOCKWORK_SCENE_NODE_HH

#include <QObject>
#include <QUuid>


namespace clockwork {
/**
 *
 */
class SceneNode : public QObject {
	Q_OBJECT
public:
	/**
	 * An enumeration of available node types.
	 */
	enum class Type {
		Root,
		Object,
		Property,
	};
	/**
	 * Returns the node's unique identifier.
	 */
	const QUuid& getUniqueIdentifier() const;
	/**
	 * Returns the node's type.
	 */
	Type getNodeType() const;
	/**
	 * Returns true if the node has a parent, false otherwise.
	 */
	bool hasParent() const;
	/**
	 * Returns the node's parent.
	 */
	const SceneNode* getParent() const;
	/**
	 * Returns the scene node's name.
	 */
	QString getName() const;
	/**
	 * Sets the scene node's name.
	 * @param name the scene node's name.
	 */
	void setName(const QString& name);
	/**
	 * Returns true if this node is pruned, false otherwise.
	 */
	bool isPruned() const;
	/**
	 * Prune this node.
	 * @param pruned true if this node is to be pruned, false otherwise.
	 */
	void setPruned(const bool pruned);
	/**
	 * Updates the node.
	 */
	virtual void update();
protected:
	/**
	 * Instantiates a named scene node.
	 * @param type the scene node's type.
	 * @param parent the scene node's parent.
	 * @param name the scene node's name.
	 */
	SceneNode(const Type type, SceneNode* const parent, const QString& name);
	/**
	 * Adds a child node.
	 * @param child the child node to add.
	 */
	void addChild(SceneNode* const child);
	/**
	 * Removes the specified child node.
	 * @param child the child node to remove.
	 */
	void removeChild(SceneNode* const child);
	/**
	 * Returns true if the specified node is a direct child of this node, false otherwise.
	 * @param node the node to query.
	 */
	bool isChild(const SceneNode* const node) const;
	/**
	 * Returns the direct child with the specified name if it exists, nullptr otherwise.
	 * @param name the name of the child node to return.
	 */
	template<class Node> Node* getChild(const QString& name) {
		static_assert(std::is_base_of<SceneNode, Node>::value);
		return findChild<Node*>(name, Qt::FindDirectChildrenOnly);
	}
	/**
	 * Returns the direct child with the specified name if it exists, nullptr otherwise.
	 * @param name the name of the child node to return.
	 */
	template<class Node> const Node* getChild(const QString& name) const {
		static_assert(std::is_base_of<SceneNode, Node>::value);
		return findChild<const Node*>(name, Qt::FindDirectChildrenOnly);
	}
	/**
	 * Returns all direct children of a given type.
	 */
	template<class Node> QList<Node*> getChildren() {
		static_assert(std::is_base_of<SceneNode, Node>::value);
		return findChildren<Node*>(QString(), Qt::FindDirectChildrenOnly);
	}
	/**
	 * Returns all direct children of a given type.
	 */
	template<class Node> QList<const Node*> getChildren() const {
		static_assert(std::is_base_of<SceneNode, Node>::value);
		return findChildren<const Node*>(QString(), Qt::FindDirectChildrenOnly);
	}
private:
	/**
	 * The scene node's unique identifier.
	 */
	const QUuid identifier_;
	/**
	 * The scene node's type.
	 */
	const Type type_;
	/**
	 * If set to true, this node will be skipped by certain operations performed on the
	 * scene. For example, if this is a node that is out of view, it will be pruned so
	 * that the renderer does not waste time on an otherwise invisible object.
	 */
	bool isPruned_;
signals:
	/**
	 * A signal that is emitted when the scene node changes.
	 */
	void nodeChanged();
	/**
	 * A signal that is emitted when the scene node's "pruned" state changes.
	 * @param pruned true if the scene node is pruned, false otherwise.
	 */
	void nodePruned(const bool pruned);
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_NODE_HH
