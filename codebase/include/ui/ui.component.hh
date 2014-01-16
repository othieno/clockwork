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

#include <QWidget>


namespace clockwork {
namespace ui {

/**
 * @see ui.hh.
 */
class UserInterface;

class GUIComponent : public QWidget
{
Q_OBJECT
protected:
	/**
	 * Instantiate a GUIComponent that is attached to the user interface.
	 * @param ui the user interface that this component is attached to.
	 */
	GUIComponent(UserInterface& ui);
protected slots:
	/**
	 * This slot is called for each GUIComponent when the user interface is
	 * updating itself. It updates this component based on the state of other
	 * components in the user interface.
	 * @param source a pointer to the component that triggered the GUI update.
	 */
	virtual void onInterfaceUpdate(const GUIComponent* const source);
signals:
	/**
	 * This signal is raised when the component changes its state. This will
	 * update the entire user interface, effectively updating any components
	 * that may depend on this one.
	 * @param source a pointer to the component that changed, i.e. this component.
	 */
	void componentChanged(const GUIComponent* const source);
};

} // namespace ui
} // namespace clockwork
