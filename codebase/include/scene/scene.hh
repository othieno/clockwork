/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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
#include <QSet>
#include "scene.object.hh"


namespace clockwork {
namespace scene {

/**
 * @see scene.viewer.hh.
 */
class Viewer;

/**
 * The scene graph.
 */
class Scene : public QAbstractItemModel
{
public:
   /**
    * Return the scene's unique instance.
    */
   static Scene& getInstance();
   /**
    * Return the scene graph.
    */
   Object& getGraph();
   /**
    * Return the set of active viewers.
    */
   const QSet<Viewer*>& getActiveViewers();
   /**
    * Activate a viewer. When a viewer is activated, it receives
    * requests to render the scene from its viewpoint.
    * @param viewer the viewer to activate.
    */
   void activateViewer(Viewer& viewer);
   /**
    * Deactivate a viewer.
    * @param viewer the viewer to deregister.
    */
   void deactivateViewer(Viewer& viewer);
   /**
    * Return true if the scene has at least one active viewer, false otherwise.
    */
   bool hasActiveViewers() const;
   /**
    * Save the scene to a JSON file.
    * @param filename the name of the JSON file.
    */
   void save(const QString& filename) const;
   /**
    * @see QAbstractItemModel::index.
    */
   QModelIndex index(const int, const int, const QModelIndex& = QModelIndex()) const override final;
   /**
    * @see QAbstractItemModel::parent.
    */
   QModelIndex parent(const QModelIndex&) const override final;
   /**
    * @see QAbstractItemModel::rowCount.
    */
   int rowCount(const QModelIndex& = QModelIndex()) const override final;
   /**
    * @see QAbstractItemModel::columnCount.
    */
   inline int columnCount(const QModelIndex& = QModelIndex()) const override final { return 1; }
   /**
    * @see QAbstractItemModel::data.
    */
   QVariant data(const QModelIndex&, const int) const override final;
   /**
    * @see QAbstractItemModel::headerData.
    */
   QVariant headerData(const int, const Qt::Orientation = Qt::Horizontal, const int = Qt::DisplayRole) const override final;
private:
   /**
    * The Scene is a singleton.
    */
   Scene();
   Scene(const Scene&) = delete;
   Scene& operator=(const Scene&) = delete;
   /**
    * The scene graph.
    */
   Object* const _graph;
   /**
    * The set of active viewers.
    */
   QSet<Viewer*> _activeViewers;
   /**
    * When true, this signals that each active viewer's viewport needs to be updated.
    */
   bool _doViewportUpdate;
   /**
    * Update the viewports of each activated viewer.
    */
   void updateViewports();
};

} // namespace scene
} // namespace clockwork
