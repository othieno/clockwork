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
#pragma once

#include "ui.component.hh"
#include <QComboBox>
#include "tostring.hh"


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
   /**
    * Set the selected item.
    * @param item the item to select.
    */
   template<typename ItemType, typename UserDataType>
   void setSelectedItem(const ItemType& item)
   {
      setSelectedItem(_qComboBox->findData(static_cast<UserDataType>(item)));
   }
protected:
   /**
    * Instantiate a GUIComboBox with a given description, that is attached
    * to a user interface.
    * @param ui the user interface that this component is attached to.
    * @param description the combo box's description.
    */
   GUIComboBox(UserInterface& ui, const QString& description);
   /**
    * Instantiate a GUIComboBox with a given description, a specified
    * list of items, and that is attached to a user interface.
    * @param ui the user interface that this component is attached to.
    * @param description the combo box's description.
    * @param items the combo box's item list.
    */
   GUIComboBox(UserInterface& ui, const QString& description, const QStringList& items);
   /**
    * Build the combo box.
    * @param items the combo box's items.
    * @param defaultItem the item that will be selected by default.
    */
   template<typename ItemType, typename UserDataType>
   void build(const QList<ItemType>& items, const ItemType& defaultItem)
   {
      if (!items.isEmpty())
      {
         // Block all signals while the combo box is being created. This prevents
         // the componentChanged signal from being raised while elements are being
         // inserted into the combo box.
         _qComboBox->blockSignals(true);

         int selectedIndex = 0;

         // Add the items to the combo box.
         for (const auto& item : items)
         {
            const auto& itemText = clockwork::toString(item);
            const auto& itemUserData = static_cast<UserDataType>(item);

            // Add the item to the combo box.
            const auto& itemIndex = addItem(itemText, itemUserData);

            // Get the index of the current item.
            if (item == defaultItem)
               selectedIndex = itemIndex;
         }
         setSelectedItem(selectedIndex);

         // Re-activate all signals.
         _qComboBox->blockSignals(false);
      }
   }
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
