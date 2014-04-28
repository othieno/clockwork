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

#include <cstdint>
#include <iostream>


namespace clockwork {
namespace graphics {

struct ColorRGBA
{
   /**
    * The color's normalised red channel.
    */
   float red;
   /**
    * The color's normalised green channel.
    */
   float green;
   /**
    * The color's normalised blue channel.
    */
   float blue;
   /**
    * The color's normalised alpha channel.
    */
   float alpha;
   /**
    * Instantiate an RGBa color with normalised red, green and blue channels.
    * @param red the red channel.
    * @param green the green channel.
    * @param blue the blue channel.
    * @param alpha the alpha channel.
    */
   ColorRGBA(const float& red = 0.0f, const float& green = 0.0f, const float& blue = 0.0f, const float& alpha = 1.0f);
   /**
    * Convert the RGBA color into a 32-bit integer value.
    * Consider this a shortcut for ColorRGBA::merge(*this).
    */
   operator uint32_t() const;
public:
   /**
    * Merge a ColorRGBA object into one 32-bit integer.
    * @param color the ColorRGBA object to merge.
    */
   static uint32_t merge(const ColorRGBA& color);
   /**
    * Split a 32-bit integer value into an RGBA color.
    * @param ARGB the 32-bit integer that represents an A8R8G8B8 color.
    */
   static ColorRGBA split(const uint32_t& ARGB);
   /**
    * Return a random RGBA color.
    */
   static ColorRGBA getRandom();
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::ColorRGBA&);
