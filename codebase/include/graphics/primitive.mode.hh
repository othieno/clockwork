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
#include "vertex.hh"


namespace clockwork {
namespace graphics {


/**
 * TODO Explain me better.
 */
class PrimitiveMode
{
public:
   enum class Identifier
   {
      Points,
      Lines,
      LineStrip,
      LineLoop,
      Triangles,
      TriangleStrip,
      TriangleFan
   };
   /**
    * Return the primitive mode's identifier.
    */
   const PrimitiveMode::Identifier& getIdentifier() const;
   /**
    * Perform primitive assembly on a collection of vertices. This operation
    * creates point, line or triangle primitives from a collection of vertices.
    * @param vertices the collection of vertices from which primitives will be formed.
    */
   virtual VertexArray& assemble(VertexArray& vertices) const = 0;
protected:
   /**
    * Instantiate a primitive mode with a given identifier.
    * @param identifier the primitive mode's identifier.
    */
   explicit PrimitiveMode(const PrimitiveMode::Identifier& identifier);
private:
   /**
    * The primitive mode's identifier.
    */
   const PrimitiveMode::Identifier _identifier;
};


/**
 * The PrimitiveModeFactory is a factory that creates and stores PrimitiveMode objects.
 */
class PrimitiveModeFactory : public clockwork::Factory<PrimitiveMode::Identifier, const PrimitiveMode*>
{
public:
   static PrimitiveModeFactory& getInstance();
private:
   PrimitiveModeFactory();
   PrimitiveModeFactory(const PrimitiveModeFactory&) = delete;
   PrimitiveModeFactory& operator=(const PrimitiveModeFactory&) = delete;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::PrimitiveMode::Identifier&);
