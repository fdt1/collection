/*
 *  variety_gnu_normal_iterator_adapter.h
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
#include "variety_output_interface.h"
#include "variety_static_types.h"
#include "variety_adapter.h"
#include "variety_iterator_implementation.h"
#include <iterator>


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename value_template, typename base_template>
		class adapter<static_types_template, __gnu_cxx::__normal_iterator<const value_template*, base_template> > : 
		public virtual input_interface<static_types_template>,
		public virtual forward_interface<static_types_template>,
		public virtual backward_interface<static_types_template>,
		public virtual iterator_implementation<static_types_template>
		{
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::value_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef __gnu_cxx::__normal_iterator<const value_template*, base_template> base_type;
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
		
		template <typename static_types_template, typename value_template, typename base_template>
		class adapter<static_types_template, __gnu_cxx::__normal_iterator<value_template*, base_template> > : 
		public virtual input_interface<static_types_template>,
		public virtual output_interface<static_types_template>,
		public virtual forward_interface<static_types_template>,
		public virtual backward_interface<static_types_template>,
		public virtual iterator_implementation<static_types_template>
		{
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::value_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef __gnu_cxx::__normal_iterator<value_template*, base_template> base_type;
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
		public:
			// output_interface
			virtual value_type& operator*() { return get_base().operator*(); }
		};
		
	} // namespace internal
	
	
} // namespace variety