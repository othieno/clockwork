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
#pragma once

#include <map>
#include <list>
#include <sstream>


namespace clockwork {

template<class KeyType, class ValueType>
class Factory
{
public:
   /**
    * Instantiate a Factory with a default key.
    * @param key the factory's default key.
    */
   Factory(const KeyType& key) :
   _defaultKey(key)
   {}
   /**
    * The destructor.
    */
   virtual ~Factory()
   {
      _map.clear();
   }
   /**
    * Return the default key.
    */
   const KeyType& getDefaultKey() const
   {
      return _defaultKey;
   }
   /**
    * Return a list of keys in the factory.
    */
   std::list<KeyType> getKeys() const
   {
      std::list<KeyType> keys;
      for (const auto& entry : _map)
         keys.push_back(entry.first);

      return keys;
   }
   /**
    * Return the keys in the form of a list of strings.
    */
   std::list<std::string> getKeysAsStrings() const
   {
      std::list<std::string> keys;
      std::stringstream sstream;

      for (const auto& entry : _map)
      {
         sstream << entry.first;
         keys.push_back(sstream.str());

         // Clear the string stream.
         sstream.str(std::string());
      }
      return keys;
   }
   /**
    * Return the default value, i.e. the value associated to the default key.
    */
   ValueType* getDefaultValue()
   {
      return get(_defaultKey);
   }
   /**
    * Return an element from the factory associated to the given key.
    * @param key the element's key.
    */
   ValueType* get(const KeyType& key)
   {
      return exists(key) ? _map[key] : nullptr;
   }
   /**
    * Delete an item with the given key from the factory.
    * @param key the element's key.
    */
   void remove(const KeyType& key)
   {
      if (exists(key))
         _map.erase(key);
   }
   /**
    * Add an element to the factory.
    * @param key the element's key.
    * @param value the actual element.
    */
   void put(const KeyType& key, ValueType* value)
   {
      // If the key exists, then remove its old value before setting a new one.
      if (exists(key))
         remove(key);

      _map.insert(std::pair<const KeyType, ValueType*>(key, value));
   }
   /**
    * Return true if a given key exists in the factory.
    * @param key the key to query.
    */
   bool exists(const KeyType& key) const
   {
      return (!_map.empty() && _map.find(key) != _map.end());
   }
private:
   /**
    * The default key.
    */
   const KeyType _defaultKey;
   /**
    * The map containing key-value pairs.
    */
   std::map<KeyType, ValueType*> _map;
};

} // namespace clockwork
