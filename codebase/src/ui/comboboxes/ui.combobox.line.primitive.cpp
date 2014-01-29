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
#include "ui.combobox.line.primitive.hh"
#include "render.parameters.factory.hh"
#include "scene.hh"
#include "scene.viewer.hh"
#include "services.hh"

using clockwork::ui::GUILinePrimitiveComboBox;
using clockwork::graphics::RenderParameters;
using clockwork::graphics::RenderParametersFactory;
using clockwork::graphics::LineRenderParameters;
using ItemType = LineRenderParameters::LinePrimitive;
using UserDataType = std::underlying_type<ItemType>::type;


GUILinePrimitiveComboBox::GUILinePrimitiveComboBox(UserInterface& ui) :
GUIComboBox(ui, "Primitive"),
_renderParameters(static_cast<LineRenderParameters*>(RenderParametersFactory::getUniqueInstance().get(RenderParameters::Type::Line)))
{
   // Build the combo box.
   if (_renderParameters != nullptr)
   {
      const auto& items = _renderParameters->getLinePrimitives();
      const auto& defaultItem = _renderParameters->getLinePrimitive();

      // Build the combo box.
      build<ItemType, UserDataType>(items, defaultItem);
   }
}


void
GUILinePrimitiveComboBox::onInterfaceUpdate(const clockwork::ui::GUIComponent* const source)
{
   if (source != this)
   {
      // The line algorithm combo box is only visible if the current renderer is
      // set to Renderer::Type::Wireframe, and enabled if a scene viewer is set.
      bool isEnabled = false;
      bool isVisible = false;
      auto* const viewer = clockwork::scene::Scene::getUniqueInstance().getViewer();
      if (viewer != nullptr)
      {
         isEnabled = true;
         isVisible = clockwork::graphics::RenderParameters::Type::Line == viewer->getRenderType();
      }
      setEnabled(isEnabled);
      setVisible(isVisible);
   }
}


void
GUILinePrimitiveComboBox::onItemSelected(const int& index)
{
   if (_renderParameters != nullptr)
      _renderParameters->setLinePrimitive(getItem<ItemType>(index));
}
