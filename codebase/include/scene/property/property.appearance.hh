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

#include "scene.property.hh"
#include "model3d.hh"
#include "material.hh"


namespace clockwork {
namespace scene {

class Appearance : public Property
{
public:
   /**
    * Instantiate an Appearance property with a specified proprietor.
    * @param proprietor the scene object that is described by this property.
    */
   explicit Appearance(Object& proprietor);
   /**
    * Return the 3D model.
    */
   const clockwork::graphics::Model3D* getModel3D() const;
   /**
    * Set the 3D model.
    * @param model3D the 3D model to set.
    */
   void setModel3D(const clockwork::graphics::Model3D* const model3D);
   /**
    * Set the 3D model.
    * @param filename the name of the file containing the the 3D model to set.
    */
   void setModel3D(const QString& filename);
   /**
    * Return the material.
    */
   const clockwork::graphics::Material& getMaterial() const;
   /**
    * Set the material.
    * @param material the material to set.
    */
   void setMaterial(const clockwork::graphics::Material&& material);
private:
   /**
    * A 3D model.
    */
   const clockwork::graphics::Model3D* _model3D;
   /**
    * A material, i.e. the 3D model's look and feel.
    */
   clockwork::graphics::Material _material;
};

} // namespace scene
} // namespace clockwork
