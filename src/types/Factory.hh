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
#include <memory>


namespace clockwork {
/**
 *
 */
template<class Key, class Value>
class Factory {
public:
	/**
	 *
	 */
	Factory(Factory&) = delete;
	/**
	 *
	 */
	Factory(Factory&&) = delete;
	/**
	 *
	 */
	Factory& operator=(Factory&) = delete;
	/**
	 *
	 */
	Factory& operator=(Factory&&) = delete;
	/**
	 * Frees up resources used by the factory.
	 */
	virtual ~Factory();
	/**
	 * Returns true if a value with the specified key is stored by the factory, false otherwise.
	 * @param key the key to query.
	 */
	bool contains(const Key& key) const;
	/**
	 * Returns an element associated with the specified key.
	 * @param key the element's key.
	 */
	Value* get(const Key& key);
	/**
	 * Deletes the entry with the specified key from the factory's cache.
	 * @param key the entry's key.
	 */
	void remove(const Key& key);
	/**
	 * Returns a list of keys stored in the factory's cache.
	 */
	QList<Key> getKeys() const;
protected:
	/**
	 * Instantiates a Factory object.
	 */
	Factory() = default;
private:
	/**
	 *
	 */
	using CacheEntry = std::unique_ptr<Value>;
	/**
	 * Instantiates the Value object assigned to the specified key.
	 * @param key the Value object's unique key.
	 */
	static Value* create(const Key& key);
	/**
	 * The cache will contain already instantiated values.
	 */
	QHash<Key, CacheEntry> cache_;
};


template<class K, class V>
Factory<K, V>::~Factory() {
	cache_.clear();
}


template<class K, class V> bool
Factory<K, V>::contains(const K& key) const {
	return !cache_.isEmpty() && cache_.contains(key);
}


template<class K, class V> V*
Factory<K, V>::get(const K& key) {
	if (!contains(key)) {
		cache_[key] = Factory::CacheEntry(Factory::create(key));
	}
	return cache_[key];
}


template<class K, class V> void
Factory<K, V>::remove(const K& key) {
	cache_.remove(key);
}


template<class K, class V> QList<K>
Factory<K, V>::getKeys() const {
	return cache_.uniqueKeys();
}
} // namespace clockwork

#endif // CLOCKWORK_FACTORY_HH
