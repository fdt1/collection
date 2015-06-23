/*
 *  lazy4_internal_ChainStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 15/08/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IBijectiveStorage.h"
#include "lazy4_Iterator.h"
#include "lazy4_Collection_std_vector.h"
#include <algorithm>
#include <vector>


namespace lazy4 {
	
	namespace internal2 {
		
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename I, typename T, typename ValueVector = std::vector<T> >
		class ChainStorage :
		public ITemplateStorage<I, T, true >
		{
			
		public:
			typedef typename ValueVector::size_type Index;
			typedef ITemplateStorage<I, Index, false> IIndexStorage;
#if 0

		public:
			struct myCollection : lazy4::Collection<I, Index> {
				//! set the iterator to the primary occurrence of second from the current step.
				//! @return the corresponding Iterator set at the beginning.
				//Iterator find_second(const_ref_second_type second) { Iterator it = begin(); it.find_second(second); return it; }
		

			};
#endif

		public:
			ValueVector _value_vector;
			IIndexStorage* _index_storage;
			
		public:
			virtual IIndexStorage* get_index_storage() const { return _index_storage; }
			
			virtual void set_index_storage(IIndexStorage* storage) { _index_storage = storage; }
						
			
		public:
			// FIXME : Modifier<int, void> ???? 
			static const I& distance_function(void* enum_value, const IIndexStorage& key_to_value_map) { static I i; return i; }

			static bool find_collection(const I& objectID, const ChainStorage& chain_storage, Collection<const T&>& collection) { 
				static Collection<const T&, void, const ValueVector&> chain_collection = chain_storage._value_vector;
				if (const Index* begin_index = (*chain_storage._index_storage).find(objectID)) {
					Iterator<const T&, void, const ValueVector&> begin = chain_collection.begin() + (*begin_index);
					
					if (const Index* end_index = (*chain_storage._index_storage).find(objectID + 1)) {
						Iterator<const T&, void, const ValueVector&> end = chain_collection.begin() + (*end_index);
						collection = Collection<const T&>(begin, end);
					} else {
						collection = Collection<const T&>(begin, chain_collection.end());
					}
					return true;
				} else {
					return false;
				}
			}
			
			static Collection<const T&> index_to_value_function(const I& objectID, const ChainStorage& chain_storage) { 
				Collection<const T&> collection;
				find_collection(objectID, chain_storage, collection);
				return collection;
			}

		public:
			//! return the new begin index of objectID
			virtual Index shift(const I& begin_objectID, long long offset) {
				if (offset == 0) {
					return get_begin_index(begin_objectID);
				} 

				// shift all followers
				I end_objectID = static_cast<I> ((*_index_storage).all().size());
				
				// shift all followers
				shiftIndex(begin_objectID, end_objectID, offset);
				
				Index index = get_begin_index(begin_objectID);
				if (offset < 0) {
					_value_vector.erase(_value_vector.begin() + index, _value_vector.begin() + index + offset);
				} else {
					_value_vector.insert(_value_vector.begin() + index, offset, T());
				}
				
				return index;
			}
			
			virtual void shiftIndex(const I& begin_objectID, const I& end_objectID, long long offset) {
				if (offset == 0) {
					return;
				} 
				
				// shift all followers
				for (I objectID = begin_objectID; objectID != end_objectID; ++objectID) {
					Index& index = const_cast<Index&> ((*_index_storage).get(objectID));
					index += offset;
				}
			}
			
			virtual void rotateData(const Index& begin_index, const Index& end_index, long long offset) {
				if (offset == 0) {
					return;
				} 
				
				// shift all followers
				size_t size = end_index - begin_index;
				if (offset > 0) {
					for (Index index = begin_index; index != end_index; ++index) {
						_value_vector[(index + offset) % size] = _value_vector[index];
					}
				} else {
					for (Index index = end_index - 1; index >= begin_index; --index) {
						_value_vector[(index + offset) % size] = _value_vector[index];
					}
				}
			}
			
			virtual Index get_end_index(const I& objectID) {
				if (const Index* end_index = (*_index_storage).find(objectID + 1)) {
					return (*end_index);
				} else {
					return _value_vector.size();
				}
			}
			
			virtual Index get_begin_index(const I& objectID) {
				if (const Index* pt_begin_index = (*_index_storage).find(objectID)) {
					return (*pt_begin_index);
				} else {
					Index begin_index = _value_vector.size();
					// create all the missing elements
					for (size_t begin_objectID = (*_index_storage).all().size(); begin_objectID <= objectID; ++begin_objectID) {
						(*_index_storage).set(static_cast<I> (begin_objectID), begin_index);
					}
					return begin_index;
				}
			}
			
			virtual Index resize(const I& objectID, size_t size) {
				Index begin_index = get_begin_index(objectID);
				size_t current_size = get_end_index(objectID) - (begin_index);				
				shift(objectID + 1, size - current_size);
				return begin_index;
			}
	
		public:
			virtual bool exist(const I& objectID) const { return (*_index_storage).exist(objectID); }
			
			virtual Query<I> all() const { return (*_index_storage).all(); }
			
			virtual Query<I, Collection<const T&> > content() const { 
#if 1 //FIXME
				static Modifier<I, void, const IIndexStorage& > modifier(distance_function, (*_index_storage));
				static Modifier<Collection<const T&>, I, const ChainStorage& > modifier2(index_to_value_function, (*this));
				Query<I, void> iterator_collection = (*_index_storage).all();
				return iterator_collection.change_second(modifier).change_second(modifier2);
#else
				static Modifier<Collection<const T&>, Index, const ChainStorage& > modifier(index_to_value_function, (*this));
				Query<I, Index> iterator_collection = (*_index_storage).content();
				return iterator_collection.change_second(modifier);
#endif
			}

			
			virtual bool unset(const I& objectID) { 
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					size_t current_size = get_end_index(objectID) - (*begin_index);
					shift(objectID, current_size);
					return true;
				} else {
					return false;
				}
			}
		
			virtual bool unset(const I& objectID, Collection<const T&>& old_value_collection) { 
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					// copy first
					Collection<const T&, void, ValueVector> collection;
					ValueVector& vec = collection.container();
					size_t current_size = get_end_index(objectID) - (*begin_index);
					vec.insert(vec.begin(), _value_vector.begin() + (*begin_index), _value_vector.begin() + (*begin_index) + current_size);
					old_value_collection = collection;
					// then erase
					shift(objectID, current_size);
					return true;
				} else {
					return false;
				}
			}

			virtual bool copy(const I& sourceID, const I& targetID) { 
				if (sourceID != targetID) {
					if (const Index* source_begin_index = (*_index_storage).find(sourceID)) {
						size_t source_size = get_end_index(sourceID) - (*source_begin_index);
						Index target_begin_index = resize(targetID, source_size);
						_value_vector.insert(_value_vector.begin() + target_begin_index, _value_vector.begin() + (*source_begin_index), _value_vector.begin() + (*source_begin_index) + source_size);
						return true;
					}
				}
				return false;
			}
			
			virtual bool copy(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) {
				if (sourceID != targetID) {
					if (const Index* source_begin_index = (*_index_storage).find(sourceID)) {
						// memorize position
						Index target_begin_index = get_begin_index(targetID);
						Index target_end_index = get_end_index(targetID);
						// copy first collection
						Collection<const T&, void, ValueVector> collection;
						ValueVector& vec = collection.container();
						vec.insert(vec.begin(), _value_vector.begin() + target_begin_index, _value_vector.begin() + target_end_index);
						old_value_collection = collection;
						// then elements
						size_t source_size = get_end_index(sourceID) - (*source_begin_index);
						resize(targetID, source_size);
						_value_vector.insert(_value_vector.begin() + target_begin_index, _value_vector.begin() + (*source_begin_index), _value_vector.begin() + (*source_begin_index) + source_size);
						// then new values
						new_value_collection = index_to_value_function(targetID, *this);
						return true;
					}
				}
				return false;
			}

			virtual bool move(const I& sourceID, const I& targetID) {
				if (sourceID != targetID) {
					if (const Index* source_begin_index = (*_index_storage).find(sourceID)) {
						// memorize position
						Index source_end_index = get_end_index(sourceID);
						Index target_begin_index = get_begin_index(targetID);
						Index target_end_index = get_end_index(targetID);
						size_t source_size = source_end_index - (*source_begin_index);
						size_t target_size = target_end_index - (target_begin_index);
						// then shift to swap data
						if (targetID > sourceID) {
							rotateData(*source_begin_index, target_end_index, 0-source_size /*up*/);
							shiftIndex(sourceID+1, targetID+1, 0-source_size);
						} else {
							rotateData(target_begin_index, source_end_index, source_size /*down*/);
							shiftIndex(targetID+1, sourceID + 1, source_size);
						}
						// then fit the good size of vector
						resize(targetID, target_size);
						return true;
					}
				}
				return false;
			}
			
			virtual bool move(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) { 
				if (sourceID != targetID) {
					if (const Index* source_begin_index = (*_index_storage).find(sourceID)) {
						// memorize position
						Index source_end_index = get_end_index(sourceID);
						Index target_begin_index = get_begin_index(targetID);
						Index target_end_index = get_end_index(targetID);
						size_t source_size = source_end_index - (*source_begin_index);
						size_t target_size = target_end_index - (target_begin_index);
						// copy first collection
						Collection<const T&, void, ValueVector> collection;
						ValueVector& vec = collection.container();
						vec.insert(vec.begin(), _value_vector.begin() + target_begin_index, _value_vector.begin() + target_end_index);
						old_value_collection = collection;
						// then shift to swap data
						if (targetID > sourceID) {
							rotateData(*source_begin_index, target_end_index, 0-source_size /*up*/);
							shiftIndex(sourceID+1, targetID+1, 0-source_size);
						} else {
							rotateData(target_begin_index, source_end_index, source_size /*down*/);
							shiftIndex(targetID+1, sourceID + 1, source_size);
						}
						// then fit the good size of vector
						resize(targetID, target_size);
						// then new values
						new_value_collection = index_to_value_function(targetID, *this);
						return true;
					}
				}
				return false;
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value) {
				// memorize position
				Index begin_index = get_begin_index(objectID);
				Index end_index = get_end_index(objectID);
				// then fit the good size of vector
				size_t target_size = end_index - begin_index;
				size_t source_size = value.size();
				resize(objectID, source_size);
				bool modified = source_size != target_size;
				// then replace data
				for (Iterator<const T&> value_it = value.begin(); !value_it.eof(); ++value_it, ++begin_index) {
					const T& source_value = *value_it;
					T& target_value = _value_vector[begin_index];
					if (!modified) {
						if (target_value == source_value) {
							continue;
						}
						modified = true;
					}
					target_value = source_value;
				}
				return modified;
			}
			
			virtual bool set(const I& objectID, const Collection<const T&>& value, Collection<const T&>& old_value_collection) {
				// memorize position
				Index begin_index = get_begin_index(objectID);
				Index end_index = get_end_index(objectID);
				// copy first collection
				Collection<const T&, void, ValueVector> collection;
				ValueVector& vec = collection.container();
				vec.insert(vec.begin(), _value_vector.begin() + begin_index, _value_vector.begin() + end_index);
				old_value_collection = collection;
				// then fit the good size of vector
				size_t target_size = end_index - begin_index;
				size_t source_size = value.size();
				resize(objectID, source_size);
				bool modified = source_size != target_size;
				// then replace data
				for (Iterator<const T&> value_it = value.begin(); !value_it.eof(); ++value_it, ++begin_index) {
					const T& source_value = *value_it;
					T& target_value = _value_vector[begin_index];
					if (!modified) {
						if (target_value == source_value) {
							continue;
						}
						modified = true;
					}
					target_value = source_value;
				}
				return modified;
			}
			
			virtual bool find(const I& objectID, Collection<const T&>& value) const { return find_collection(objectID, *this, value); }
			
			virtual Collection<const T&> get(const I& objectID) { return index_to_value_function(objectID, *this); }
	

		public:
			virtual bool add(const I& objectID, const T& value) {
				Index begin_index = get_begin_index(objectID);
				Index end_index = get_end_index(objectID);
				typename ValueVector::iterator vec_it = std::find(_value_vector.begin() + begin_index, _value_vector.begin() + end_index, const_cast<T&> (value));
				if (vec_it == _value_vector.begin() + end_index) {
					return insert(objectID, value);
				} else {
					return false;
				}
			}
			
			virtual bool add(const I& objectID, const Collection<const T&>& value_collection) {
				Index begin_index = get_begin_index(objectID);
				Index end_index = get_end_index(objectID);
				ValueVector insert_vec;
				for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it) {
					T& value = const_cast<T&> (*value_it);
					Index index = begin_index;
					for (; index != end_index; ++index) {
						if (_value_vector[index] == value) {
							break;
						}
					}
					if (index != end_index) {
						insert_vec.push_back(value);
					}
				}
				
				return insert(objectID, Collection<const T&, void, ValueVector&>(insert_vec));
			}
			
			virtual bool insert(const I& objectID, const T& value) {
				// add one element to objectID is equivalent to shift the followers
				Index end_index = shift(objectID + 1, 1);
				_value_vector[end_index - 1] = value;
				return true;
			}
			
			virtual bool insert(const I& objectID, const T& value, size_t position) {
				// add one element to objectID is equivalent to shift the followers
				Index end_index = shift(objectID + 1, 1);
				Index begin_index = get_begin_index(objectID);
				// now shift data
				for (Index index = end_index; index > begin_index + position; --index) {
					_value_vector[index] = _value_vector[index-1];
				}
				_value_vector[begin_index + position] = value;
				return true;
			}
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value) { return insert(objectID, value, 0); }
			
			virtual bool insert(const I& objectID, const Collection<const T&>& value_collection, size_t position) {
				size_t source_size = value_collection.size();
				// add one element to objectID is equivalent to shift the followers
				Index end_index = shift(objectID + 1, source_size);
				Index begin_index = get_begin_index(objectID);
				
				// now shift data
				for (Index index = end_index; index > begin_index + position; --index) {
					_value_vector[index] = _value_vector[index-1];
				}
				
				// now inserting data
				for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it, ++begin_index) {
					T& value = const_cast<T&> (*value_it);
					_value_vector[begin_index + position] = value;
				}
				return true;
			}
			
			virtual bool erase(const I& objectID, size_t position) {
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					Index end_index = get_end_index(objectID);
					// now shift data
					for (Index index = (*begin_index) + position; index < end_index; ++index) {
						_value_vector[index] = _value_vector[index+1];
					}
					// remove one element to objectID is equivalent to shift the followers
					shift(objectID + 1, -1);
					return true;
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, size_t position, T& old_value) {
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					Index end_index = get_end_index(objectID);
					// copy first old data
					old_value = _value_vector[(*begin_index) + position];
					// now shift data
					for (Index index = (*begin_index) + position; index < end_index; ++index) {
						_value_vector[index] = _value_vector[index+1];
					}
					// remove one element to objectID is equivalent to shift the followers
					shift(objectID + 1, -1);
					return true;
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t count) {
				if (count != 0) {
					if (const Index* begin_index = (*_index_storage).find(objectID)) {
						Index end_index = get_end_index(objectID);
						// now shift data
						for (Index index = (*begin_index) + position + count; index < end_index; ++index) {
							_value_vector[index] = _value_vector[index+1];
						}
						// remove one element to objectID is equivalent to shift the followers
						shift(objectID + 1, 0-count);
						return true;
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, size_t position, size_t count, Collection<const T&>& old_value_collection) {
				if (count != 0) {
					if (const Index* begin_index = (*_index_storage).find(objectID)) {
						Index end_index = get_end_index(objectID);
						// copy first collection
						Collection<const T&, void, ValueVector> collection;
						ValueVector& vec = collection.container();
						vec.insert(vec.begin(), _value_vector.begin() + (*begin_index) + position, _value_vector.begin() + (*begin_index) + position + count);
						old_value_collection = collection;
						// now shift data
						for (Index index = (*begin_index) + position + count; index < end_index; ++index) {
							_value_vector[index] = _value_vector[index+1];
						}
						// remove elements to objectID is equivalent to shift the followers
						shift(objectID + 1, 0-count);
						return true;
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, const T& value) {
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					Index end_index = get_end_index(objectID);
					typename ValueVector::iterator vec_it = std::find(_value_vector.begin() + (*begin_index), _value_vector.begin() + end_index, const_cast<T&> (value));
					if (vec_it != _value_vector.begin() + end_index) {
						// add one element to objectID is equivalent to shift the followers
						Index end_index = get_end_index(objectID);
						// now shift data
						for (Index index = (vec_it - _value_vector.begin()); index < end_index; ++index) {
							_value_vector[index] = _value_vector[index+1];
						}
						// remove one element to objectID is equivalent to shift the followers
						shift(objectID + 1, -1);
						return true;
					}
				}
				return false;
			}
			
			virtual bool erase(const I& objectID, const Collection<const T&>& value_collection) {
				if ((*_index_storage).find(objectID)) {
					bool erased = false;
					for (Iterator<const T&> value_it = value_collection.begin(); !value_it.eof(); ++value_it) {
						T& value = const_cast<T&> (*value_it);
						if (erase(objectID, value)) {
							erased = true;
						}
					}
					return erased;
				}
				return false;
			}
			
			virtual bool replace(const I& objectID, const T& value, const T& new_value) {
				if (const Index* begin_index = (*_index_storage).find(objectID)) {
					Index end_index = get_end_index(objectID);
					typename ValueVector::iterator vec_it = std::find(_value_vector.begin() + (*begin_index), _value_vector.begin() + end_index, const_cast<T&> (value));
					if (vec_it == _value_vector.begin() + end_index) {
						*vec_it = new_value;
					}
				}
				return false;
			}

				
		};
		
	}
}