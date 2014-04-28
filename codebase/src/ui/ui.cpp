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
#include "ui.hh"
#include "ui.combobox.renderer.hh"
#include "ui.combobox.projection.hh"
#include "ui.combobox.image.filter.hh"
#include "ui.combobox.texture.filter.hh"
#include "ui.combobox.line.algorithm.hh"
#include "ui.combobox.primitive.mode.hh"
#include "ui.combobox.framebuffer.resolution.hh"
#include "services.hh"
#include <QHBoxLayout>
#include <cassert>
#include "window.hh"

using clockwork::ui::UserInterface;


UserInterface::UserInterface(clockwork::ui::Window& window) :
QWidget(nullptr),
_displayDevice(new clockwork::ui::GUIDisplayDevice(*this)),
_sceneView(new clockwork::ui::GUISceneView(*this)),
_busyIndicator(new QLabel(this)),
_busyIndicatorMovie(new QMovie(":/asset/busy.indicator.gif", QByteArray(), _busyIndicator)),
_menubar(window.menuBar()),
_statusbar(window.statusBar())
{
   assert(_displayDevice != nullptr);
   assert(_sceneView != nullptr);
   assert(_busyIndicator != nullptr);
   assert(_busyIndicator != nullptr);
   assert(_busyIndicatorMovie != nullptr && _busyIndicatorMovie->isValid());
   assert(_menubar != nullptr);
   assert(_statusbar != nullptr);

   connect(this, SIGNAL(updated()), &window, SIGNAL(stateChanged()));
   connect(&clockwork::system::Services::Graphics.getFramebuffer(), SIGNAL(frameReady()), this, SLOT(hideBusyIndicator()));
}


clockwork::Error
UserInterface::build()
{
   blockSignals(true);

   QHBoxLayout* const uiLayout = new QHBoxLayout(this);
   assert(uiLayout != nullptr);
   uiLayout->setContentsMargins(0, 0, 0, 0);
   uiLayout->addWidget(_displayDevice);

   // Configure the display device.
   QVBoxLayout* const displayLayout = new QVBoxLayout(_displayDevice);
   assert(displayLayout != nullptr);
   displayLayout->setContentsMargins(0, 0, 0, 0);
   _displayDevice->setLayout(displayLayout);

   buildMenuBar();
   buildStatusBar();
   buildSceneView(*displayLayout);

   blockSignals(false);

   // Initialise the user interface.
   onComponentStateChanged(nullptr);

   return clockwork::Error::None;
}


void
UserInterface::registerComponent(GUIComponent& component)
{
   _registeredComponents.insert(&component);
}


void
UserInterface::buildMenuBar()
{
#ifdef __TO_IMPLEMENT
   // Build the menu bar.
   if (_menubar != nullptr)
   {
      auto* const fileMenu = _menubar->addMenu("File");
      if (fileMenu != nullptr)
      {
         fileMenu->addAction("New");
         fileMenu->addMenu("Load");
         fileMenu->addSeparator();
         fileMenu->addMenu("Save");
         fileMenu->addSeparator();
         fileMenu->addAction("Reload");
         fileMenu->addSeparator();
         fileMenu->addAction("Quit");
      }
      auto* const preferencesMenu = _menubar->addMenu("Preferences");
      if (preferencesMenu != nullptr)
      {
         auto* const fbResolutionMenu = preferencesMenu->addMenu("Resolution");
         fbResolutionMenu->addAction("VGA");
         fbResolutionMenu->addAction("SVGA");
         fbResolutionMenu->addAction("XGA");
      }
      auto* const viewMenu = _menubar->addMenu("View");
      if (viewMenu != nullptr)
      {
         viewMenu->addAction("Show User Interface");
      }
      auto* const helpMenu = _menubar->addMenu("Help");
      if (helpMenu != nullptr)
      {
         helpMenu->addAction("Get Source Code");
         helpMenu->addAction("Report a Bug");
         fileMenu->addSeparator();
         helpMenu->addAction("About");
      }
   }
#endif
}


void
UserInterface::buildSceneView(QVBoxLayout& layout)
{
   _sceneView->build();
   layout.addWidget(_sceneView);
}


void
UserInterface::buildStatusBar()
{
   _statusbar->setStyleSheet("QStatusBar { background:#333 }");
   _statusbar->addWidget(&_sceneView->getVisibilityToggle());
   _statusbar->addWidget(new GUIPrimitiveModeComboBox(*this));
   _statusbar->addWidget(new GUIImageFilterComboBox(*this));
   _statusbar->addWidget(new GUIProjectionComboBox(*this));
   _statusbar->addWidget(new GUIRendererComboBox(*this));
   _statusbar->addWidget(new GUITextureFilterComboBox(*this));
   _statusbar->addWidget(new GUILineAlgorithmComboBox(*this));

   _statusbar->addPermanentWidget(new GUIFramebufferResolutionComboBox(*this));

   // Initialise the busy indicator.
   _busyIndicator->setMovie(_busyIndicatorMovie);
   _busyIndicator->setVisible(true);
   _busyIndicator->setStyleSheet("QLabel { padding:0 0.3em 0 0 }");
   _busyIndicatorMovie->setCacheMode(QMovie::CacheAll);
   hideBusyIndicator();
   _statusbar->addPermanentWidget(_busyIndicator);
}


void
UserInterface::onComponentStateChanged(clockwork::ui::GUIComponent* const source)
{
   showBusyIndicator();

   for (auto* const component : _registeredComponents)
      component->onInterfaceUpdate(source);

   emit updated();
}


void
UserInterface::showBusyIndicator()
{
   _busyIndicatorMovie->setPaused(false);
}


void
UserInterface::hideBusyIndicator()
{
   _busyIndicatorMovie->setPaused(true);
   _busyIndicatorMovie->jumpToFrame(0);
}
