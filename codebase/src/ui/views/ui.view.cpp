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
#include "ui.view.hh"

using clockwork::ui::GUIView;


GUIView::GUIView(clockwork::ui::UserInterface& ui, const QString& toolTip) :
GUIComponent(ui),
_visibilityToggle(new QCheckBox(toolTip, this)) //TODO Use icons instead of titles.
{
   assert(_visibilityToggle != nullptr);
   connect(_visibilityToggle, SIGNAL(clicked(bool)), this, SLOT(setVisible(bool)));

   _visibilityToggle->setToolTip(toolTip);
   _visibilityToggle->setStyleSheet("QCheckBox { background:#fff }");
}


QCheckBox&
GUIView::getVisibilityToggle()
{
   return *_visibilityToggle;
}


void
GUIView::setVisible(const bool visible)
{
   QWidget::setVisible(visible);
   _visibilityToggle->setChecked(visible);
}
