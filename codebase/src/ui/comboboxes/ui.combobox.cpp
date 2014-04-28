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
#include "ui.hh"
#include "ui.combobox.hh"
#include "scene.hh"
#include <QLabel>
#include <QHBoxLayout>

using clockwork::ui::GUIComboBox;


GUIComboBox::GUIComboBox(UserInterface& ui, const QString& description) :
GUIComponent(ui),
_qComboBox(new QComboBox(this))
{
   assert(_qComboBox != nullptr);
   _qComboBox->setToolTip(description);

   auto* const layout = new QHBoxLayout(this);
   assert(layout != nullptr);

   layout->setContentsMargins(0, 0, 0, 0);
   layout->addWidget(_qComboBox);
   setLayout(layout);

   connect(_qComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(const int&)));
}


GUIComboBox::GUIComboBox(UserInterface& ui, const QString& description, const QStringList& items) :
GUIComboBox(ui, description)
{
   _qComboBox->addItems(items);
}


void
GUIComboBox::onCurrentIndexChanged(const int& index)
{
   onItemSelected(index);
   emit componentStateChanged(this);
}


void
GUIComboBox::setSelectedItem(const int& index)
{
   // Make sure the index is in a valid [min, max] range.
   const auto& maximumIndex = _qComboBox->count() - 1;
   const auto& minimumIndex = maximumIndex >= 0 ? 0 : -1;

   _qComboBox->setCurrentIndex(std::min(maximumIndex, std::max(minimumIndex, index)));
}


int
GUIComboBox::addItem(const QString& text, const QVariant& userData)
{
   const auto itemIndex = _qComboBox->count();
   _qComboBox->addItem(text, userData);

   return itemIndex;
}


void
GUIComboBox::onInterfaceUpdate(const clockwork::ui::GUIComponent* const source)
{
   if (source != this)
      setEnabled(clockwork::scene::Scene::getInstance().hasActiveViewers());
}
