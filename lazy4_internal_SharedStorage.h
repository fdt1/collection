/*
 *  lazy4_internal_SharedStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ISharedStorage.h"
#include "lazy4_internal_IBijectiveStorage.h"
#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_Modifier.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C, typename E >
		class SharedStorage :
		public ISharedStorage<I, T, C, E>
		{
		public:
			typedef I J;
			typedef E U;
			typedef IBijectiveStorage<E, T, false> IBijectiveStorage;
			typedef ITemplateStorage<I, E, C> ITemplateStorage;
			
		public:
			IBijectiveStorage* _enum_to_value_storage;
			ITemplateStorage* _key_to_enum_storage;
			
		public:
			static const T& enum_to_value_function(const E& enum_value, const IBijectiveStorage& enum_to_value_storage) { return const_cast<IBijectiveStorage&> (enum_to_value_storage).get(enum_value); }
			
			static const E& value_to_enum_function(const T& value, const IBijectiveStorage& enum_to_value_storage) { return const_cast<IBijectiveStorage&> (enum_to_value_storage).get_key(value); }
			
		public:
			virtual IBijectiveStorage* get_key_storage() const { return _enum_to_value_storage; }
			
			virtual void set_key_storage(IBijectiveStorage* storage) { _enum_to_value_storage = storage; }
			
			virtual ITemplateStorage* get_value_storage() const { return _key_to_enum_storage; }

			virtual void set_value_storage(ITemplateStorage* storage) { _key_to_enum_storage = storage; }
		
		public:
			virtual bool exist(const I& objectID) const { return (*_key_to_enum_storage).exist(objectID); }
			
			virtual Query<I> all() const { return all_associate(); }
			
			virtual Query<I, const T&> content() const {
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				return content_associate().change_second(modifier);
			}
			
			virtual bool unset(const I& objectID) { return (*_key_to_enum_storage).unset(objectID); }
			
			virtual bool unset(const I& objectID, T& old_value) { 
				E old_key;
				if ((*_key_to_enum_storage).unset(objectID, old_key)) {
					old_value = get_value(old_key);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) { return (*_key_to_enum_storage).copy(sourceID, targetID); }
			
			virtual bool move(const I& sourceID, const I& targetID) { return (*_key_to_enum_storage).move(sourceID, targetID); }
			
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) { 
				const E* new_key;
				E old_key;
				if ((*_key_to_enum_storage).copy(sourceID, targetID, new_key, old_key)) {
					new_value = find_value(*new_key);
					old_value = get_value(old_key);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) { 
				const E* new_key;
				E old_key;
				if ((*_key_to_enum_storage).move(sourceID, targetID, new_key, old_key)) {
					new_value = find_value(*new_key);
					old_value = get_value(old_key);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const T& value) { return (*_key_to_enum_storage).set(objectID, get_key(value)); }
			
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) { 
				E old_key;
				const E* new_key;
				if ((*_key_to_enum_storage).set(objectID, get_key(value), new_key, old_key)) {
					new_value = find_value(*new_key);
					old_value = get_value(old_key);
					return true;
				} else {
					return false;
				}
			}
			
			virtual const T* find(const I& objectID) const { 
				if (const E* enum_value = (*_key_to_enum_storage).find(objectID)) { 
					return find_value(*enum_value); 
				} else {
					return NULL;
				}
			}
			
			virtual const T& get(const I& objectID) { 
				const E& enum_value = (*_key_to_enum_storage).get(objectID);
				return get_value(enum_value); 
			}
			
		public:
			virtual bool set_associate(const J& objectID, const U& enum_value) { return (*_key_to_enum_storage).set(objectID, enum_value); }
			
			virtual bool set_associate(const J& objectID, const U& enum_value, const U*& new_value, U& old_enum_value) { return (*_key_to_enum_storage).set(objectID, enum_value, new_value, old_enum_value); }
			
			virtual const U* find_associate(const J& objectID) const { return (*_key_to_enum_storage).find(objectID); }
			
			virtual const U& get_associate(const J& objectID) { return (*_key_to_enum_storage).get(objectID); }
			
			virtual Query<J, const U&> content_associate() const { return (*_key_to_enum_storage).content(); }
			
			virtual bool unset_associate(const J& objectID) { return unset(objectID); }
			
			virtual bool unset_associate(const J& objectID, U& old_enum_value) {
				T old_value;
				if (unset(objectID, old_value)) { 
					old_enum_value = get_key(old_value);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool exist_associate(const J& objectID) const { return exist(objectID); }
			
			virtual Query<J> all_associate() const { return content_associate(); }
			
			virtual bool copy_associate(const J& sourceID, const J& targetID) { return copy(sourceID, targetID); }
			
			virtual bool move_associate(const J& sourceID, const J& targetID) { return move(sourceID, targetID); }
			
		public:
			virtual const E* find_key(const T& value) const { return (*_enum_to_value_storage).find_associate(value); }
			
			virtual const E& get_key(const T& value) { return (*_enum_to_value_storage).get_associate(value); }
			
			virtual const T& get_value(const E& enum_value) { return (*_enum_to_value_storage).get(enum_value); }
			
			virtual const T* find_value(const E& enum_value) const { return (*_enum_to_value_storage).find(enum_value); }
			
			virtual bool set_key(const E& enum_value, const T& value) { return (*_enum_to_value_storage).set(enum_value, value); } 
			
			virtual bool set_key(const E& enum_value, const T& value, const T*& new_value, T& old_value) { return (*_enum_to_value_storage).set(enum_value, value, new_value, old_value); } 
			
		};

		
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename E>
		class SharedStorage<I, T, true, E> :
		public ISharedStorage<I, T, true, E>
		{
		public:
			typedef I J;
			typedef E U;
			typedef IBijectiveStorage<E, T> IBijectiveStorage;
			typedef ITemplateStorage<I, E, true> ITemplateStorage;
			
		public:
			ITemplateStorage* _key_to_enum_storage;
			IBijectiveStorage* _enum_to_value_storage;
			
		public:
			static const T& enum_to_value_function(const E& enum_value, const IBijectiveStorage& enum_to_value_storage) { return const_cast<IBijectiveStorage&> (enum_to_value_storage).get(enum_value); }
			
			static const E& value_to_enum_function(const T& value, const IBijectiveStorage& enum_to_value_storage) { return const_cast<IBijectiveStorage&> (enum_to_value_storage).get_associate(value); }
			
			static Collection<const T&> enum_collection_to_value_collection_function(const Collection<const E&>& enum_collection, const IBijectiveStorage& enum_to_value_storage) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, enum_to_value_storage);
				return enum_collection.change_first(modifier); 
			}
			
		public:
			virtual IBijectiveStorage* get_key_storage() const { return _enum_to_value_storage; }
			
			virtual void set_key_storage(IBijectiveStorage* storage) { _enum_to_value_storage = storage; }
			
			virtual ITemplateStorage* get_value_storage() const { return _key_to_enum_storage; }
			
			virtual void set_value_storage(ITemplateStorage* storage) { _key_to_enum_storage = storage; }
			
		public:
			virtual bool exist(const I& objectID) const { return (*_key_to_enum_storage).exist(objectID); }
			
			virtual Query<I> all() const { return content_associate(); }
			
			virtual Query<I, Collection<const T&> > content() const {
				static Modifier<Collection<const T&>, Collection<const E&>, const IBijectiveStorage& > modifier(enum_collection_to_value_collection_function, (*_enum_to_value_storage));
				return content_associate().change_second(modifier);
			}
			
			virtual bool unset(const I& objectID) { return (*_key_to_enum_storage).unset(objectID); }
			
			virtual bool unset(const I& objectID, Collection<const T&>& old_value_collection) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> old_key_collection;
				if ((*_key_to_enum_storage).unset(objectID, old_key_collection)) {
					old_value_collection = old_key_collection.change_first(modifier);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) { return (*_key_to_enum_storage).copy(sourceID, targetID); }
			
			virtual bool move(const I& sourceID, const I& targetID) { return (*_key_to_enum_storage).move(sourceID, targetID); }
			
			virtual bool copy(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> new_key_collection;
				Collection<const E&> old_key_collection;
				if ((*_key_to_enum_storage).copy(sourceID, targetID, new_key_collection, old_key_collection)) {
					old_value_collection = old_key_collection.change_first(modifier);
					new_value_collection = new_key_collection.change_first(modifier);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> new_key_collection;
				Collection<const E&> old_key_collection;
				if ((*_key_to_enum_storage).move(sourceID, targetID, new_key_collection, old_key_collection)) {
					old_value_collection = old_key_collection.change_first(modifier);
					new_value_collection = new_key_collection.change_first(modifier);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value) {
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_key_to_enum_storage).set(objectID, enum_collection);
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value, Collection<const T&>& old_value) {
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier2(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				Collection<const E&> old_enum;
				if ((*_key_to_enum_storage).set(objectID, enum_collection, old_enum)) {
					old_value = old_enum.change_first(modifier2);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool find(const I& objectID, Collection<const T&>& value) const {
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection;
				if ((*_key_to_enum_storage).find(objectID, enum_collection)) {
					value = enum_collection.change_first(modifier);
					return true;
				} else {
					value = Collection<const T&>();
					return false;
				}
			}
			
			virtual Collection<const T&> get(const I& objectID) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = (*_key_to_enum_storage).get(objectID);
				return enum_collection.change_first(modifier);
			}
			
		public:
			virtual bool add(const I& objectID, const T& value) { return (*_key_to_enum_storage).add(objectID, get_key(value)); } 
			
			virtual bool add(const I& objectID, const Collection<const T&>& value) { 
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_key_to_enum_storage).add(objectID, enum_collection); 
			}
			
			virtual bool insert(const I& objectID, const T& value) { return (*_key_to_enum_storage).insert(objectID, get_key(value)); } 
			
			virtual bool insert(const I& objectID, const T& value, size_t position) { return (*_key_to_enum_storage).insert(objectID, get_key(value), position); } 
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value) { 
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_key_to_enum_storage).insert(objectID, enum_collection); 
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value, size_t position) { 
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_key_to_enum_storage).insert(objectID, enum_collection, position); 
			}
			
			virtual bool erase(const I& objectID, size_t position) { return (*_key_to_enum_storage).erase(objectID, position); }
			
			virtual bool erase(const I& objectID, size_t position, size_t size) { return (*_key_to_enum_storage).erase(objectID, position, size); }
			
			virtual bool erase(const I& objectID, const T& value) { return (*_key_to_enum_storage).erase(objectID, get_key(value)); }
			
			virtual bool erase(const I& objectID, const Collection<const T&>& value) {
				static Modifier<const E&, const T&, const IBijectiveStorage& > modifier(value_to_enum_function, (*_enum_to_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_key_to_enum_storage).erase(objectID, enum_collection); 
			}
			
			virtual bool erase(const I& objectID, size_t position, T& old_value) {
				E old_enum;
				if ((*_key_to_enum_storage).erase(objectID, position, old_enum)) {
					old_value = get_value(old_enum);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t size, Collection<const T&>& old_value_collection) { 
				static Modifier<const T&, const E&, const IBijectiveStorage& > modifier(enum_to_value_function, (*_enum_to_value_storage));
				Collection<const E&> old_enum_collection;
				if ((*_key_to_enum_storage).erase(objectID, position, size, old_enum_collection)) {
					old_value_collection = old_enum_collection.change_first(modifier);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool replace(const I& objectID, const T& value, const T& new_value)  { return (*_key_to_enum_storage).replace(objectID, get_key(value), get_key(new_value)); }
			
		public:
			virtual bool set_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_key_to_enum_storage).set(objectID, enum_value_collection); }
			
			virtual bool set_associate(const J& objectID, const Collection<const U&>& enum_value_collection, Collection<const U&>& old_enum_value_collection) { return (*_key_to_enum_storage).set(objectID, enum_value_collection, old_enum_value_collection); }
			
			virtual bool find_associate(const J& objectID, Collection<const U&>& enum_value_collection) const { return (*_key_to_enum_storage).find(objectID, enum_value_collection); }
			
			virtual Query<J, Collection<const U&> > content_associate() const { return (*_key_to_enum_storage).content(); }
			
			virtual Collection<const U&> get_associate(const J& objectID) { return (*_key_to_enum_storage).get(objectID); }
			
			virtual bool unset_associate(const J& objectID) { return (*_key_to_enum_storage).unset(objectID); }
			
			virtual bool unset_associate(const J& objectID, Collection<const U&>& old_enum_value_collection) { return (*_key_to_enum_storage).unset(objectID, old_enum_value_collection); }
			
			virtual bool exist_associate(const J& objectID) const { return (*_key_to_enum_storage).exist(objectID); }
			
			virtual Query<J> all_associate() const { return (*_key_to_enum_storage).all(); }
			
			virtual bool copy_associate(const J& sourceID, const J& targetID) { return (*_key_to_enum_storage).copy(sourceID, targetID); }
			
			virtual bool move_associate(const J& sourceID, const J& targetID) { return (*_key_to_enum_storage).move(sourceID, targetID); }
			
		public:
			virtual bool add_associate(const J& objectID, const U& enum_value) { return (*_key_to_enum_storage).add(objectID, enum_value); } 
			
			virtual bool add_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_key_to_enum_storage).add(objectID, enum_value_collection); } 
			
			virtual bool insert_associate(const J& objectID, const U& enum_value) { return (*_key_to_enum_storage).insert(objectID, enum_value); }
			
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_key_to_enum_storage).insert(objectID, enum_value_collection); }
			
			virtual bool insert_associate(const J& objectID, const U& enum_value, size_t position) { return (*_key_to_enum_storage).insert(objectID, enum_value, position); }
			
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& enum_value_collection, size_t position) { return (*_key_to_enum_storage).insert(objectID, enum_value_collection, position); }
			
			virtual bool erase_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_key_to_enum_storage).erase(objectID, enum_value_collection); }
			
			virtual bool erase_associate(const J& objectID, const U& enum_value) { return (*_key_to_enum_storage).erase(objectID, enum_value); }
			
			virtual bool erase_associate(const J& objectID, size_t position) { return (*_key_to_enum_storage).erase(objectID, position); }
			
			virtual bool erase_associate(const J& objectID, size_t position, size_t count) { return (*_key_to_enum_storage).erase(objectID, position, count); }
			
			virtual bool erase_associate(const J& objectID, size_t position, U& old_enum_value) { return (*_key_to_enum_storage).erase(objectID, position, old_enum_value); }
			
			virtual bool erase_associate(const J& objectID, size_t position, size_t count, Collection<const U&>& old_enum_value_collection) { return (*_key_to_enum_storage).erase(objectID, position, count, old_enum_value_collection); }
			
			virtual bool replace_associate(const J& objectID, const U& enum_value, const U& new_enum_value) { return (*_key_to_enum_storage).replace(objectID, enum_value, new_enum_value); }
			
		public:
			virtual const E* find_key(const T& value) const { return (*_enum_to_value_storage).find_associate(value); }
			
			virtual const E& get_key(const T& value) { return (*_enum_to_value_storage).get_associate(value); }
			
			virtual const T& get_value(const E& enum_value) { return (*_enum_to_value_storage).get(enum_value); }
			
			virtual const T* find_value(const E& enum_value) const { return (*_enum_to_value_storage).find(enum_value); }
			
			virtual bool set_key(const E& enum_value, const T& value) { return (*_enum_to_value_storage).set(enum_value, value); } 
			
			virtual bool set_key(const E& enum_value, const T& value, const T*& new_value, T& old_value) { return (*_enum_to_value_storage).set(enum_value, value, new_value, old_value); } 
			
		};
		
	}
}