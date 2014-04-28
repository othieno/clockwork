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

#include <string>
#include <atomic>


namespace clockwork {
namespace system {

struct Debug
{
   /**
    * Show debug information.
    */
   static bool printToDisplay;
   /**
    * The current display's refresh rate.
    */
   static int displayRefreshRate;
   /**
    * The number of objects in the scene.
    */
   static std::atomic_uint sceneObjectCount;
   /**
    * The number of polygons in the scene.
    */
   static std::atomic_uint scenePolygonCount;
   /**
    * The number of rendered polygons in the scene.
    */
   static std::atomic_uint renderedPolygonCount;
   /**
    * The number of milliseconds it takes to draw a frame.
    */
   static std::atomic_ulong millisecondsPerFrame;
   /**
    * The name of the current viewer.
    */
   static std::string sceneViewerName;
   /**
    * Convert the debug data into string format.
    */
   static std::string toString();
};

} // namespace system
} // namespace clockwork
