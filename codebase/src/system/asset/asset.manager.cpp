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
#include "asset.manager.hh"
#include <QFileInfo>
#include "file.reader.hh"


clockwork::system::AssetManager::AssetManager()
{}


//TODO Use smart pointers.
const clockwork::graphics::Model3D*
clockwork::system::AssetManager::loadModel3D(const std::string& filename)
{
	clockwork::graphics::Model3D* model = nullptr;

	QFileInfo fileInfo(QString(filename.c_str()));
	if (fileInfo.exists() && fileInfo.isFile() && fileInfo.isReadable() && fileInfo.size())
	{
		// If the model was already loaded, then return the instance in memory instead.
		const auto& key = fileInfo.canonicalFilePath();
#ifdef __ENABLE_ASSET_HASHTABLE
//TODO Find out why using maps or hash tables causes segmentation faults or exceptions.
		if (contains(key))
			model = static_cast<clockwork::graphics::Model3D*>(value(key));
		else
#endif // __ENABLE_ASSET_HASHTABLE
		{
			model = new clockwork::graphics::Model3D;
			if (model != nullptr)
			{
				// Load the OBJ file.
				QFile file(key);
				const auto& error = clockwork::io::loadOBJ(file, *model);
				if (error == clockwork::Error::None)
				{
#ifdef __ENABLE_ASSET_HASHTABLE
					insert(key, model);
#endif // __ENABLE_ASSET_HASHTABLE
				}
				else
				{
					delete model;
					model = nullptr;
					std::cout << error << std::endl;
				}
			}
		}
	}
	return model;
}
