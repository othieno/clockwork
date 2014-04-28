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

#include "factory.hh"


namespace clockwork {
namespace graphics {

class TextureFilter
{
public:
   /**
    * Types of texture filters.
    */
   enum class Type
   {
      None,
      Bilinear,
      Trilinear,
      Anisotropic
   };
   /**
    * Return the filter's type.
    */
   const Type& getType() const;
protected:
   /**
    * Instantiate a filter with a given type.
    */
   explicit TextureFilter(const Type type);
private:
   /**
    * This filter's type.
    */
   const Type _type;
};


/**
 * The TextureFilterFactory is a factory that creates and stores TextureFilter objects.
 */
class TextureFilterFactory : public clockwork::Factory<TextureFilter::Type, const TextureFilter*>
{
public:
   /**
    * Return the factory's unique instance.
    */
   static TextureFilterFactory& getInstance();
private:
   /**
    * The TextureFilterFactory is a singleton.
    */
   TextureFilterFactory();
   TextureFilterFactory(const TextureFilterFactory&) = delete;
   TextureFilterFactory& operator=(const TextureFilterFactory&) = delete;
};

} // namespace graphics
} // namespace clockwork
