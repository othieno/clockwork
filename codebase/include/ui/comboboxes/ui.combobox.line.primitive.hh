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

#include "ui.combobox.hh"
#include "line.render.parameters.hh"


namespace clockwork {
namespace ui {

class GUILinePrimitiveComboBox : public GUIComboBox
{
public:
   /**
    * Instantiate a GUILinePrimitiveComboBox attached to a user interface.
    * @param ui the user interface that this component is attached to.
    */
   GUILinePrimitiveComboBox(UserInterface& ui);
   /**
    * @see GUIComponent::onInterfaceUpdate.
    */
   virtual void onInterfaceUpdate(const GUIComponent* const) override final;
private:
   /**
    * An instance to the line render parameters.
    */
   clockwork::graphics::LineRenderParameters* const _renderParameters;
   /**
    * @see GUIComboBox::onItemSelected.
    */
   void onItemSelected(const int&) override final;
};

} // namespace ui
} // namespace clockwork
