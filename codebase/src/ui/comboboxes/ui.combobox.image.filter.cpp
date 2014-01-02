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


clockwork::ui::GUIImageFilterComboBox::GUIImageFilterComboBox(UserInterface& ui) :
GUIComboBox(ui, "Image Filter")
{
	// Build the combo box.
	build();
}


void
clockwork::ui::GUIImageFilterComboBox::loadItemList()
{
	const auto& factory = clockwork::graphics::ImageFilterFactory::getUniqueInstance();
	const auto& keys = factory.getKeys();
	const auto& defaultKey = factory.getDefaultKey();
	int defaultIndex = 0;

	// Add the keys as items to the combo box.
	for (const auto& key : keys)
	{
		using UserDataType = std::underlying_type<clockwork::graphics::ImageFilter::Type>::type;

		const auto& text = QString(clockwork::toString(key).c_str());
		const auto& userData = static_cast<UserDataType>(key);

		// Add the item to the combo box.
		const auto& itemIndex = addItem(text, userData);

		// Get the index of the current item.
		if (key == defaultKey)
			defaultIndex = itemIndex;
	}
	setSelectedItem(defaultIndex);
}


void
clockwork::ui::GUIImageFilterComboBox::onItemSelected(const int& index)
{
	// Get the selected image filter type and update the framebuffer with it.
	const auto& type = getItem<clockwork::graphics::ImageFilter::Type>(index);
	clockwork::system::Services::Graphics.setImageFilter(type);
}
