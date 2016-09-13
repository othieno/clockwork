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
#ifndef CLOCKWORK_SCENE_NODE_HH
#define CLOCKWORK_SCENE_NODE_HH

#include <QObject>
#include <QUuid>
#include <QSet>


namespace clockwork {
/**
 *
 */
class SceneNode : public QObject
{
public:
	/**
	 * Returns the node's unique identifier.
	 */
	const QUuid& getIdentifier() const;
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
protected:
	/**
	 * Instantiates a named scene node.
	 * @param name the scene node's name.
	 */
	explicit SceneNode(const QString& name);
	/**
	 * Returns true if the node has at least one child, false otherwise.
	 */
	bool hasChildren() const;
	/**
	 * Return the node's children.
	 */
	const QSet<SceneNode*>& getChildren() const;
	/**
	 * Add a child node.
	 * @param node the child node to add.
	 */
	void addChild(SceneNode* const node);
	/**
	 * Remove a child node.
	 * @param node the child node to remove.
	 */
	void removeChild(SceneNode* const node);
private:
	/**
	 * The scene node's unique identifier.
	 */
	const QUuid identifier_;
	/**
	 * If set to true, this node will be skipped by certain operations performed on the
	 * scene. For example, if this is a node that is out of view, it will be pruned so
	 * that the renderer does not waste time on an otherwise invisible object.
	 */
	bool isPruned_;
	/**
	 * The node's children.
	 */
	QSet<SceneNode*> children_;
#ifdef TO_IMPLEMENT
protected:
	/**
	* Add a property and return its instance.
	* @param identifier the property identifier.
	*/
	Property& addProperty(const Property::Identifier& identifier);
	/**
	* Return the property with the specified identifier.
	* @param identifier the property identifier.
	*/
	const Property* getProperty(const Property::Identifier& identifier) const;
	/**
	* Return true if the object has the specified property, false otherwise.
	* @param identifier the identifier of the property to query.
	*/
	bool hasProperty(const Property::Identifier& identifier) const;
	/**
	* Remove a property.
	* @param identifier the identifier of the property to remove.
	*/
	void removeProperty(const Property::Identifier& identifier);
private:
	/**
	* The object's properties.
	*/
	QHash<unsigned int, Property*> _properties;
#endif // TO_IMPLEMENT
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_NODE_HH
