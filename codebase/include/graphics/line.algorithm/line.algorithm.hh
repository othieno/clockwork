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

/**
 * @see fragment.hh.
 */
class Fragment;

class LineAlgorithm
{
public:
   enum class Identifier
   {
      Bresenham,
      XiaolinWu
   };
   /**
    * Return the algorithm's identifier.
    */
   const LineAlgorithm::Identifier& getIdentifier() const;
   /**
    * Draw a line from an origin to an endpoint.
    * @param origin a fragment containing the line's origin.
    * @param endpoint a fragment containing the line's endpoint.
    */
   virtual void draw(const Fragment& origin, const Fragment& endpoint) const = 0;
private:
   /**
    * The algorithm's identifier.
    */
   LineAlgorithm::Identifier _identifier;
};


/**
 * The LineAlgorithmFactory is a factory that creates and stores LineAlgorithm objects.
 */
class LineAlgorithmFactory : public clockwork::Factory<LineAlgorithm::Identifier, const LineAlgorithm*>
{
public:
   static LineAlgorithmFactory& getInstance();
private:
   LineAlgorithmFactory();
   LineAlgorithmFactory(const LineAlgorithmFactory&) = delete;
   LineAlgorithmFactory& operator=(const LineAlgorithmFactory&) = delete;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::LineAlgorithm::Identifier&);
