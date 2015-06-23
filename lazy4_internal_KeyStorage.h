/*
 *  lazy4_internal_KeyStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IBijectiveStorage.h"
#include "lazy4_internal_ITemplateStorage.h"


namespace lazy4 {
	
	namespace internal2 {
		
		
		template<typename I, typename T>
		class KeyStorage :
		public IBijectiveStorage<I, T, false>
		{
		public: 
			typedef T J;
			typedef I U;
			typedef ITemplateStorage<I, T, false> IKeyToValueStorage;
			typedef ITemplateStorage<T const*, I, false> IValueToKeyStorage;
			
		public:
			static const T& pointer_to_ref_function(T const* const& value) { return *value; }
			
		public:
			IKeyToValueStorage* _key_to_value_map;
			IValueToKeyStorage* _value_to_key_map;
			
		public:
			virtual IKeyToValueStorage* get_key_storage() const { return _key_to_value_map; }
			
			virtual void set_key_storage(IKeyToValueStorage* storage) { _key_to_value_map = storage; }
			
			virtual IValueToKeyStorage* get_value_storage() const { return _value_to_key_map; }
			
			virtual void set_value_storage(IValueToKeyStorage* storage) { _value_to_key_map = storage; }
			
		public:
			virtual bool exist(const I& objectID) const { return (*_key_to_value_map).exist(objectID); }
			
			virtual Query<I> all() const { return content(); }
			
			virtual Query<I, const T&> content() const { return (*_key_to_value_map).content(); }
			
			virtual bool unset(const I& objectID) {
				T old_value;
				return unset(objectID, old_value);
			}
			
			virtual bool unset(const I& objectID, T& old_value) {
				if ((*_key_to_value_map).unset(objectID, old_value)) {
					return (*_value_to_key_map).unset(&old_value);
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) {
				// illegal operation !
				return false;
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				// illegal operation !
				return false;
			}
			
			virtual bool move(const I& sourceID, const I& targetID) {
				const T* new_value;
				T old_value;
				return move(sourceID, targetID, new_value, old_value);
			}
			
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) {
				if (sourceID == targetID) {
					return false;
				}
				new_value = NULL;
				if ((*_key_to_value_map).move(sourceID, targetID, new_value, old_value)) {
					return (*_value_to_key_map).move(&old_value, new_value);
				} else if (new_value) {
					(*_value_to_key_map).set(new_value, targetID);
					return false;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const T& value) {
				const T* new_value;
				T old_value;
				return set(objectID, value, new_value, old_value);
			}
			
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) {
				new_value = NULL;
				if ((*_key_to_value_map).set(objectID, value, new_value, old_value)) {
					return (*_value_to_key_map).move(&old_value, new_value);
				} else if (new_value) {
					(*_value_to_key_map).set(new_value, objectID);
					return false;
				} else {
					return false;
				}
			}
			
			virtual const T* find(const I& objectID) const { return (*_key_to_value_map).find(objectID); }			
			
			virtual const T& get(const I& objectID) { return (*_key_to_value_map).get(objectID); }
			
		public:
			virtual bool set_associate(const J& value, const U& objectID) { return set(objectID, value); }
			
			virtual bool set_associate(const J& value, const U& objectID, const U*& new_objectID, U& old_objectID) { 
				new_objectID = NULL;
				if ((*_value_to_key_map).set(&value, objectID, new_objectID, old_objectID)) {
					return (*_key_to_value_map).move(old_objectID, *new_objectID);
				} else if (new_objectID) {
					(*_key_to_value_map).set(*new_objectID, value);
					return false;
				} else {
					return false;
				}
			}
			
			virtual const U* find_associate(const J& value) const { return (*_value_to_key_map).find(&value); }
			
			virtual const U& get_associate(const J& value) { return (*_value_to_key_map).get(&value); }
			
			virtual Query<J, const U&> content_associate() const { 
				static Modifier<const T&, const T*> modifier(pointer_to_ref_function);
				return (*_value_to_key_map).content().change_first(modifier);
			}
			
			virtual bool unset_associate(const J& value) { 
				U old_objectID;
				return unset_associate(value, old_objectID);
			}
			
			virtual bool unset_associate(const J& value, U& old_ojectID) {
				if ((*_value_to_key_map).unset(&value, old_ojectID)) {
					return (*_key_to_value_map).unset(old_ojectID);
				} else {
					return false;
				}
			}
			
			virtual bool exist_associate(const J& value) const { return (*_value_to_key_map).exist(&value); }
			
			virtual Query<J> all_associate() const { return content_associate(); }
			
			virtual bool copy_associate(const J& sourceID, const J& targetID) {
				// illegal operation
				return false;
			}
			
			virtual bool move_associate(const J& source_value, const J& target_value) {
				const U* new_objectID; 
				U old_objectID;
				return move_associate(source_value, target_value, new_objectID, old_objectID);
			}
			
			virtual bool move_associate(const J& source_value, const J& target_value, const U*& new_objectID, U& old_objectID) {
				if (source_value == target_value) {
					return false;
				}
				new_objectID = NULL;
				if ((*_value_to_key_map).move(&source_value, &target_value, new_objectID, old_objectID)) {
					return (*_key_to_value_map).move(old_objectID, *new_objectID);
				} else if (new_objectID) {
					(*_key_to_value_map).set(*new_objectID, target_value);
					return false;
				} else {
					return false;
				}
			}
			
		};
		
		
	}
	
	
}