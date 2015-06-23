/*
 *  lazy4_internal_DualStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/06/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IDualStorage.h"
#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_Iterator.h"


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C = false, bool D = false >
		class DualStorage :
		public IDualStorage<I, T, C, D>
		{
		public:
			typedef T J;
			typedef I U;
			
			
		public:
			typedef typename internal2::ITemplateStorage<I, T, C> ITemplateStorage;
			typedef typename internal2::ITemplateStorage<J, U, D> IAssociateStorage;
			
		public:
			ITemplateStorage* _value_storage;
			IAssociateStorage* _associate_storage;
			
		public:
			virtual IAssociateStorage* get_associate_storage() const { return _associate_storage; }
			
			virtual void set_associate_storage(IAssociateStorage* storage) { _associate_storage = storage; }
			
			virtual ITemplateStorage* get_value_storage() const { return _value_storage; }
			
			virtual void set_value_storage(ITemplateStorage* storage) { _value_storage = storage; }
			
		public:
			virtual bool exist(const I& objectID) const { return (*_value_storage).exist(objectID); }
			
			virtual Query<I> all() const { return all_associate(); }
			
			virtual Query<I, const T&> content() const { return (*_value_storage).content(); }
			
			virtual bool unset(const I& objectID) {
				T old_value;
				return unset(objectID, old_value);
			}
			
			virtual bool unset(const I& objectID, T& old_value) { 
				if ((*_value_storage).unset(objectID, old_value)) {
					(*_associate_storage).unset(old_value);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) { 
				T old_value;
				const T* new_value;
				return move(sourceID, targetID, new_value, old_value);
			}
			
			virtual bool move(const I& sourceID, const I& targetID) { 
				T old_value;
				const T* new_value;
				return move(sourceID, targetID, new_value, old_value);
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) { 
				new_value = NULL;
				if ((*_value_storage).copy(sourceID, targetID, new_value, old_value)) {
					return (*_associate_storage).copy(old_value, *new_value);
				} else if (new_value) {
					(*_associate_storage).set(*new_value, targetID);
					return false;
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) { 
				if (sourceID == targetID) {
					return false;
				}
				new_value = NULL;
				if ((*_value_storage).move(sourceID, targetID, new_value, old_value)) {
					return (*_associate_storage).move(old_value, *new_value);
				} else if (new_value) {
					(*_associate_storage).set(*new_value, targetID);
					return false;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const T& value) { 
				T old_value;
				const T* new_value;
				return set(objectID, value, new_value, old_value);
			}
			
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) { 
				if ((*_value_storage).set(objectID, value, new_value, old_value)) {
					return (*_associate_storage).move(old_value, *new_value);
				} else {
					return false;
				}
			}
			
			virtual const T* find(const I& objectID) const { return (*_value_storage).find(objectID); }
			
			virtual const T& get(const I& objectID) { return (*_value_storage).get(objectID); }
			
		public:
			virtual bool set_associate(const J& objectID, const U& value) {
				const U* new_value;
				U old_value;
				return set_associate(objectID, value, new_value, old_value); 
			}
			
			virtual bool set_associate(const J& objectID, const U& value, const U*& new_value, U& old_value) { 
				if ((*_associate_storage).set(objectID, value, new_value, old_value)) {
					return (*_value_storage).move(old_value, *new_value);
				} else {
					return false;
				}
			}
			
			virtual const U* find_associate(const J& objectID) const { return (*_associate_storage).find(objectID); }
			
			virtual const U& get_associate(const J& objectID) { return (*_associate_storage).get(objectID); }
			
			virtual Query<J, const U&> content_associate() const { return (*_associate_storage).content(); }
			
			virtual bool unset_associate(const J& objectID) { 
				U old_value;
				return unset_associate(objectID, old_value); 
			}
			
			virtual bool unset_associate(const J& objectID, U& old_value) {
				if ((*_associate_storage).unset(objectID, old_value)) {
					(*_value_storage).unset(old_value);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool exist_associate(const J& objectID) const { return (*_associate_storage).exist(objectID); }
			
			virtual Query<J> all_associate() const { return (*_associate_storage).all(); }
			
			virtual bool copy_associate(const J& sourceID, const J& targetID) { 
				/* illegal operation */
				return false; 
			}
			
			virtual bool move_associate(const J& sourceID, const J& targetID) { 
				const U* new_value;
				U old_value;
				if ((*_associate_storage).move(sourceID, targetID, new_value, old_value)) {
					return (*_value_storage).move(old_value, *new_value);
				} else {
					return false;
				}
			}			
		};
		
