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
#include "ui.view.scene.hh"
#include "scene.hh"
#include <QVBoxLayout>

using clockwork::ui::GUISceneView;


GUISceneView::GUISceneView(clockwork::ui::UserInterface& ui) :
GUIView(ui, "Show scene hierarchy"),
_treeView(new QTreeView(this))
{
   assert(_treeView != nullptr);
   connect(_treeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onClicked(const QModelIndex&)));
   setVisible(false);
}


void
GUISceneView::build()
{
   // Block all signals until the component is built.
   _treeView->blockSignals(true);

   QVBoxLayout* const layout = new QVBoxLayout(this);
   layout->addWidget(_treeView);
   setLayout(layout);
   setMinimumWidth(400);
   setMaximumWidth(400);

   QAbstractItemModel& model = clockwork::scene::Scene::getInstance();
   _treeView->setModel(&model);

   const auto& index = model.index(0, 0);
   _treeView->setCurrentIndex(index);
   onClicked(index);

   _treeView->blockSignals(false);
}


void
GUISceneView::onClicked(const QModelIndex& index)
{
   GUIComponent::SelectedSceneObject = static_cast<clockwork::scene::Object*>(index.internalPointer());
   assert(GUIComponent::SelectedSceneObject != nullptr);

   emit componentStateChanged(this);
}
