/*
 *  lazy4_internal_CollectorStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IStorage.h"
#include "lazy4_internal_TemplateStorage.h"

#include <vector>

namespace lazy4 {
		
	namespace internal2 {
#if 0
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		class MemoryStorage {
		public:
			typedef unsigned int I;
			typedef IStorage<I>* T;
			typedef unsigned short E;
			typedef std::vector<unsigned short> EnumVector;
			typedef std::vector<EnumVector> KeyToEnumVectorMap;
			typedef std::vector<T> EnumToValueMap;
			typedef std::vector<I> KeyVector;
			typedef TemplateStorage<I, I, false, KeyVector> KeyStorage;
			typedef std::vector<E> EnumVector;
			typedef TemplateCollectionStorage<I, E, std::vector<std::vector<E> > > KeyToEnumStorage;
			typedef AssociativeStorage<E, T, std::vector<T const*>, std::tr1::unordered_map<T, E> > > EnumToValueStorage
			
			template<typename I, typename E, typename T,
			typename KeyToEnumStorage = TemplateCollectionStorage<I, E, std::map<I, std::vector<E> > >,
			typename EnumToValueStorage = AssociativeStorage<E, T, std::vector<T const*>, std::tr1::unordered_map<T, E> > >
			typedef SharedCollectionStorage :
			
		public:
			KeyToEnumVectorMap _key_to_enum_map;
			KeyVector _unused_key_vector;
			EnumToValueMap _enum_to_value_map;
			
		public:
			bool modifyObject(int objectID, IStorage* storage) {
				return true;
			}
			
			bool insertObject(int objectID, IStorage* storage) {
				return true;
			}
			
			bool removeObject(int objectID, IStorage* storage) {
				return true;
			}
			
			bool removeObject(int objectID) {
				return true;
			}
			
			bool addStorage(IStorage* storage) {
				storage->id() = _enum_to_value_map.size();
				_enum_to_value_map.push_back(storage); 
				return true;
			}
			
			bool removeStorage(IStorage* storage) {
				EnumToValueMap::iterator it = std::find(_enum_to_value_map.begin(), _enum_to_value_map.end(), storage);
				if (it != _enum_to_value_map.end()) {
					_enum_to_value_map.erase(it);
					return true;
				}
				return false;
			}
		};
#endif
#if 0
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename E, typename T>
		class SharedStorage<I, E, T, true> :
		public ISharedStorage<I, E, T, true >
		{
		public:
			typedef typename std::vector<E> EnumVector;
			typedef typename std::map<const I, EnumVector> KeyToEnumMap;
			typedef typename std::vector<T const*> EnumToValueMap;
			typedef typename std::tr1::unordered_map<T, E> ValueToEnumMap;
			
		public:
			I _id;
			KeyToEnumMap _key_to_enum_map;
			EnumToValueMap _enum_to_value_map;
			ValueToEnumMap _value_to_enum_map;
			T _empty_value;
			E _empty_enum;
			
		public:
			static const T& enum_to_value_function(const E& enum_value, const EnumToValueMap& enum_to_value_map) {
				return *(enum_to_value_map[enum_value]);
			}
			
		public:
			virtual const I& id() const { return _id; }
			virtual I& id() { return _id; }
			
			
		public:
			virtual bool exist(const I& objectID) const { return _key_to_enum_map.find(objectID) != _key_to_enum_map.end(); }
			
			virtual bool unset(const I& objectID) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					_key_to_enum_map.erase(it); 
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value) {
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) {
					EnumVector& vec = enum_it->second;
					vec.clear();
					for (Iterator<const T&> it = value.begin(); !it.eof(); ++it) {
						vec.push_back(get_key(*it)); 
					}
					if (vec.empty()) {
						_key_to_enum_map.erase(enum_it);
					}
					return true;
				} else {
					EnumVector& vec = _key_to_enum_map[objectID];
					for (Iterator<const T&> it = value.begin(); !it.eof(); ++it) {
						vec.push_back(get_key(*it)); 
					}
					if (vec.empty()) {
						typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
						_key_to_enum_map.erase(enum_it);
					}
					return false;
				}
			}
			
			virtual bool find(const I& objectID, Collection<const T&>& value) const {
				typename KeyToEnumMap::const_iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) { 
					Modifier<const T&, const E&, const EnumToValueMap& > modifier(enum_to_value_function, _enum_to_value_map);
					Collection<const E&, void, const EnumVector&> collec = enum_it->second;
					value = collec.change_first(modifier);
					return true;
				} else {
					value = Collection<const T&>();
					return false;
				}
			}
			
			virtual Collection<const T&> get(const I& objectID) const { 
				typename KeyToEnumMap::const_iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) {
					Modifier<const T&, const E&, const EnumToValueMap& > modifier(enum_to_value_function, _enum_to_value_map);
					Collection<const E&, void, const EnumVector&> collec = enum_it->second;
					return collec.change_first(modifier);
				} else {
					return Collection<const T&>();
				}
			}
			
		public:
			virtual bool insert(const I& objectID, const T& value, size_t position) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					it->second[position] = const_cast<E&> (get_key(value)); 
					return true;
				} else {
					_key_to_enum_map[objectID][position] = const_cast<E&> (get_key(value)); 
					return false;
				}
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value, size_t position) {
				typename KeyToEnumMap::iterator vec_it = _key_to_enum_map.find(objectID);
				if (vec_it != _key_to_enum_map.end()) { 
					EnumVector& vec = vec_it->second;
					for (Iterator<const T&> it = value.begin(); !it.eof(); ++it) {
						vec[position++] = const_cast<E&> (get_key(*it)); 
					}
					return true;
				} else {
					EnumVector& vec = _key_to_enum_map[objectID];
					position = 0;
					for (Iterator<const T&> it = value.begin(); !it.eof(); ++it) {
						vec[position++] = const_cast<E&> (get_key(*it)); 
					}
					return false;
				}
			}
			
			virtual bool erase(const I& objectID, size_t position) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					EnumVector& vec = it->second;
					vec.erase(vec.begin() + position); 
					if (vec.empty()) {
						_key_to_enum_map.erase(it);
					}
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t size) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					it->second.erase(it->second.begin() + position, it->second.begin() + position + size); 
					if (it->second.empty()) {
						_key_to_enum_map.erase(it);
					}
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool erase(const I& objectID, const T& value) {
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) { 
					EnumVector& vec = enum_it->second;
					typename EnumVector::iterator vec_it = std::find(vec.begin(), vec.end(), const_cast<E&> (get_key(value)));
					if (vec_it != vec.end()) {
						vec.erase(vec_it);
						if (vec.empty()) {
							_key_to_enum_map.erase(enum_it);
						}
						return true;
					}
				} 
				return false;
			}
			
			virtual bool erase(const I& objectID, const Collection<const T&>& value) {
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) { 
					bool ret = true;
					EnumVector& vec = enum_it->second;
					for (Iterator<const T&> it = value.begin(); !it.eof(); ++it) {
						typename EnumVector::iterator vec_it = std::find(vec.begin(), vec.end(), const_cast<E&> (get_key(*it)));
						if (vec_it != vec.end()) {
							enum_it->second.erase(vec_it);
						} else {
							ret = false;
						}
					}
					if (enum_it->second.empty()) {
						_key_to_enum_map.erase(enum_it);
					}
					return ret;
				}
				return false;
			}
			
		public:
			virtual bool set_enum(const I& objectID, const Collection<const E&>& enum_collection) { 
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) {
					EnumVector& vec = enum_it->second;
					vec.clear();
					for (Iterator<const E&> it = enum_collection.begin(); !it.eof(); ++it) {
						vec.push_back(*it); 
					}
					return true;
				} else {
					EnumVector& vec = _key_to_enum_map[objectID];
					for (Iterator<const E&> it = enum_collection.begin(); !it.eof(); ++it) {
						vec.push_back(*it); 
					}
					return false;
				}
			}
			
			virtual Collection<const E&> get_enum(const I& objectID) const { 
				typename KeyToEnumMap::const_iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) {
					return Collection<const E&, void, const EnumVector&> (it->second);
				} else {
					return Collection<const E&>();
				}
			}
			
			virtual bool find_enum(const I& objectID, Collection<const E&>& enum_collection) const { 
				typename KeyToEnumMap::const_iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) {
					enum_collection = Collection<const E&, void, const EnumVector&> (it->second);
					return true;
				} else {
					enum_collection = Collection<const E&>();
					return false;
				}
			}
			
			virtual const E& find_enum(const T& value) const { 
				typename ValueToEnumMap::const_iterator it = _value_to_enum_map.find(value);
				return it != _value_to_enum_map.end() ? it->second : _empty_enum;
			}
			
			virtual const E& get_key(const T& value) const { 
				typename ValueToEnumMap::const_iterator it = _value_to_enum_map.find(const_cast<T&> (value));
				if (it != _value_to_enum_map.end()) {
					return it->second;
				} else {
					return _empty_enum;
				}
			}
			
			virtual const E* find_key(const T& value) const { 
				typename ValueToEnumMap::const_iterator it = _value_to_enum_map.find(const_cast<T&> (value));
				if (it != _value_to_enum_map.end()) {
					return &(it->second);
				} else {
					return &_empty_enum;
				}
			}
			
			virtual const T* find_value(const E& enum_value) const { 
				return _enum_to_value_map.size() > enum_value ? _enum_to_value_map[enum_value] : &_empty_value;
			}
			
			virtual const T& get_value(const E& enum_value) const { 
				return _enum_to_value_map.size() > enum_value ? *(_enum_to_value_map[enum_value]) : _empty_value;
			}
			
			virtual bool set_key(const E& enum_value, const T& value) {
				if (enum_value >= _enum_to_value_map.size()) {
					_enum_to_value_map.resize(enum_value + 1);  //FIXME : doesn't work !
				}
				typename ValueToEnumMap::iterator it = _value_to_enum_map.insert(std::make_pair<T, E>(value, enum_value)).first;
				_enum_to_value_map[enum_value] = &(it->first);
				return true;
			} 
			
		public:
			virtual bool insert_enum(const I& objectID, const E& enum_value, size_t position) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					it->second[position] = const_cast<E&> (enum_value);  //FIXME : doesn't work ! size issue
					return true;
				} else {
					_key_to_enum_map[objectID].push_back(const_cast<E&> (enum_value)); 
					return false;
				}
			}
			
			virtual bool insert_enum(const I& objectID, const Collection<const E&>& enum_collection, size_t position) {
				typename KeyToEnumMap::iterator it = _key_to_enum_map.find(objectID);
				if (it != _key_to_enum_map.end()) { 
					it->second.insert(it->second.begin() + position, enum_collection.begin(), enum_collection.end()); 
					return true;
				} else {
					_key_to_enum_map[objectID].insert(it->second.begin() + position, enum_collection.begin(), enum_collection.end()); 
					return false;
				}
			}
			
			virtual bool erase_enum(const I& objectID, const E& enum_value) {
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) { 
					typename EnumVector::iterator vec_it = std::find(enum_it->second.begin(), enum_it->second.end(), const_cast<E&> (enum_value));
					if (vec_it != enum_it->second.end()) {
						enum_it->second.erase(vec_it);
						if (enum_it->second.empty()) {
							_key_to_enum_map.erase(enum_it);
						}
						return true;
					}
				} 
				return false;
			}
			
			virtual bool erase_enum(const I& objectID, const Collection<const E&>& enum_collection) {
				typename KeyToEnumMap::iterator enum_it = _key_to_enum_map.find(objectID);
				if (enum_it != _key_to_enum_map.end()) { 
					bool ret = true;
					for (Iterator<const E&> it = enum_collection.begin(); !it.eof(); ++it) {
						typename EnumVector::iterator vec_it = std::find(enum_it->second.begin(), enum_it->second.end(), *it);
						if (vec_it != enum_it->second.end()) {
							enum_it->second.erase(vec_it);
						} else {
							ret = false;
						}
					}
					if (enum_it->second.empty()) {
						_key_to_enum_map.erase(enum_it);
					}
					return ret;
				}
				return false;
			}
			
		};
#endif
		
	}
	
}