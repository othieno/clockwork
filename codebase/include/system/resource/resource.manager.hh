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

#include <QHash>
#include <QCryptographicHash>
#include "model3d.hh"


namespace clockwork {
namespace system {

class ResourceManager : public QObject
{
friend class Services;
public:
   /**
    * Load, store and return a 3D model from a given file. The 3D model is stored
    * in the resource dictionary which makes sure only a single instance of the
    * same 3D model is created in memory.
    * @param filename the name of the file containing the 3D model to load.
    */
   const clockwork::graphics::Model3D* loadModel3D(const QString& filename);
private:
   /**
    * The file hash generator.
    */
   QCryptographicHash _hashGenerator;
   /**
    * The resource dictionary where each resource is identified by its
    * cryptographic hash (stored in the form of a string).
    */
   QHash<const QString, clockwork::system::Resource*> _resources;
   /**
    * The ResourceManager is a singleton object so only a single instance of this
    * class should be created. To prevent copying and accidental instantiation,
    * the constructor is hidden (accessible only by the Services class),
    * and its copy constructor and operator are deleted.
    */
   ResourceManager();
   ResourceManager(const ResourceManager&) = delete;
   ResourceManager& operator=(const ResourceManager&) = delete;
};

} // namespace system
} // namespace clockwork
