/*
 *  lazy4_internal_CollectionStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 22/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ITemplateStorage.h"
#include "lazy4_Collection_std_vector.h"
#include "lazy4_Iterator.h"
#include <algorithm>
#include <vector>


namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename ValueVector>
		class CollectionStorage {
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename A >
		class CollectionStorage<I, T, std::vector<T, A> > :
		public ITemplateStorage<I, T, true >
		{
			
		public:
			typedef std::vector<T, A> ValueVector;
			typedef ITemplateStorage<I, ValueVector, false> IVectorStorage;
			
		public:
			IVectorStorage* _vector_storage;
			
		public:
			virtual IVectorStorage* get_vector_storage() const { return _vector_storage; }
			
			virtual void set_vector_storage(IVectorStorage* storage) { _vector_storage = storage; }
		public:
			virtual bool exist(const I& objectID) const { return (*_vector_storage).exist(objectID); }
			
			virtual Query<I> all() const { return (*_vector_storage).all(); }
			
			virtual Query<I, Collection<const T&> > content() const { 
				return Query<I, Collection<const T&, void, const ValueVector&> > ((*_vector_storage).content());
			}

			virtual bool unset(const I& objectID) { return (*_vector_storage).unset(objectID); }
			
			virtual bool unset(const I& objectID, Collection<const T&>& old_value_collection) {
				Collection<const T&, void, ValueVector> collection;
				if ((*_vector_storage).unset(objectID, collection.container())) { 
					// make a copy
					old_value_collection = collection;
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool copy(const I& sourceID, const I& targetID) { return (*_vector_storage).copy(sourceID, targetID); }
			
			virtual bool move(const I& sourceID, const I& targetID) { return (*_vector_storage).move(sourceID, targetID); }
			
			virtual bool copy(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) {
				const ValueVector* new_value = NULL;
				Collection<const T&, void, ValueVector> collection;
				if ((*_vector_storage).copy(sourceID, targetID, new_value, collection.container())) {
					new_value_collection = Collection<const T&, void, const ValueVector&> (*new_value);
					old_value_collection = collection;
					return true;
				} else if (new_value) {
					new_value_collection = Collection<const T&, void, const ValueVector&> (*new_value);
					return false;
				} else {
					return false;
				}
			}
			
			virtual bool move(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) {
				const ValueVector* new_value = NULL;
				Collection<const T&, void, ValueVector> collection;
				if ((*_vector_storage).move(sourceID, targetID, new_value, collection.container())) {
					new_value_collection = Collection<const T&, void, const ValueVector&> (*new_value);
					old_value_collection = collection;
					return true;
				} else if (new_value) {
					new_value_collection = Collection<const T&, void, const ValueVector&> (*new_value);
					return false;
				} else {
					return false;
				}
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				typename ValueVector::iterator target_it = targetVec.begin();
				typename ValueVector::iterator target_end = targetVec.end();
				bool modified = false;
				
				for (Iterator<const T&> value_it = value.begin(); !value_it.eof(); ++value_it, ++target_it) {
					const T& source_value = *value_it;
					if (target_it < target_end) {
						T& target_value = *target_it;
						if (!modified) {
							if (target_value == source_value) {
								continue;
							}
							modified = true;
						}
						target_value = source_value;
					} else {
						modified = true;
						targetVec.push_back(source_value); 
					}
				}
				return modified;
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value, Collection<const T&>& old_value) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				old_value = Collection<const T&, void, ValueVector>(targetVec);
				typename ValueVector::iterator target_it = targetVec.begin();
				typename ValueVector::iterator target_end = targetVec.end();
				bool modified = false;
				
				for (Iterator<const T&> value_it = value.begin(); !value_it.eof(); ++value_it, ++target_it) {
					const T& source_value = *value_it;
					if (target_it < target_end) {
						T& target_value = *target_it;
						if (!modified) {
							if (target_value == source_value) {
								continue;
							}
							modified = true;
						}
						target_value = source_value;
					} else {
						modified = true;
						targetVec.push_back(source_value); 
					}
				}
				return modified;
			}
			
			virtual bool find(const I& objectID, Collection<const T&>& value) const {
				if (const ValueVector* vectorValue = (*_vector_storage).find(objectID)) {
					value = Collection<const T&, void, const ValueVector&>(*vectorValue);
					return true;
				} else {
					return false;
				}
			}
			
			virtual Collection<const T&> get(const I& objectID) {
				const ValueVector& vectorValue = (*_vector_storage).get(objectID);
				return Collection<const T&, void, const ValueVector&>(vectorValue);
			}
			
		public:
			virtual bool add(const I& objectID, const T& value) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				typename ValueVector::iterator vec_it = std::find(targetVec.begin(), targetVec.end(), const_cast<T&> (value));
				if (vec_it == (targetVec).end()) {
					targetVec.push_back(value); 
					return true;
				} else {
					return false;
				}
			}
			
			virtual bool add(const I& objectID, const Collection<const T&>& value_collection) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				if (targetVec.empty()) {
					targetVec.insert(targetVec.begin(), value_collection.begin(), value_collection.end()); 
					return true;
				} else {
					bool added = false;
					for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it) {
						T& value = const_cast<T&> (*value_it);
						typename ValueVector::iterator vec_it = std::find((targetVec).begin(), (targetVec).end(), value);
						if (vec_it == (targetVec).end()) {
							targetVec.push_back(value); 
							added = true;
						}
					}
					return added;
				} 
			}
			
			virtual bool insert(const I& objectID, const T& value) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				targetVec.push_back(value); 
				return true;
			}
			
			virtual bool insert(const I& objectID, const T& value, size_t position) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				if (position >= targetVec.size()) {
					targetVec.resize(position + 1);
				}
				targetVec.insert(targetVec.begin() + position, value); 
				return true;
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				targetVec.insert(targetVec.begin(), value.begin(), value.end()); 
				return true;
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value, size_t position) {
				ValueVector& targetVec = const_cast<ValueVector&>((*_vector_storage).get(objectID));
				if (position >= targetVec.size()) {
					targetVec.resize(position + 1);
				}
				targetVec.insert(targetVec.begin() + position, value.begin(), value.end()); 
				return true;
			}
			
			virtual bool erase(const I& objectID, size_t position) {
				if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
					if (position < (*targetVec).size()) {
						(*targetVec).erase((*targetVec).begin() + position);
						return true;
					}
				}
				return false;
				
			}
			
			virtual bool erase(const I& objectID, size_t position, T& old_value) {
				if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
					if (position < (*targetVec).size()) {
						typename ValueVector::iterator vec_it = (*targetVec).begin() + position;
						old_value = *(vec_it);
						(*targetVec).erase(vec_it); 
						return true;
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t count) {
				if (count != 0) {
					if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
						if (position < (*targetVec).size()) {
							typename ValueVector::iterator vec_it = (*targetVec).begin() + position;
							typename ValueVector::iterator vec_end = vec_it + count;
							if (vec_end > (*targetVec).end()) {
								vec_end = (*targetVec).end();
							}
							(*targetVec).erase(vec_it, vec_end); 
							return true;
						}
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t count, Collection<const T&>& old_value) {
				if (count != 0) {
					if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
						if (position < (*targetVec).size()) {
							typename ValueVector::iterator vec_it = (*targetVec).begin() + position;
							typename ValueVector::iterator vec_end = vec_it + count;
							if (vec_end > (*targetVec).end()) {
								vec_end = (*targetVec).end();
							}
							// make a copy
							Collection<const T&, void, ValueVector> collection = Collection<const T&, void, ValueVector>((*targetVec));
							old_value = Collection<const T&, void>(collection.begin() + position, collection.begin() + (vec_end - vec_it));
							(*targetVec).erase(vec_it, vec_end); 
							return true;
						}
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, const T& value) {
				if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
					typename ValueVector::iterator vec_it = std::find((*targetVec).begin(), (*targetVec).end(), const_cast<T&> (value));
					if (vec_it != (*targetVec).end()) {
						(*targetVec).erase(vec_it);
						return true;
					}
				} 
				return false;
			}
			
			virtual bool erase(const I& objectID, const Collection<const T&>& value) {
				if (ValueVector* targetVec = const_cast<ValueVector*>((*_vector_storage).find(objectID))) {
					bool erased = false;
					for (Iterator<const T&> value_it = value.begin(); !value_it.eof(); ++value_it) {
						typename ValueVector::iterator vec_it = std::find((*targetVec).begin(), (*targetVec).end(), *value_it);
						if (vec_it != (*targetVec).end()) {
							(*targetVec).erase(vec_it);
							erased = true;
						}
					}
					return erased;
				}
				return false;
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
			
		};
		
	}
}