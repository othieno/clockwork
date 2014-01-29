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

#include <iostream>


namespace clockwork {
namespace graphics {

/**
 * A normalised viewport. Its values are independent of the display resolution.
 */
struct Viewport
{
   /**
    * The viewport's horizontal origin.
    */
   double x;
   /**
    * The viewport's vertical origin.
    */
   double y;
   /**
    * The viewport's width.
    */
   double width;
   /**
    * The viewport's height.
    */
   double height;
   /**
    * TODO Explain me.
    * @see glDepthRange documentation.
    */
   double near;
   /**
    * TODO Explain me.
    * @see glDepthRange documentation
    */
   double far;
   /**
    * Instantiate a viewport with a given origin, width and height.
    * @param x the viewport's origin on the horizontal plane.
    * @param y the viewport's origin on the vertical plane.
    * @param width the viewport's width.
    * @param height the viewport's height.
    * @param near the mapping of the near clipping plane to the window coordinates.
    * @param far the mapping of the far clipping plane to the window coordinates.
    */
   Viewport
   (
      const double& x = 0,
      const double& y = 0,
      const double& width = 1.0,
      const double& height = 1.0,
      const double& near = 0.0,
      const double& far = 1.0
   );
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::Viewport&);
