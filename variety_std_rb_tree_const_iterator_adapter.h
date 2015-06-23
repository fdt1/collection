/*
 *  variety_std_rb_tree_const_iterator_adapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "variety_forward_interface.h"
#include "variety_backward_interface.h"
#include "variety_input_interface.h"
#include "variety_static_types.h"
#include "variety_adapter.h"
#include "variety_iterator_implementation.h"
#include <iterator>


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename pair_value_template>
		class adapter<static_types_template, std::_Rb_tree_const_iterator<pair_value_template> > : 
		public virtual input_interface<static_types_template>,
		public virtual forward_interface<static_types_template>,
		public virtual backward_interface<static_types_template>,
		public virtual iterator_implementation<static_types_template>
		{
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef std::_Rb_tree_const_iterator<pair_value_template> base_type;
		public:
			virtual const base_type& get_base() const = 0;
			virtual base_type& get_base() = 0;
		public:
			// forward_interface
			virtual iterator_type& operator++() { assert(false); }
			virtual iterator_type operator++(int) { return get_base().operator++(); }
			virtual void increment() { get_base().operator++(); }
		public:
			// backward_interface
			virtual iterator_type operator--() { return get_base().operator--(); }
			virtual void decrement() { get_base().operator--(); }
		public:	
			// input_interface
			virtual const value_type& operator*() const { return get_base().operator*(); }
			virtual bool is_valid() const { return true; /*FIXME*/ }
		};
		
	} // namespace internal
	
	
} // namespace variety