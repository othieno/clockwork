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
#ifndef CLOCKWORK_RESOURCE_HH
#define CLOCKWORK_RESOURCE_HH

#include <QObject>


/**
 * @see QFile.
 */
class QFile;
namespace clockwork {
/**
 *
 */
class ResourceManager;
/**
 *
 */
class Resource : public QObject {
	friend class ResourceManager;
public:
	/**
	 *
	 */
	Resource(const Resource&) = delete;
	/**
	 *
	 */
	Resource(const Resource&&) = delete;
	/**
	 *
	 */
	Resource& operator=(const Resource&) = delete;
	/**
	 *
	 */
	Resource& operator=(const Resource&&) = delete;
protected:
	/**
	 *
	 */
	Resource() = default;
private:
	/**
	 * Loads the resource from the specified file.
	 * @param file the file containing the resource to load.
	 */
	virtual void load(QFile& file) = 0;
};
} // namespace clockwork

#endif // CLOCKWORK_RESOURCE_HH
