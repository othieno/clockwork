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
#pragma once

#include "ui.component.hh"
#include <QComboBox>


namespace clockwork {
namespace ui {

class GUIComboBox : public GUIComponent
{
Q_OBJECT
public:
	/**
	 * Return the currently selected item.
	 */
	template<typename ItemType>
	ItemType getSelectedItem()
	{
		return getItem<ItemType>(_qComboBox->currentIndex());
	}
	/**
	 * Return the item at the given index.
	 * @param index the index to query.
	 */
	template<typename ItemType>
	ItemType getItem(const int& index)
	{
		return static_cast<ItemType>(_qComboBox->itemData(index).toInt());
	}
	/**
	 * Set the selected item based on a given index.
	 * @param index the index of the item to select.
	 */
	void setSelectedItem(const int& index);
protected:
	/**
	 * Instantiate a labeled GUIComboBox that is attached to a user interface.
	 * @param ui the user interface that this component is attached to.
	 * @param label the combo box's label.
	 */
	GUIComboBox(UserInterface& ui, const std::string& label);
	/**
	 * Instantiate a labeled GUIComboBox with a given list of items,
	 * that is attached to a user interface.
	 * @param ui the user interface that this component is attached to.
	 * @param label the combo box's label.
	 * @param items the combo box's item list.
	 */
	GUIComboBox(UserInterface& ui, const std::string& label, std::list<std::string> items);
	/**
	 * Load the combo box's items.
	 */
	virtual void loadItemList() = 0;
	/**
	 * Add an item to the combo box and return its index.
	 * @param text the item's text.
	 * @param userData the item's user data.
	 */
	int addItem(const QString& text, const QVariant& userData);
	/**
	 * @see GUIComponent::onInterfaceUpdate.
	 */
	virtual void onInterfaceUpdate(const GUIComponent* const) override;
	/**
	 * The event handler for when a new item is selected.
	 * @param index the index of the currently selected item.
	 */
	virtual void onItemSelected(const int& index) = 0;
	/**
	 * Build the combo box.
	 */
	void build();
private:
	/**
	 * The actual combobox.
	 */
	QComboBox* const _qComboBox;
private slots:
	/**
	 * The event handler for when the current index changes.
	 * @param index the index of the currently selected item.
	 */
	void onCurrentIndexChanged(const int& index);
};
} // namespace ui
} // namespace clockwork
