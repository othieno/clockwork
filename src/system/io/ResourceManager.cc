/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2016 Jeremy Othieno.
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


clockwork::Error
ResourceManager::open(const QString& filename, QFile& file) {
	// Make sure the referenced file is closed.
	file.close();

	auto error = clockwork::Error::None;
	file.setFileName(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		error = clockwork::Error::FileNotAccessible;
	}
	return error;
}


QString
ResourceManager::getFileHash(QFile& file, const QCryptographicHash::Algorithm algorithm) {
	QString fileHash;
	if (file.isOpen() && file.isReadable()) {
		file.reset(); // Make sure to start at the beginning of the file.

		constexpr std::size_t READ_SIZE = 8192;
		QCryptographicHash fileHashGenerator(algorithm);
		while (!file.atEnd()) {
			fileHashGenerator.addData(file.read(READ_SIZE));
		}
		fileHash = fileHashGenerator.result().toHex();
	}
	return fileHash;
}
