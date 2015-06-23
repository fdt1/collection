/*
 *  lazy4_internal_IInheritanceStorage.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_ITemplateStorage.h"



namespace lazy4 {
	
	namespace internal2 {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C, bool D = false>
		class IInheritanceStorage :
		public ITemplateStorage<I, T, C> 
		{
		public:
			virtual bool unset_model(const I& instance) = 0; 			
			virtual bool unset_occurrence(const I& model) = 0; 			
			virtual const I& get_model(const I& instance) = 0; 
			virtual Collection<I> get_occurrence(const I& model) = 0; 
			virtual const I* find_model(const I& occurrrence) const = 0; 
			virtual bool find_occurrence(const I& model, Collection<const T&>& occurrence_collection) const = 0; 
			virtual bool set_model(const I& instance, const I& model) = 0; 			
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template <typename I, typename T, bool C>
		class IInheritanceStorage<I, T, C, false>  :
		public ITemplateStorage<I, T, C> 
		{
		public:
			virtual bool unset_model(const I& instance) = 0; 			
			virtual bool unset_occurrence(const I& model) = 0; 			
			virtual Collection<I> get_model(const I& instance) = 0; 
			virtual Collection<I> get_occurrence(const I& model) = 0; 
			virtual bool find_model(const I& instance, Collection<const T&>& model_collection) const = 0; 
			virtual bool find_occurrence(const I& model, Collection<const T&>& occurrence_collection) const = 0; 
		public:
			virtual bool add_model(const I& objectID, const T& value) = 0;
			virtual bool add_model(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool insert_model(const I& objectID, const T& value) = 0;
			virtual bool insert_model(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool insert_model(const I& objectID, const T& value, size_t position) = 0;
			virtual bool insert_model(const I& objectID, const Collection<const T&>& value_collection, size_t position) = 0;
			virtual bool erase_model(const I& objectID, const Collection<const T&>& value_collection) = 0;
			virtual bool erase_model(const I& objectID, const T& value) = 0;
			virtual bool erase_model(const I& objectID, size_t position) = 0;
			virtual bool erase_model(const I& objectID, size_t position, size_t count) = 0;
			virtual bool erase_model(const I& objectID, size_t position, T& old_value) = 0;
			virtual bool erase_model(const I& objectID, size_t position, size_t count, Collection<const T&>& old_value_collection) = 0;
			virtual bool replace_model(const I& objectID, const T& value, const T& new_value) = 0;
		};
		
	}
	
	
}

