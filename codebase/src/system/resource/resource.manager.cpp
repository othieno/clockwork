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
#include "resource.manager.hh"
#include <QFileInfo>
#include "file.reader.hh"
#include <cassert>

using clockwork::system::ResourceManager;


ResourceManager::ResourceManager() :
_hashGenerator(QCryptographicHash::Sha1)
{}


const clockwork::graphics::Model3D*
ResourceManager::loadModel3D(const QString& filename)
{
   clockwork::graphics::Model3D* output = nullptr;

   // Check if the file exists and can be read.
   const QFileInfo info(filename);
   if (info.exists() && info.isFile() && info.isReadable() && info.size())
   {
      QFile file(filename);
      if (file.open(QIODevice::ReadOnly))
      {
         // Calculate the file's hash.
         _hashGenerator.reset();
         while (!file.atEnd())
            _hashGenerator.addData(file.read(8192));

         // If the file has been loaded, then return the loaded instance.
         const auto& key = QString(_hashGenerator.result().toHex());
         if (_resources.contains(key))
            output = static_cast<clockwork::graphics::Model3D*>(_resources.value(key));
         else
         {
            // A new 3D model has to be loaded. Create a new instance where the model
            // will be stored.
            output = new clockwork::graphics::Model3D;
            assert(output != nullptr);

            // The input file cursor needs rewound to the beginning of the file since
            // it's currently at the end of the file.
            assert(file.reset());

            auto error = clockwork::io::loadOBJ(file, *output);
            if (error != clockwork::Error::None)
            {
               delete output;
               output = nullptr;

               std::cout << error << std::endl;
            }
            else
               _resources.insert(key, output);
         }
      }
   }
   return output;
}
