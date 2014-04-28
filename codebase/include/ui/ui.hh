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

#include "error.hh"
#include "ui.display.hh"
#include "ui.view.scene.hh"
#include <QMenuBar>
#include <QStatusBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>


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
friend class clockwork::ui::Window;
public:
   /**
    * Build the user interface.
    */
   clockwork::Error build();
   /**
    * Register a user interface component so that it receives
    * updates from this interface.
    * @param component the component to register.
    */
   void registerComponent(GUIComponent& component);
private:
   /**
    * Instantiate a user interface attached to a window.
    * @param window the window where this interface will be rendered to.
    */
   explicit UserInterface(clockwork::ui::Window& window);
   UserInterface(const UserInterface&) = delete;
   UserInterface& operator=(const UserInterface&) = delete;
   /**
    * The set of all components attached to this interface.
    */
   QSet<GUIComponent*> _registeredComponents;
   /**
    * The display device.
    */
   GUIDisplayDevice* const _displayDevice;
   /**
    * The scene view.
    */
   GUISceneView* const _sceneView;
   /**
    * The busy indicator.
    */
   QLabel* const _busyIndicator;
   /**
    * The movie (animation) that is played when the busy indicator is activated.
    */
   QMovie* const _busyIndicatorMovie;
   /**
    * The menu bar.
    */
   QMenuBar* const _menubar;
   /**
    * The status bar.
    */
   QStatusBar* const _statusbar;
   /**
    * Build the menubar component.
    */
   void buildMenuBar();
   /**
    * Build the statusbar component.
    */
   void buildStatusBar();
   /**
    * Build the scene view.
    */
   void buildSceneView(QVBoxLayout& layout);
private slots:
   /**
    * This slot is called when a component changes its state. It will
    * update all components attached to the user interface if need be,
    * effectively updating any components that may depend on the
    * component that emitted the signal.
    * @param source the component that changed its state.
    */
   void onComponentStateChanged(clockwork::ui::GUIComponent* const source);
   /**
    * Show the busy indicator.
    */
   void showBusyIndicator();
   /**
    * Hide the busy indicator.
    */
   void hideBusyIndicator();
signals:
   /**
    * This signal is emitted when all the components attached to this user
    * interface have been updated after a user interaction.
    */
   void updated();
};

} // namespace ui
} // namespace clockwork
