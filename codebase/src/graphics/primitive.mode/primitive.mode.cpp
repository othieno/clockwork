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
#include "primitive.mode.hh"

using clockwork::graphics::PrimitiveMode;
using clockwork::graphics::PrimitiveModeFactory;


PrimitiveMode::PrimitiveMode(const PrimitiveMode::Identifier& identifier) :
_identifier(identifier)
{}


const PrimitiveMode::Identifier&
PrimitiveMode::getIdentifier() const
{
   return _identifier;
}


PrimitiveModeFactory::PrimitiveModeFactory() :
Factory(PrimitiveMode::Identifier::Triangles)
{
   put(PrimitiveMode::Identifier::Points, nullptr);
   put(PrimitiveMode::Identifier::Lines, nullptr);
   put(PrimitiveMode::Identifier::LineStrip, nullptr);
   put(PrimitiveMode::Identifier::LineLoop, nullptr);
   put(PrimitiveMode::Identifier::Triangles, nullptr);
   put(PrimitiveMode::Identifier::TriangleStrip, nullptr);
   put(PrimitiveMode::Identifier::TriangleFan, nullptr);
}


PrimitiveModeFactory&
PrimitiveModeFactory::getInstance()
{
   static PrimitiveModeFactory INSTANCE;
   return INSTANCE;
}
