/*
 *  variety_std_vector_adapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "variety_const_random_interface.h"
#include "variety_mutable_random_interface.h"
#include "variety_static_types.h"
#include "variety_adapter.h"
#include "variety_collection_implementation.h"
#include "variety_std_reverse_iterator_adapter.h"
#include <vector>


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename value_template, typename allocator_template>
		class adapter<static_types_template, std::vector<value_template, allocator_template> > : 
		public virtual const_random_interface<static_types_template>,
		public virtual mutable_random_interface<static_types_template>,
		public virtual collection_implementation<static_types_template>
		{
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef typename std::vector<value_template, allocator_template> base_type;
			typedef typename std::vector<value_template, allocator_template>::iterator base_iterator_type;
			typedef typename std::vector<value_template, allocator_template>::iterator base_const_iterator_type;
		public:
			virtual const base_type& get_base() const = 0;
			virtual base_type& get_base() = 0;
		public:
			// const_random_interface methods
			virtual const value_type& at(int index) const { return get_base().at(index); }
		public:
			// mutable_random_interface methods
			virtual value_type& at(int index) { return get_base().at(index); }
			virtual iterator_type push_back(const value_type& value) { get_base().push_back(value); return --get_base().end(); }
		public:
			// iterable_interface
			virtual iterator_type begin() const { return get_base().begin(); }
			virtual iterator_type end() const { return get_base().end(); }
			virtual size_t size() const { return get_base().size(); }
		};
		
	} // namespace internal
	
	
} // namespace variety