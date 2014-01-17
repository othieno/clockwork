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
#include "ui.combobox.image.filter.hh"
#include "scene.hh"
#include "services.hh"
#include "image.filter.factory.hh"

using clockwork::ui::GUIImageFilterComboBox;
using ItemType = clockwork::graphics::ImageFilter::Type;
using UserDataType = std::underlying_type<ItemType>::type;


GUIImageFilterComboBox::GUIImageFilterComboBox(UserInterface& ui) :
GUIComboBox(ui, "Image Filter")
{
   const auto& factory = clockwork::graphics::ImageFilterFactory::getUniqueInstance();
   const auto& items = factory.getKeys();
   const auto& defaultItem = factory.getDefaultKey();

   // Build the combo box.
   build<ItemType, UserDataType>(items, defaultItem);
}


void
GUIImageFilterComboBox::onItemSelected(const int& index)
{
   // Get the selected image filter type and update the framebuffer with it.
   clockwork::system::Services::Graphics.setImageFilter(getItem<ItemType>(index));
}
