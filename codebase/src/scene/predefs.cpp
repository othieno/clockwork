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
#include "predefs.hh"
#include "scene.property.hh"
#include "property.appearance.hh"
#include <cassert>

using clockwork::scene::Property;
using clockwork::scene::Appearance;
using namespace clockwork::scene::predefs;


Suzanne::Suzanne() :
Object("Suzanne")
{
   setScale(0.7, 0.7, 0.7);
   setRotation(-180, 0, 0);

   auto& appearance = static_cast<Appearance&>(addProperty(Property::Identifier::Appearance));
   appearance.setModel3D(":/asset/models/suzanne.obj");
}


Suzanne&
Suzanne::getInstance()
{
   static Suzanne INSTANCE;
   return INSTANCE;
}


TexturedCube::TexturedCube() :
Object("Textured Cube")
{
   assert(false);
}


TexturedCube&
TexturedCube::getInstance()
{
   static TexturedCube INSTANCE;
   return INSTANCE;
}
