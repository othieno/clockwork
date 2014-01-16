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
#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include "scene.node.hh"


namespace clockwork {
namespace scene {

/**
 * @see scene.object.hh.
 */
class Object;

/**
 * @see scene.viewer.hh.
 */
class Viewer;

class Scene : public QAbstractItemModel
{
Q_OBJECT
public:
   /**
    * Return the scene's unique instance.
    */
   static Scene& getUniqueInstance();
   /**
    * Return the scene's title.
    */
   const QString getTitle() const;
   /**
    * Set the scene's title.
    * @param title the title to set.
    */
   void setTitle(const QString& title);
   /**
    * Return the current viewer.
    */
   clockwork::scene::Viewer* getViewer();
   /**
    * Set the current viewer.
    * @param viewer the scene viewer to set.
    */
   void setViewer(Viewer& viewer);
   /**
    * Remove the viewer that is currently set.
    */
   void removeViewer();
   /**
    * Return true if the scene has a viewer, false otherwise.
    */
   bool hasViewer() const;
   /**
    * Add an object to the scene.
    * @param object the object to add.
    */
   void addObject(Object* const object);
   /**
    * Return the root nodes.
    */
   std::set<Node*>& getRootNodes();
   /**
    * Remove all entities from the scene.
    */
   void clear();
   /**
    * Save the scene to a JSON file.
    */
   void save() const;
   /**
    * Convert the scene into a set of renderer jobs. This method traverses the
    * scene's entities while adding anything that can be rendered to a renderer's
    * job queue in the form of a renderer job to be processed by the renderer.
    */
   void render();
   /**
    * @see QAbstractItemModel::index.
    */
   virtual QModelIndex index(const int, const int, const QModelIndex& = QModelIndex()) const override final;
   /**
    * @see QAbstractItemModel::parent.
    */
   virtual QModelIndex parent(const QModelIndex&) const override final;
   /**
    * @see QAbstractItemModel::rowCount.
    */
   virtual int rowCount(const QModelIndex& = QModelIndex()) const override final;
   /**
    * @see QAbstractItemModel::columnCount.
    */
   virtual int columnCount(const QModelIndex& = QModelIndex()) const override final;
   /**
    * @see QAbstractItemModel::data.
    */
   virtual QVariant data(const QModelIndex&, const int) const override final;
   /**
    * @see QAbstractItemModel::headerData.
    */
   virtual QVariant headerData(const int, const Qt::Orientation = Qt::Horizontal, const int = Qt::DisplayRole) const override final;
   // The constructor is temporarily public.
   Scene();
private:
   /**
    * The Scene is a singleton object so no other instances of this class should be
    * created. As such, its constructor is hidden, and its copy constructor and
    * operator are deleted.
    */
   //Scene();
   Scene(const Scene&) = delete;
   Scene& operator=(const Scene&) = delete;
   /**
    * The current scene viewer.
    */
   Viewer* _currentViewer;
   /**
    * The root nodes.
    */
   std::set<Node*> _rootNodes;
};

} // namespace scene
} // namespace clockwork
