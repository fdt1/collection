/*
 *  lazy4_internal_IAssociativeStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy4_internal_ITemplateStorage.h"



namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C, typename J, typename U, bool D>
		class IAssociativeStorage :
		public ITemplateStorage<I, T, C> 
		{
		public:
			virtual bool set_associate(const J& objectID, const U& value) = 0;
			virtual bool set_associate(const J& objectID, const U& value, const U*& new_value, U& old_value) = 0;
			virtual const U* find_associate(const J& objectID) const = 0;
			virtual const U& get_associate(const J& objectID) = 0;
			virtual Query<J, const U&> content_associate() const = 0;
			virtual bool unset_associate(const J& objectID) = 0;
			virtual bool unset_associate(const J& objectID, U& old_value) = 0;
			virtual bool exist_associate(const J& objectID) const = 0;
			virtual Query<J> all_associate() const = 0;
			virtual bool copy_associate(const J& sourceID, const J& targetID) = 0;
			virtual bool move_associate(const J& sourceID, const J& targetID) = 0;	
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C, typename J, typename U>
		class IAssociativeStorage<I, T, C, J, U, true> :
		public ITemplateStorage<I, T, C> 
		{
		public:
			virtual bool set_associate(const J& objectID, const Collection<const U&>& value_collection) = 0;
			virtual bool set_associate(const J& objectID, const Collection<const U&>& value_collection, Collection<const U&>& old_value_collection) = 0;
			virtual bool find_associate(const J& objectID, Collection<const U&>& value_collection) const = 0;
			virtual Query<J, Collection<const U&> > content_associate() const = 0;
			virtual Collection<const U&> get_associate(const J& objectID) = 0;
			virtual bool unset_associate(const J& objectID) = 0;
			virtual bool unset_associate(const J& objectID, Collection<const U&>& old_value_collection) = 0;
			virtual bool exist_associate(const J& objectID) const = 0;
			virtual Query<J> all_associate() const = 0;
			virtual bool copy_associate(const J& sourceID, const J& targetID) = 0;
			virtual bool move_associate(const J& sourceID, const J& targetID) = 0;	
		public:
			virtual bool add_associate(const J& objectID, const U& value) = 0;
			virtual bool add_associate(const J& objectID, const Collection<const U&>& value_collection) = 0;
			virtual bool insert_associate(const J& objectID, const U& value) = 0;
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& value_collection) = 0;
			virtual bool insert_associate(const J& objectID, const U& value, size_t position) = 0;
			virtual bool insert_associate(const J& objectID, const Collection<const U&>& value_collection, size_t position) = 0;
			virtual bool erase_associate(const J& objectID, const Collection<const U&>& value_collection) = 0;
			virtual bool erase_associate(const J& objectID, const U& value) = 0;
			virtual bool erase_associate(const J& objectID, size_t position) = 0;
			virtual bool erase_associate(const J& objectID, size_t position, size_t count) = 0;
			virtual bool erase_associate(const J& objectID, size_t position, U& old_value) = 0;
			virtual bool erase_associate(const J& objectID, size_t position, size_t count, Collection<const U&>& old_value_collection) = 0;
		};
		
		
	}
	

}


