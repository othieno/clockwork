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
#ifndef CLOCKWORK_SCENE_HH
#define CLOCKWORK_SCENE_HH

#include "SceneViewer.hh"


namespace clockwork {
/**
 * @see system/Application.hh.
 */
class Application;
/**
 *
 */
class Scene : public QObject {
	friend class Application;
public:
	/**
	 *
	 */
	Scene(const Scene&) = delete;
	/**
	 *
	 */
	Scene(Scene&&) = delete;
	/**
	 *
	 */
	Scene& operator=(const Scene&) = delete;
	/**
	 *
	 */
	Scene& operator=(Scene&&) = delete;
	/**
	 * Returns the instance of the SceneNode with the specified name if it exists,
	 * nullptr otherwise.
	 * @param name a node's name.
	 */
	SceneNode* getNode(const QString& name);
	/**
	 * Returns all scene nodes of a given Node type.
	 */
	template<class Node> QList<Node*> getAllNodes() {
		static_assert(std::is_base_of<SceneNode, Node>::value);
		return findChildren<Node*>(QString(), Qt::FindDirectChildrenOnly);
	}
	/**
	 * Adds the specified node to the scene.
	 * The scene will claim ownership of the node, i.e. it will automatically
	 * destroy the node in its destructor.
	 * @param node a SceneNode to add to the scene.
	 */
	void addNode(SceneNode* const node);
	/**
	 * Removes a node with the specified name from the scene.
	 * @param name the name of the node to remove.
	 */
	void removeNode(const QString& name);
	/**
	 * Returns the SceneViewer instance.
	 */
	SceneViewer* getViewer();
	/**
	 * Sets the type of SceneViewer.
	 * @param type the SceneViewer type to set.
	 */
	//void setViewer(const SceneViewer::Type type);
private:
	/**
	 * Instantiates a Scene object.
	 */
	Scene();
	/**
	 * The scene viewer.
	 */
	std::unique_ptr<SceneViewer> viewer_;
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_HH
