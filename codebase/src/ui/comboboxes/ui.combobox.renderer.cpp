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
#include "ui.hh"
#include "ui.combobox.renderer.hh"
#include "render.parameters.factory.hh"
#include "scene.hh"
#include "scene.viewer.hh"

using clockwork::ui::GUIRendererComboBox;
using ItemType = clockwork::graphics::RenderParameters::Type;
using UserDataType = std::underlying_type<ItemType>::type;


GUIRendererComboBox::GUIRendererComboBox(UserInterface& ui) :
GUIComboBox(ui, "Renderer")
{
   auto& factory = clockwork::graphics::RenderParametersFactory::getUniqueInstance();
   const auto& items = factory.getKeys();
   const auto& defaultItem = factory.getDefaultKey();

   // Build the combo box.
   build<ItemType, UserDataType>(items, defaultItem);
}


void
GUIRendererComboBox::onItemSelected(const int& index)
{
   // Set the current viewer's renderer.
   auto* const viewer = clockwork::scene::Scene::getUniqueInstance().getViewer();
   if (viewer != nullptr)
      viewer->setRenderType(getItem<ItemType>(index));
}
