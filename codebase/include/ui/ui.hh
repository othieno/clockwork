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

#include "error.hh"
#include "ui.control.panel.hh"
#include "ui.display.hh"
#include "ui.busy.indicator.hh"
#include <QMenuBar>
#include <QStatusBar>


namespace clockwork {
namespace ui {

/**
 * @see window.hh.
 */
class Window;

/**
 * TODO Explain me.
 */
class UserInterface : public QWidget
{
Q_OBJECT
public:
	/**
	 * Instantiate a user interface attached to a window.
	 * @param window the window where this interface will be rendered to.
	 */
	explicit UserInterface(Window& window);
	/**
	 * Build the user interface.
	 */
	clockwork::Error build();
	/**
	 * Return the window that this user interface is attached to.
	 */
	Window& getWindow();
private:
	/**
	 * A reference to the window where this user interface is rendered.
	 */
	Window& _window;
	/**
	 * The display device.
	 */
	GUIDisplay* const _display;
	/**
	 * The control panel.
	 */
	GUIControlPanel* const _controlPanel;
	/**
	 * The busy indicator.
	 */
	GUIBusyIndicator* const _busyIndicator;
	/**
	 * The menu bar.
	 */
	QMenuBar* const _qMenuBar;
	/**
	 * The status bar.
	 */
	QStatusBar* const _qStatusBar;
private slots:
	/**
	 * Update the user interface and the components that are attached to it.
	 * @param source the component that triggered the update.
	 */
	void update(const GUIComponent* const source);
signals:
	/**
	 * This signal is raised when the user interface's components need to
	 * be updated, which usually happens after any sort of interaction
	 * with the user interface.
	 */
	void updateComponents(const GUIComponent* const source);
};

} // namespace ui
} // namespace clockwork
