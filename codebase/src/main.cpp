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
#include <QApplication>


int main(int argc, char** argv)
{
   QApplication application(argc, argv);
   auto error = clockwork::system::Services::initialise(argc, (const char**)argv);
   if (error == clockwork::Error::None)
   {
      clockwork::ui::Window window;
      window.showMaximized();

      // If the return value of the exec function is not zero, then execution failed.
      if (application.exec())
         error = clockwork::Error::Unknown;

      // Cleanup the services when done.
      error = clockwork::system::Services::dispose(error);
   }

   // Print the error for debug purposes.
   if (error != clockwork::Error::None)
      std::cout << error << std::endl;
   return static_cast<int>(error);
}
