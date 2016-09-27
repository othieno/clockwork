/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#include "ResourceManager.hh"
#include <QCryptographicHash>
#include <QFileInfo>

using clockwork::ResourceManager;


// TODO Use Bloom filter on filenames, before hashing files.

const clockwork::Mesh*
ResourceManager::loadMesh(const QString& filename)
{
	const Mesh* mesh = nullptr;
	const auto& fileHash = getFileHash(filename, QCryptographicHash::Md4);
	if (!fileHash.isEmpty()) {
		if (resources_.contains(fileHash)) {
			//mesh = static_cast<Mesh*>(resources_[fileHash]);
		} else {
/*
			// A new mesh has to be instantiated and cached.
			output = new clockwork::graphics::Mesh;
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
*/
		}
	}
	return mesh;
}


QString
ResourceManager::getFileHash(const QString& filename, const QCryptographicHash::Algorithm algorithm) {
	QString hash;
	const QFileInfo info(filename);
	if (info.exists() && info.isFile() && info.isReadable() && info.size() > 0) {
		QCryptographicHash hashGenerator(algorithm);
		QFile file(filename);

		file.open(QIODevice::ReadOnly);
		while (!file.atEnd()) {
			hashGenerator.addData(file.read(8192));
		}
		file.close();
		hash = hashGenerator.result().toHex();
	}
	return hash;
}
