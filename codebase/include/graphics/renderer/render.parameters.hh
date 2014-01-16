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
#include <array>
#include <functional>
#include "face.hh"
#include "fragment.hh"
#include "services.hh"


namespace clockwork {
namespace graphics {

class RenderParameters
{
public:
   /**
    * Available types of renders.
    */
   enum class Type
   {
      Point,
      Wireframe,
      Random,
      Depth,
      Normals,
      Texture,
      Constant,
      Phong,
      Cel,
      Bump,
      Deferred
   };
   /**
    * Return the type of render performed by these parameters.
    */
   const Type& getType() const;
   /**
    * TODO Explain me.
    */
   virtual void preVertexProgram(const Face& face, const Vertex& vertex, Fragment& fragment) const;
   /**
    * TODO Explain me.
    */
   virtual void postVertexProgram(const Face& face, const Vertex& vertex, Fragment& fragment) const;
   /**
    * The primitive assembly operation creates a point, line or polygon primitive from
    * fragments. In the case of polygon primitives, missing fragments in the hollows of
    * the polygon triangles are interpolated. These primitives are then passed to the
    * fragment program which determines their color.
    * @param triangle a set of 3 fragments that will create one or more primitives.
    */
   virtual void primitiveAssembly(const std::array<const Fragment*, 3>& triangle) const = 0;
protected:
   /**
    * Instantiate a render parameter set.
    * @param type the type of render performed by this set of parameters.
    */
   RenderParameters(const Type& type);
   /**
    * @see Framebuffer::plot(2).
    */
   inline void plot(const Fragment& fragment) const
   {
      clockwork::system::Services::Graphics.plot(fragment, _fragmentProgram);
   }
   /**
    * @see Framebuffer::plot(3).
    */
   inline void plot(const uint32_t& x, const uint32_t& y, const double& z, const uint32_t color) const
   {
      clockwork::system::Services::Graphics.plot(x, y, z, color);
   }
   /**
    * Set the fragment program.
    * @param program a pointer to the fragment program.
    */
   void setFragmentProgram(const std::function<uint32_t(const Fragment&)>& program);
private:
   /**
    * The type of render performed by these parameters.
    */
   const Type _type;
   /**
    * A pointer to the fragment program. By default, this will point to the default
    * fragment program.
    */
   std::function<uint32_t(const Fragment&)> _fragmentProgram;
   /**
    * The default fragment program.
    * @param fragment the fragment containing the attributes that will determine a color.
    */
   uint32_t defaultFragmentProgram(const Fragment& fragment) const;
};

} // namespace graphics
} // namespace clockwork

std::ostream& operator<<(std::ostream&, const clockwork::graphics::RenderParameters::Type&);
