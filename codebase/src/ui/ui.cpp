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
#include "ui.window.hh"
#include "services.hh"
#include "ui.combobox.renderer.hh"
#include "ui.combobox.projection.hh"
#include "ui.combobox.image.filter.hh"
#include "ui.combobox.texture.filter.hh"
#include "ui.combobox.line.algorithm.hh"
#include "ui.combobox.line.primitive.hh"
#include "ui.combobox.framebuffer.resolution.hh"
#include <QHBoxLayout>


clockwork::ui::UserInterface::UserInterface(clockwork::ui::Window& window) :
QWidget(&window),
_window(window),
_display(new clockwork::ui::GUIDisplay(*this)),
//_controlPanel(new clockwork::ui::GUIControlPanel(*this)),
_controlPanel(nullptr),
_busyIndicator(new clockwork::ui::GUIBusyIndicator(*this)),
_qMenuBar(window.menuBar()),
_qStatusBar(new QStatusBar(_display))
{
   // Make the GUI the window's central widget.
   _window.setCentralWidget(this);

   // Make the display the GUI's background widget.
   _display->setParent(this);
   QHBoxLayout* const uiLayout = new QHBoxLayout(this);
   uiLayout->setContentsMargins(0, 0, 0, 0);
   uiLayout->addWidget(_display);

   // The Graphics is the last subsystem to be updated, which is why the
   // busy indicator is hidden after the Graphics update task completes.
   connect(&clockwork::system::Services::Graphics, SIGNAL(updateComplete()), _busyIndicator, SLOT(hide()));
}


clockwork::ui::Window&
clockwork::ui::UserInterface::getWindow()
{
   return _window;
}


void
clockwork::ui::UserInterface::update(const clockwork::ui::GUIComponent* const source)
{
   // Show the busy indicator since the system's about to process tasks.
   _busyIndicator->show();

   // Update the user interface's components.
   emit updateComponents(source);

   // Update the system.
   clockwork::system::Services::update();
}


clockwork::Error
clockwork::ui::UserInterface::build()
{
   // Configure the display's layout.
   if (_display != nullptr)
   {
      QVBoxLayout* const layout = new QVBoxLayout(_display);
      if (layout != nullptr)
      {
         _display->setLayout(layout);
         layout->setContentsMargins(0, 0, 0, 0);

         // Build the control panel.
         if (_controlPanel != nullptr)
         {
            layout->addWidget(_controlPanel);
         }

#ifdef __ENABLE_PROTOTYPES
         // Build the menu bar.
         if (_qMenuBar != nullptr)
         {
            auto* const fileMenu = _qMenuBar->addMenu("File");
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
            auto* const preferencesMenu = _qMenuBar->addMenu("Preferences");
            if (preferencesMenu != nullptr)
            {
               auto* const fbResolutionMenu = preferencesMenu->addMenu("Resolution");
               fbResolutionMenu->addAction("VGA");
               fbResolutionMenu->addAction("SVGA");
               fbResolutionMenu->addAction("XGA");
            }
            auto* const viewMenu = _qMenuBar->addMenu("View");
            if (viewMenu != nullptr)
            {
               viewMenu->addAction("Show User Interface");
            }
            auto* const helpMenu = _qMenuBar->addMenu("Help");
            if (helpMenu != nullptr)
            {
               helpMenu->addAction("Get Source Code");
               helpMenu->addAction("Report a Bug");
               fileMenu->addSeparator();
               helpMenu->addAction("About");
            }
         }
#endif

         // Build the status bar.
         if (_qStatusBar != nullptr)
         {
            layout->addWidget(_qStatusBar, 0, Qt::AlignBottom);

            _qStatusBar->addWidget(new GUIRendererComboBox(*this));
            _qStatusBar->addWidget(new GUIProjectionComboBox(*this));
            _qStatusBar->addWidget(new GUIImageFilterComboBox(*this));
            _qStatusBar->addWidget(new GUILineAlgorithmComboBox(*this));
            _qStatusBar->addWidget(new GUILinePrimitiveComboBox(*this));
            _qStatusBar->addWidget(new GUITextureFilterComboBox(*this));

            // Configure the busy indicator.
            if (_busyIndicator != nullptr)
            {
               _busyIndicator->setVisible(false);
               _qStatusBar->addPermanentWidget(_busyIndicator);
            }
         }
      }
      // Update the user interface to initialise its components.
      update(nullptr);
   }
   return clockwork::Error::None;
}