#if 0 // FIWME: work must go on ...	
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I>
		class DualStorage<I, true, true> :
		public IDualStorage<I, true, true>
		{
		public:
			typedef I T;
			typedef I J;
			typedef I U;

		public:
			typedef typename internal::ITemplateStorage<I, T, true> ITemplateStorage;
			typedef typename internal::ITemplateStorage<I, T, true> IAssociateStorage;
			
		public:
			IAssociateStorage* _associate_storage;
			ITemplateStorage* _value_storage;
			
		public:
			virtual IAssociateStorage* get_associative_storage() const { return _associate_storage; }
			
			virtual void set_associative_storage(IAssociateStorage* storage) { _associate_storage = storage; }
			
			virtual ITemplateStorage* get_value_storage() const { return _value_storage; }
			
			virtual void set_value_storage(ITemplateStorage* storage) { _value_storage = storage; }
			
		public:
			virtual bool exist(const I& objectID) const { return (*_value_storage).exist(objectID); }
			
			virtual Query<I> all() const { return (*_value_storage).all(); }
			
			virtual Query<I, Collection<const T&> > content() const { return (*_value_storage).content(); }
			
			virtual bool unset(const I& objectID) { 
				Collection<const T&> old_value_collection;
				return unset(objectID, old_value_collection);
			}
			
			virtual bool unset(const I& objectID, Collection<const T&>& old_value_collection) { 
				if ((*_value_storage).unset(objectID, old_value_collection)) {
					for (Iterator<const T&> old_value_it = old_value_collection.begin(); !old_value_it.eof(); ++old_value_it) {
						const T& old_value = *old_value_it;
						(*_associate_storage).erase(old_value, objectID);
					}
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) { 
				Collection<const T&> new_value_collection;
				Collection<const T&> old_value_collection;
				return (*_associate_storage).copy(sourceID, targetID, new_value_collection, old_value_collection); 
			}
			
			virtual bool move(const I& sourceID, const I& targetID) { 
				Collection<const T&> new_value_collection;
				Collection<const T&> old_value_collection;
				return (*_associate_storage).move(sourceID, targetID, new_value_collection, old_value_collection); 
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) { 
				if ((*_value_storage).copy(sourceID, targetID, new_value_collection, old_value_collection)) {
					for (Iterator<const T&> old_value_it = old_value_collection.begin(); !old_value_it.eof(); ++old_value_it) {
						const T& old_value = *old_value_it;
						(*_associate_storage).erase(old_value, targetID);
					}
					for (Iterator<const T&> new_value_it = new_value_collection.begin(); !new_value_it.eof(); ++new_value_it) {
						const T& new_value = *new_value_it;
						(*_associate_storage).add(new_value, targetID);
					}
					return true;
				} else {
					for (Iterator<const T&> new_value_it = new_value_collection.begin(); !new_value_it.eof(); ++new_value_it) {
						const T& new_value = *new_value_it;
						(*_associate_storage).add(new_value, targetID);
					}
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) { 
				if ((*_value_storage).copy(sourceID, targetID, new_value_collection, old_value_collection)) {
					for (Iterator<const T&> old_value_it = old_value_collection.begin(); !old_value_it.eof(); ++old_value_it) {
						const T& old_value = *old_value_it;
						(*_associate_storage).erase(old_value, targetID);
					}
					for (Iterator<const T&> new_value_it = new_value_collection.begin(); !new_value_it.eof(); ++new_value_it) {
						const T& new_value = *new_value_it;
						(*_associate_storage).replace(new_value, sourceID, targetID);
					}
					return true;
				} else {
					for (Iterator<const T&> new_value_it = new_value_collection.begin(); !new_value_it.eof(); ++new_value_it) {
						const T& new_value = *new_value_it;
						(*_associate_storage).replace(new_value, sourceID, targetID);
					}
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value_collection) {
				Collection<const T&> old_value_collection;
				return set(objectID, value_collection, old_value_collection);
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value_collection, Collection<const T&>& old_value_collection) {
				if ((*_value_storage).set(objectID, value_collection, 
					+)) {
					for (Iterator<const T&> old_value_it = old_value_collection.begin(); !old_value_it.eof(); ++old_value_it) {
						const T& old_value = *old_value_it;
						(*_associate_storage).erase(old_value, objectID);
					}
					for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it) {
						const T& value = *value_it;
						(*_associate_storage).add(value, objectID);
					}
					return true;
				} else {
					return false;
				}
			}

			
			
			virtual bool find(const I& objectID, Collection<const T&>& value) const { return (*_value_storage).find(objectID, value); }
			
			virtual Collection<const T&> get(const I& objectID) { return (*_value_storage).get(objectID); }
			
		public:
			virtual bool add(const I& objectID, const T& value) {
				if ((*_value_storage).add(objectID, value)) {
					return (*_associate_storage).add(value, objectID);
				} else {
					return false;
				}
			}
			
			virtual bool add(const I& objectID, const Collection<const T&>& value_collection) {
				bool added = false;
				for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it) {
					T& value = const_cast<T&> (*value_it);
					added |= add(objectID, value);
				}
				return added;
			}
			
			virtual bool insert(const I& objectID, const T& value) { 
				if ((*_value_storage).add(objectID, value)) {
					return (*_associate_storage).add(value, objectID);
				} else {
					return false;
				}
			} 
			
			virtual bool insert(const I& objectID, const T& value, size_t position) {
				return (*_value_storage).insert(objectID, get_key(value), position); 
			} 
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value) { 
				static Modifier<const E&, const T&, const IKeyStorage& > modifier(value_to_enum_function, (*_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_associate_storage).insert(objectID, enum_collection); 
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value, size_t position) { 
				static Modifier<const E&, const T&, const IKeyStorage& > modifier(value_to_enum_function, (*_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_associate_storage).insert(objectID, enum_collection, position); 
			}
			
			virtual bool erase(const I& objectID, size_t position) { return (*_associate_storage).erase(objectID, position); }
			
			virtual bool erase(const I& objectID, size_t position, size_t size) { return (*_associate_storage).erase(objectID, position, size); }
			
			virtual bool erase(const I& objectID, const T& value) { return (*_associate_storage).erase(objectID, get_key(value)); }
			
			virtual bool erase(const I& objectID, const Collection<const T&>& value) {
				static Modifier<const E&, const T&, const IKeyStorage& > modifier(value_to_enum_function, (*_value_storage));
				Collection<const E&> enum_collection = value.change_first(modifier);
				return (*_associate_storage).erase(objectID, enum_collection); 
			}
			
			virtual bool erase(const I& objectID, size_t position, T& old_value) {
				E old_enum;
				if ((*_associate_storage).erase(objectID, position, old_enum)) {
					old_value = get_value(old_enum);
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t size, Collection<const T&>& old_value_collection) { 
				static Modifier<const T&, const E&, const IKeyStorage& > modifier(enum_to_value_function, (*_value_storage));
				Collection<const E&> old_enum_collection;
				if ((*_associate_storage).erase(objectID, position, size, old_enum_collection)) {
					old_value_collection = old_enum_collection.change_first(modifier);
					return true;
				} else {
					return false;
				}
			}
			
			
			virtual bool replace(const I& objectID, const T& value, const T& new_value) {
				if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
					typename ValueVector::iterator vec_it = std::find((*targetVec).begin(), (*targetVec).end(), const_cast<T&> (value));
					if (vec_it != (*targetVec).end()) {
						(*vec_it) = new_value;
						return true;
					}
				} 
				return false;
			}

		public:
			virtual bool set_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_associate_storage).set(objectID, enum_value_collection); }
			
			virtual bool set_associate(const J& objectID, const Collection<const U&>& enum_value_collection, Collection<const U&>& old_enum_value_collection) { return (*_associate_storage).set(objectID, enum_value_collection, old_enum_value_collection); }
			
			virtual bool find_associate(const J& objectID, Collection<const U&>& enum_value_collection) const { return (*_associate_storage).find(objectID, enum_value_collection); }
			
			virtual Query<J, Collection<const U&> > content_associate() const { return (*_associate_storage).content(); }
			
			virtual Collection<const U&> get_associate(const J& objectID) { return (*_associate_storage).get(objectID); }
			
			virtual bool unset_associate(const J& objectID) { return (*_associate_storage).unset(objectID); }
			
			virtual bool unset_associate(const J& objectID, Collection<const U&>& old_enum_value_collection) { return (*_associate_storage).unset(objectID, old_enum_value_collection); }
			
			virtual bool exist_associate(const J& objectID) const { return (*_associate_storage).exist(objectID); }
			
			virtual Query<J> all_associate() const { return (*_associate_storage).all(); }
			
			virtual bool copy_associate(const J& sourceID, const J& targetID) { return (*_associate_storage).copy(sourceID, targetID); }
			
			virtual bool move_associate(const J& sourceID, const J& targetID) { return (*_associate_storage).move(sourceID, targetID); }
			
		public:
			virtual bool insert_associate(const J& objectID, const U& enum_value) { return (*_associate_storage).insert(objectID, enum_value); }
			
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_associate_storage).insert(objectID, enum_value_collection); }
			
			virtual bool insert_associate(const J& objectID, const U& enum_value, size_t position) { return (*_associate_storage).insert(objectID, enum_value, position); }
			
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& enum_value_collection, size_t position) { return (*_associate_storage).insert(objectID, enum_value_collection, position); }
			
			virtual bool erase_associate(const J& objectID, const Collection<const U&>& enum_value_collection) { return (*_associate_storage).erase(objectID, enum_value_collection); }
			
			virtual bool erase_associate(const J& objectID, const U& enum_value) { return (*_associate_storage).erase(objectID, enum_value); }
			
			virtual bool erase_associate(const J& objectID, size_t position) { return (*_associate_storage).erase(objectID, position); }
			
			virtual bool erase_associate(const J& objectID, size_t position, size_t count) { return (*_associate_storage).erase(objectID, position, count); }
			
			virtual bool erase_associate(const J& objectID, size_t position, U& old_enum_value) { return (*_associate_storage).erase(objectID, position, old_enum_value); }
			
			virtual bool erase_associate(const J& objectID, size_t position, size_t count, Collection<const U&>& old_enum_value_collection) { return (*_associate_storage).erase(objectID, position, count, old_enum_value_collection); }
			
		};
#endif
			
	}
}