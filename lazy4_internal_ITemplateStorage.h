/*
 *  lazy4_internal_ITemplateStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IStorage.h"
#include "lazy4_Collection.h"


namespace lazy4 {
	
	namespace internal2 {
		
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C>
		class ITemplateStorage :
		public IStorage<I> 
		{
		public:
			virtual bool set(const I& objectID, const T& value) = 0;
			virtual bool set(const I& objectID, const T& value, const T*& new_value, T& old_value) = 0;
			virtual const T* find(const I& objectID) const = 0;
			virtual const T& get(const I& objectID) = 0;
			virtual Query<I, const T&> content() const = 0;
			virtual bool unset(const I& objectID) = 0;
			virtual bool unset(const I& objectID, T& old_value) = 0;
			virtual bool copy(const I& sourceID, const I& targetID) = 0;
			virtual bool move(const I& sourceID, const I& targetID) = 0;
			virtual bool copy(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) = 0;
			virtual bool move(const I& sourceID, const I& targetID, const T*& new_value, T& old_value) = 0;
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T>
		class ITemplateStorage<I, T, true> :
		public IStorage<I> 
		{
		public:
			virtual bool set(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool set(const I& objectID, const Collection<const T&>& value_collection, Collection<const T&>& old_value_collection) = 0;
			virtual bool find(const I& objectID, Collection<const T&>& value_collection) const = 0;
			virtual Query<I, Collection<const T&> > content() const = 0;
			virtual Collection<const T&> get(const I& objectID) = 0;
			virtual bool unset(const I& objectID) = 0;
			virtual bool unset(const I& objectID, Collection<const T&>& old_value_collection) = 0;
			virtual bool copy(const I& sourceID, const I& targetID) = 0;
			virtual bool move(const I& sourceID, const I& targetID) = 0;
			virtual bool copy(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) = 0;
			virtual bool move(const I& sourceID, const I& targetID, Collection<const T&>& new_value_collection, Collection<const T&>& old_value_collection) = 0;
		public:
			virtual bool add(const I& objectID, const T& value) = 0;
			virtual bool add(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool insert(const I& objectID, const T& value) = 0;
			virtual bool insert(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool insert(const I& objectID, const T& value, size_t position) = 0;
			virtual bool insert(const I& objectID, const Collection<const T&>& value_collection, size_t position) = 0;
			virtual bool erase(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool erase(const I& objectID, const T& value) = 0;
			virtual bool erase(const I& objectID, size_t position) = 0;
			virtual bool erase(const I& objectID, size_t position, size_t count) = 0;
			virtual bool erase(const I& objectID, size_t position, T& old_value) = 0;
			virtual bool erase(const I& objectID, size_t position, size_t count, Collection<const T&>& old_value_collection) = 0;
			virtual bool replace(const I& objectID, const T& value, const T& new_value) = 0;
		};
	}
}