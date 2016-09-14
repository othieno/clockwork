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
#ifndef CLOCKWORK_FACTORY_HH
#define CLOCKWORK_FACTORY_HH

#include <QHash>


namespace clockwork {
/**
 *
 */
template<class Key, class Value>
class Factory {
public:
	/**
	 * Instantiate a Factory object.
	 */
	Factory() {}
	/**
	 * The destructor.
	 */
	virtual ~Factory() {
		cache_.clear();
	}
	/**
	 * Return a list of keys in the factory.
	 */
	QList<Key> getKeys() const {
		return cache_.uniqueKeys();
	}
	/**
	 * Return an element from the factory associated to the given key.
	 * @param key the element's key.
	 */
	Value* get(const Key& key) {
		return contains(key) ? &cache_[key] : nullptr;
	}
	/**
	 * Delete an item with the given key from the factory.
	 * @param key the element's key.
	 */
	void remove(const Key& key) {
		if (contains(key)) {
			cache_.remove(key);
		}
	}
	/**
	 * Add an element to the factory.
	 * @param key the element's key.
	 * @param value the actual element.
	 */
	void put(const Key& key, const Value& value) {
		remove(key); // Remove original value.
		cache_.insert(key, value);
	}
	/**
	 * Return true if a value with the specified key has been instantiated by the factory,
	 * false otherwise.
	 * @param key the key to query.
	 */
	bool contains(const Key& key) const {
		return !cache_.isEmpty() && cache_.contains(key);
	}
private:
	/**
	 * The cache will contain already instantiated values.
	 */
	QHash<Key, Value> cache_;
};
} // namespace clockwork

#endif // CLOCKWORK_FACTORY_HH
