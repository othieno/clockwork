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
#include "ui.combobox.texture.filter.hh"
#include "scene.hh"
#include "scene.viewer.hh"
#include "texture.filter.factory.hh"
#include "texture.render.parameters.hh"
#include "render.parameters.factory.hh"

using clockwork::ui::GUITextureFilterComboBox;
using clockwork::graphics::RenderParameters;
using clockwork::graphics::RenderParametersFactory;
using clockwork::graphics::TextureRenderParameters;
using ItemType = clockwork::graphics::TextureFilter::Type;
using UserDataType = std::underlying_type<ItemType>::type;


GUITextureFilterComboBox::GUITextureFilterComboBox(UserInterface& ui) :
GUIComboBox(ui, "Texture Filter"),
_renderParameters(static_cast<TextureRenderParameters*>(RenderParametersFactory::getUniqueInstance().get(RenderParameters::Type::Texture)))
{
   const auto& factory = clockwork::graphics::TextureFilterFactory::getUniqueInstance();
   const auto& items = factory.getKeys();
   const auto& defaultItem = factory.getDefaultKey();

   // Build the combo box.
   build<ItemType, UserDataType>(items, defaultItem);
}


void
GUITextureFilterComboBox::onInterfaceUpdate(const clockwork::ui::GUIComponent* const source)
{
   if (source != this)
   {
      // The texture filter combo box is only visible if the current renderer is
      // set to Renderer::Type::Texture and enabled if a scene viewer is set.
      bool isEnabled = false;
      bool isVisible = false;
      auto* const viewer = clockwork::scene::Scene::getUniqueInstance().getViewer();
      if (viewer != nullptr)
      {
         isEnabled = true;
         isVisible = clockwork::graphics::RenderParameters::Type::Texture == viewer->getRenderType();
      }
      setEnabled(isEnabled);
      setVisible(isVisible);
   }
}


void
GUITextureFilterComboBox::onItemSelected(const int& index)
{
   if (_renderParameters != nullptr)
      _renderParameters->setTextureFilter(getItem<ItemType>(index));
}
