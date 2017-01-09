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
class Scene : public SceneNode {
	Q_OBJECT
	Q_PROPERTY(SceneViewer* viewer READ getViewer NOTIFY viewerChanged)
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
	 * Updates the scene.
	 */
	void update() Q_DECL_OVERRIDE;
	/**
	 * Returns the instance of the SceneNode with the specified name if it exists,
	 * nullptr otherwise.
	 * @param name a node's name.
	 */
	SceneNode* getNode(const QString& name);
	/**
	 * Returns all scene nodes of a given Node type.
	 */
	template<class Node> QList<Node*> getNodes() {
		return getChildren<Node>();
	}
	/**
	 * Returns all scene nodes of a given Node type.
	 */
	template<class Node> QList<const Node*> getNodes() const {
		return getChildren<const Node>();
	}
	/**
	 * Adds a node of the specified Node type to the scene.
	 * The scene will claim ownership of the node meaning the node is
	 * automatically deleted during the scene's destruction.
	 * @param arguments the Node constructor's arguments.
	 */
	template<class Node, class... Arguments> Node* addNode(Arguments... arguments) {
		static_assert(std::is_base_of<SceneNode, Node>::value);

		Node* const node = new Node(*this, arguments...);
		if (node != nullptr) {
			connect(node, &SceneNode::nodeChanged, this, &Scene::update);
		}
		return node;
	}
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
	 * Returns the SceneViewer instance.
	 */
	const SceneViewer* getViewer() const;
	/**
	 * Sets the type of SceneViewer.
	 * @param type the type of scene viewer to set.
	 * @param name the scene viewer's name.
	 */
	void setViewer(const SceneViewer::Type type, const QString& name);
public slots:
	/**
	 * Loads a scene from the file with the specified file name.
	 * @param filename the name of the file containing the scene to load.
	 */
	void load(const QString& filename);
private:
	/**
	 * Instantiates a Scene object.
	 */
	Scene();
signals:
	/**
	 * A signal that is emitted when the scene has been updated.
	 */
	void updated();
	/**
	 * A signal that is emitted when the scene's viewer changes.
	 */
	void viewerChanged(SceneViewer* const viewer);
};
} // namespace clockwork

#endif // CLOCKWORK_SCENE_HH
