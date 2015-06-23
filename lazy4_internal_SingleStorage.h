/*
 *  lazy4_internal_TemplateStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_Query_std_tr1_unordered_map.h"
#include "lazy4_Query_std_vector.h"

#if defined( _MSC_VER )
#include <unordered_map>
#else
#include <tr1/unordered_map>
namespace std { namespace tr1 { using namespace std; } }
#endif

#include <map>
#include <vector>
#include <string>


namespace lazy4 {
	
	namespace internal2 {
				
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename T>
		class SwapOrCopy {
		public:
			static inline void apply(T& source, T& target) { target = source; }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename T, typename A> 
		class SwapOrCopy<std::vector<T, A> > {
		public:
			static inline void apply(std::vector<T, A>& source, std::vector<T, A>& target) { target.swap(source);	}
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename T, typename Traits, typename Alloc>
		class SwapOrCopy<std::basic_string<T, Traits, Alloc> > {
		public:
			static inline void apply(std::basic_string<T, Traits, Alloc>& source, std::basic_string<T, Traits, Alloc>& target) { target.swap(source); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename KeyToValueMap>
		class SingleStorage {
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename _Hash, typename _Pred, typename _Alloc >
		class SingleStorage<I, T, std::tr1::unordered_map<I, T, _Hash, _Pred, _Alloc> > :
		public ITemplateStorage<I, T, false>
		{
		public:
			typedef std::tr1::unordered_map<I, T, _Hash, _Pred, _Alloc> KeyToValueMap;
			
		public:
			KeyToValueMap _key_to_value_map;
			
		public:
			virtual bool exist(const I& objectID) const { return _key_to_value_map.find(objectID) != _key_to_value_map.end(); }
			
			virtual Query<I> all() const {
				return content();
			}
			
			virtual Query<I, const T&> content() const {
				return Query<I, const T&, const KeyToValueMap&> (_key_to_value_map);
			}
			
			virtual bool unset(const I& objectID) {
				typename KeyToValueMap::iterator it = _key_to_value_map.find(objectID);
				if (it != _key_to_value_map.end()) { 
					_key_to_value_map.erase(it); 
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool unset(const I& objectID, T& old_value) {
				typename KeyToValueMap::iterator it = _key_to_value_map.find(objectID);
				if (it != _key_to_value_map.end()) { 
					SwapOrCopy<T>::apply(it->second, old_value);
					_key_to_value_map.erase(it); 
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.find(sourceID);
				if (source_it != _key_to_value_map.end()) { 
					typename KeyToValueMap::iterator target_it = _key_to_value_map.find(targetID);
					if (target_it != _key_to_value_map.end()) { 
						if (source_it->second == target_it->second) {
							return false;
						}
						target_it->second = source_it->second;
						return true;
					} else {
						_key_to_value_map[targetID] = source_it->second;
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.find(sourceID);
				if (source_it != _key_to_value_map.end()) { 
					typename KeyToValueMap::iterator target_it = _key_to_value_map.find(targetID);
					if (target_it != _key_to_value_map.end()) { 
						if (source_it->second == target_it->second) {
							return false;
						}
						SwapOrCopy<T>::apply(target_it->second, old_value);
						new_value = &(target_it->second = source_it->second);
						return true;
					} else {
						new_value = &(_key_to_value_map[targetID] = source_it->second);
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.find(sourceID);
				if (source_it != _key_to_value_map.end()) { 
					typename KeyToValueMap::iterator target_it = _key_to_value_map.find(targetID);
					if (target_it != _key_to_value_map.end()) { 
						if (source_it->second == target_it->second) {
							return false;
						}
						target_it->second = source_it->second;
						_key_to_value_map.erase(source_it);
						return true;
					} else {
						_key_to_value_map[targetID] = source_it->second;
						_key_to_value_map.erase(source_it);
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.find(sourceID);
				if (source_it != _key_to_value_map.end()) { 
					typename KeyToValueMap::iterator target_it = _key_to_value_map.find(targetID);
					if (target_it != _key_to_value_map.end()) { 
						if (source_it->second == target_it->second) {
							return false;
						}
						SwapOrCopy<T>::apply(target_it->second, old_value);
						new_value = &(target_it->second = source_it->second);
						_key_to_value_map.erase(source_it);
						return true;
					} else {
						new_value = &(_key_to_value_map[targetID] = source_it->second);
						_key_to_value_map.erase(source_it);
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const T& value) {
				typename KeyToValueMap::iterator it = _key_to_value_map.find(objectID);
				if (it != _key_to_value_map.end()) { 
					if (value == it->second) {
						return false;
					}
					it->second = value; 
					return true;
				} else {
					_key_to_value_map[objectID] = value;
					return true;
				}
			}
			
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) {
				typename KeyToValueMap::iterator it = _key_to_value_map.find(objectID);
				if (it != _key_to_value_map.end()) { 
					if (value == it->second) {
						return false;
					}
					SwapOrCopy<T>::apply(it->second, old_value);
					new_value = &(it->second = value); 
					return true;
				} else {
					new_value = &(_key_to_value_map[objectID] = value);
					return true;
				}
			}
			
			virtual const T* find(const I& objectID) const {
				typename KeyToValueMap::const_iterator it = _key_to_value_map.find(objectID);
				if (it != _key_to_value_map.end()) { 
					return &(it->second);
				} else {
					return NULL;
				}
			}
			
			virtual const T& get(const I& objectID) { return _key_to_value_map[objectID]; }
			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename Alloc>
		class SingleStorage<I, T, std::vector<T, Alloc> > :
		public ITemplateStorage<I, T, false>
		{
		public:
#if 0 // try to 
			class VectorCollection : public Collection<T, void, const std::vector<T, Alloc>& > {
			public:
				typedef Collection<const T&, void, const std::vector<T, Alloc> > Collection;
			public:
				VectorCollection(const std::vector<T, Alloc>& container) : Collection(container) {}
				
			public:
				
			};
			
			class Modifier<Collection<I, const T&, void>, Collection<const T&, void, const std::vector<T, Alloc> > > {
			};
			
			class VectorCollection {
			public:
				typedef typename internal::Type<first_template>::type first_type;
				typedef typename internal::Type<first_template>::const_type const_first_type;
				typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
				typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
				typedef typename internal::Type<first_template>::const_template_type const_template_first_type;
				typedef typename internal::Type<second_template>::type second_type;
				typedef typename internal::Type<second_template>::const_type const_second_type;
				typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
				typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
				typedef typename internal::Type<second_template>::const_template_type const_template_second_type;
			public:
				typedef Collection<void, const T&, const std::vector<T, Alloc> > Collection;
				
			public:
				Collection _collection;
				
			VectorCollection	
			public:
				
				//! @return the first_type value
				I at_first(size_t steps) { return steps; }
				
				//! @return the first_type value
				I at_first(size_t steps) const { return steps; }
				
				//! @return the second_type value
				const T& at_second(size_t steps) { return _collection.at_first(steps); }
				
				//! @return the second_type value
				const T& at_second(size_t steps) const { return _collection.at_first(steps); }
				
				//! @return the first_type value
				I first(size_t steps) { return steps; }
				
				//! @return the first_type value
				I first(size_t steps) const { return steps; }
				
				//! @return the second_type value
				const T& second(size_t steps) { return _collection.first(steps); }
				
				//! @return the second_type value
				const T& second(size_t steps) const { return _collection.first(steps); }
								
				//! @return true if an occurrence of first exists in the current collection.
				bool exist_first(const I& first) const { return _collection.size() > first; }
				
				//! @return true if an occurrence of second exists in the current collection.
				bool exist_second(const_ref_second_type second) const { return Bridge::existSecond(second); }
				
				//! @return true if an occurrence of second exists in the current collection.
				bool exist(const_ref_first_type first, const_ref_second_type second) const { return Bridge::existPair(first, second); }
				
				
				
			};
#endif
			
		public:
			typedef std::vector<T, Alloc> KeyToValueMap;
			
		public:
			KeyToValueMap _key_to_value_map;
	
		public:
			virtual bool exist(const I& objectID) const { return objectID < _key_to_value_map.size(); }
			
			virtual Query<I> all() const {
				return content();
			}
			
			virtual Query<I, const T&> content() const {
				return Query<I, const T&, const KeyToValueMap&>(_key_to_value_map);
			}
			
			virtual bool unset(const I& objectID) {
				// illegal operation
				return false;
			}
			
			virtual bool unset(const I& objectID, T& old_value) {
				// illegal operation
				return false;
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.begin() + sourceID;
				if (source_it < _key_to_value_map.end()) { 
					if (targetID < _key_to_value_map.size()) {
						typename KeyToValueMap::iterator target_it = _key_to_value_map.begin() + targetID;
						if (*source_it == *target_it) {
							return false;
						}
						*target_it = *source_it;
						return true;
					} else {
						_key_to_value_map.resize(targetID + 1);
						_key_to_value_map[targetID] = source_it->second;
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				if (sourceID == targetID) {
					return false;
				}
				typename KeyToValueMap::iterator source_it = _key_to_value_map.begin() + sourceID;
				if (source_it < _key_to_value_map.end()) { 
					if (targetID < _key_to_value_map.size()) {
						typename KeyToValueMap::iterator target_it = _key_to_value_map.begin() + targetID;
						if (*source_it == *target_it) {
							return false;
						}
						SwapOrCopy<T>::apply(*target_it, old_value);
						*target_it = *source_it;
						new_value = &(*target_it);
						return true;
					} else {
						_key_to_value_map.resize(targetID + 1);
						new_value = &(_key_to_value_map[targetID] = source_it->second);
						return false;
					}
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID) {
				// illegal operation
				return false;
			}
			
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				// illegal operation
				return false;
			}
			
			virtual bool set(const I& objectID, const T& value) {
				typename KeyToValueMap::iterator it = _key_to_value_map.begin() + objectID;
				if (it < _key_to_value_map.end()) { 
					if (value == *it) {
						return false;
					}
					*it = value; 
					return true;
				} else {
					if (objectID >= _key_to_value_map.size()) {
						_key_to_value_map.resize(objectID + 1);
					}
					_key_to_value_map[objectID] = value;
					return true;
				}
			}
			
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) {
				typename KeyToValueMap::iterator it = _key_to_value_map.begin() + objectID;
				if (it < _key_to_value_map.end()) {
					if (value == *it) {
						return false;
					}
					SwapOrCopy<T>::apply(*it, old_value);
					*it = value; 
					new_value = &(*it);
					return true;
				} else {
					if (objectID >= _key_to_value_map.size()) {
						_key_to_value_map.resize(objectID + 1);
					}
					new_value = &(_key_to_value_map[objectID] = const_cast<T&> (value));
					return true;
				}
			}
			
			virtual const T* find(const I& objectID) const {
				typename KeyToValueMap::const_iterator it = _key_to_value_map.begin() + objectID;
				if (it < _key_to_value_map.end()) { 
					return &(*it);
				} else {
					return NULL;
				}
			}
			
			virtual const T& get(const I& objectID) { 
				typename KeyToValueMap::const_iterator it = _key_to_value_map.begin() + objectID;
				if (it < _key_to_value_map.end()) { 
					return *it;
				} else {
					_key_to_value_map.resize(objectID + 1);
					return _key_to_value_map[objectID];
				}
			}
			
		};
		
	}
}