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
#ifndef CLOCKWORK_RESOURCE_MANAGER_HH
#define CLOCKWORK_RESOURCE_MANAGER_HH

#include <QFile>
#include <QHash>
#include <QCryptographicHash>
#include <memory>
#include "Resource.hh"
#include "Error.hh"


namespace clockwork {
/**
 * @see graphics/Mesh.hh.
 */
class Mesh;
/**
 * @see system/Service.hh.
 */
class Service;
/**
 *
 */
class ResourceManager : private QObject {
	friend class Service;
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
	 * Loads a resource from the file with the specified name.
	 * @param filename the name of the file containing the resource to load.
	 */
	template<class ResourceType>
	const ResourceType* load(const QString& filename) {
		static_assert(std::is_base_of<Resource, ResourceType>::value);

		QFile file;
		auto error = open(filename, file);
		if (error != Error::None) {
			return nullptr;
		}

		const auto& fileHash = getFileHash(file, QCryptographicHash::Md4);
		if (fileHash.isEmpty()) {
			return nullptr;
		}

		// Before loading the resource, check if it's been cached.
		ResourceType* resource = findChild<ResourceType*>(fileHash, Qt::FindDirectChildrenOnly);
		if (resource == nullptr) {
			resource = new ResourceType;
			resource->setObjectName(fileHash);
			resource->setParent(this);
			resource->load(file);
		}
		return resource;
	}
private:
	/**
	 * Instantiates a ResourceManager object.
	 */
	ResourceManager() = default;
	/**
	 * Opens a file with the specified filename.
	 * @param filename the name of the file to open.
	 * @param file a reference to the File object to be updated.
	 */
	static Error open(const QString& filename, QFile& file);
	/**
	 * Returns the specified file's hash.
	 * @param file an open, readable file to hash.
	 * @param algorithm the hashing algorithm to use.
	 */
	static QString getFileHash(QFile& file, const QCryptographicHash::Algorithm algorithm);
};
} // namespace clockwork

#endif // CLOCKWORK_RESOURCE_MANAGER_HH
