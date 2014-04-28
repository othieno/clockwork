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
#include "scene.hh"
#include "services.hh"
#include "predefs.hh"
#include "camera.hh"
#include <cassert>

using clockwork::scene::Scene;
using clockwork::scene::Viewer;


Scene::Scene() :
QAbstractItemModel(nullptr),
_graph(new Object("Default Scene Graph")),
_doViewportUpdate(true)
{
   assert(_graph != nullptr);

   auto* const suzanne = &clockwork::scene::predefs::Suzanne::getInstance();
   std::list<clockwork::graphics::Camera*> cameras =
   {
      new clockwork::graphics::Camera("Camera A"),
//      new clockwork::graphics::Camera("Camera B"),
//      new clockwork::graphics::Camera("Camera C"),
//      new clockwork::graphics::Camera("Camera D")
   };

   _graph->addChild(suzanne);
   for (auto* const camera : cameras)
   {
      _graph->addChild(camera);
      activateViewer(*camera);
   }
}


Scene&
Scene::getInstance()
{
   static Scene INSTANCE;
   return INSTANCE;
}


clockwork::scene::Object&
Scene::getGraph()
{
   return *_graph;
}


const QSet<Viewer*>&
Scene::getActiveViewers()
{
   if (_doViewportUpdate)
      updateViewports();


   return _activeViewers;
}


void
Scene::activateViewer(Viewer& viewer)
{
   _activeViewers.insert(&viewer);
   _doViewportUpdate = true;
}


void
Scene::deactivateViewer(Viewer& viewer)
{
   _activeViewers.remove(&viewer);
   _doViewportUpdate = true;
}


bool
Scene::hasActiveViewers() const
{
   return !_activeViewers.empty();
}


void
Scene::updateViewports()
{
   auto it = _activeViewers.begin();

   const unsigned nActiveViewers = _activeViewers.size();
   if (nActiveViewers > 1)
   {
      // TODO Explain me more.
      // If  there is more than one active viewer, then the viewport is
      // partitioned to accomodate each viewer.
      const unsigned int M = static_cast<unsigned int>(std::ceil(nActiveViewers / 2.0));
      const unsigned int N = nActiveViewers - M;

      for (unsigned int i = 0; i < M; ++i)
      {
         const float w = 1.0f / M;
         (*it++)->setViewport(i * w, 0.0f, w, 0.5f);
      }
      for (unsigned int i = 0; i < N; ++i)
      {
         const float w = 1.0f / N;
         (*it++)->setViewport(i * w, 0.5f, w, 0.5f);
      }
   }
   else
      (*it)->setViewport(0.0f, 0.0f, 1.0f, 1.0f);

   _doViewportUpdate = false;
}


void
Scene::save(const QString&) const
{}


QModelIndex
Scene::index(const int row, const int column, const QModelIndex& parent) const
{
   const Object* const object =
   !parent.isValid() ? _graph : static_cast<const Object*>(parent.internalPointer());
   assert(object != nullptr);

   const auto& children = object->getChildren();
   const auto& hasModel = !children.isEmpty() && row < children.count();

   return !hasModel ? QModelIndex() : createIndex(row, column, *(children.begin() + row));
}


QModelIndex
Scene::parent(const QModelIndex& index) const
{
   if (index.isValid())
   {
      const auto* const node = static_cast<const Object*>(index.internalPointer());
      const auto* const parent = node->parent();
      if (parent != nullptr && parent != _graph)
      {
         const auto* const grandParent = parent->parent();
         if (grandParent != nullptr)
         {
            const auto& indexOfParent = grandParent->children().indexOf(const_cast<QObject*>(parent));
            return createIndex(indexOfParent, 0, (void*)parent);
         }
      }
   }
   return QModelIndex();
}


int
Scene::rowCount(const QModelIndex& index) const
{
   const Object* parent = _graph;
   if (index.isValid())
   {
      parent = static_cast<const Object*>(index.internalPointer());
      assert(parent != nullptr);
   }
   return parent->getChildren().count();
}


QVariant
Scene::data(const QModelIndex& index, const int role) const
{
   if (index.isValid())
   {
      if (role == Qt::DisplayRole)
         return static_cast<Object*>(index.internalPointer())->getName();
      else if (role == Qt::ToolTipRole)
         return QString("Select a scene entity.");
   }
   return QVariant();
}


QVariant
Scene::headerData(const int, const Qt::Orientation orientation, const int role) const
{
   return (role == Qt::DisplayRole && orientation == Qt::Horizontal) ? _graph->getName() : QVariant();
}
