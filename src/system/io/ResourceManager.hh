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
#ifndef CLOCKWORK_RESOURCE_MANAGER_HH
#define CLOCKWORK_RESOURCE_MANAGER_HH

#include <QHash>
#include <QCryptographicHash>
#include <memory>
#include "Resource.hh"


namespace clockwork {
/**
 * @see graphics/Model3d.hh.
 */
class Model3d;
/**
 *
 */
class ResourceManager {
public:
	/**
	 *
	 */
	ResourceManager(const ResourceManager&) = delete;
	/**
	 *
	 */
	ResourceManager(const ResourceManager&&) = delete;
	/**
	 *
	 */
	ResourceManager& operator=(const ResourceManager&) = delete;
	/**
	 *
	 */
	ResourceManager& operator=(const ResourceManager&&) = delete;
	/**
	 * Returns the ResourceManager's singleton instance.
	 */
	ResourceManager& getInstance();
	/**
	 * Loads a 3D model from the specified file.
	 * @param filename the name of the file containing the 3D model to load.
	 */
	const Model3d* loadModel3d(const QString& filename);
private:
	/**
	 * Instantiates a ResourceManager object.
	 */
	ResourceManager() = default;
	/**
	 * Returns the specified file's hash.
	 * @param filename the name of the file to hash.
	 * @param algorithm the hashing algorithm to use.
	 */
	static QString getFileHash(const QString& filename, const QCryptographicHash::Algorithm algorithm);
	/**
	 * The resource dictionary where each resource is identified by a unique hash.
	 */
	QHash<const QString, std::unique_ptr<Resource>> resources_;
};
} // namespace clockwork

#endif // CLOCKWORK_RESOURCE_MANAGER_HH
