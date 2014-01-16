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
#include "scene.hh"
#include "camera.hh"
#include "rigid.body.hh"
#include <iostream> // remove when done debugging.


clockwork::scene::Scene::Scene() :
QAbstractItemModel(nullptr),
_currentViewer(nullptr)
{
   // Set the title.
   setTitle(QString("Scene Graph"));

   // Populate the scene.
   addObject(new clockwork::graphics::Camera("Camera 1"));
   addObject(new clockwork::graphics::Camera("Camera 2"));
   addObject(new clockwork::graphics::Camera("Camera 3"));
   addObject(new clockwork::physics::SuzanneRigidBody);
}

//FIXME This is the only way to stop the application from hanging at startup...
// WHY? It worked before. Find out what changed!
static clockwork::scene::Scene UNIQUE_INSTANCE;
clockwork::scene::Scene&
clockwork::scene::Scene::getUniqueInstance()
{
   //static clockwork::scene::Scene UNIQUE_INSTANCE;
   return UNIQUE_INSTANCE;
}


clockwork::scene::Viewer*
clockwork::scene::Scene::getViewer()
{
   return _currentViewer;
}


bool
clockwork::scene::Scene::hasViewer() const
{
   return _currentViewer != nullptr;
}


void
clockwork::scene::Scene::removeViewer()
{
   std::cerr << "Implement clockwork::scene::Scene::removeViewer" << std::endl;
}


void
clockwork::scene::Scene::addObject(clockwork::scene::Object* const object)
{
   if (object != nullptr)
   {
      _rootNodes.insert(object);

      // If the current viewer is not set and the object is a viewer,
      // then make it the default viewer.
      if (_currentViewer == nullptr)
         _currentViewer = dynamic_cast<clockwork::scene::Viewer*>(object);
   }
}


std::set<clockwork::scene::Node*>&
clockwork::scene::Scene::getRootNodes()
{
   return _rootNodes;
}


const QString
clockwork::scene::Scene::getTitle() const
{
   return objectName();
}


void
clockwork::scene::Scene::setTitle(const QString& title)
{
   setObjectName(title);
}


void
clockwork::scene::Scene::save() const
{
   std::cerr << "Implement clockwork::scene::Scene::save" << std::endl;
}


QModelIndex
clockwork::scene::Scene::index(const int row, const int column, const QModelIndex& index) const
{
   const QObject* parent = this;
   if (index.isValid())
      parent = static_cast<QObject*>(index.internalPointer());

   const auto& children = parent->children();
   if (row < children.count())
      return createIndex(row, column, children.at(row));
   else
      return QModelIndex();
}


QModelIndex
clockwork::scene::Scene::parent(const QModelIndex& index) const
{
   if (index.isValid())
   {
      const auto* const indexObject = static_cast<const QObject*>(index.internalPointer());
      auto* const parent = indexObject->parent();
      if (parent != this)
      {
         const auto indexOfParent = parent->parent()->children().indexOf(parent);
         return createIndex(indexOfParent, 0, parent);
      }
   }
   return QModelIndex();
}


int
clockwork::scene::Scene::rowCount(const QModelIndex& index) const
{
   const QObject* parent = this;
   if (index.isValid())
      parent = static_cast<const QObject*>(index.internalPointer());

   return parent->children().count();
}


int
clockwork::scene::Scene::columnCount(const QModelIndex&) const
{
   return 1;
}


QVariant
clockwork::scene::Scene::data(const QModelIndex& index, const int role) const
{
   if (index.isValid())
   {
      if (role == Qt::DisplayRole)
         return static_cast<QObject*>(index.internalPointer())->objectName();
      else if (role == Qt::ToolTipRole)
         return QString("The scene entity's name.");
   }
   return QVariant();
}


QVariant
clockwork::scene::Scene::headerData(const int, const Qt::Orientation orientation, const int role) const
{
   return (role == Qt::DisplayRole && orientation == Qt::Horizontal) ? getTitle() : QVariant();
}
