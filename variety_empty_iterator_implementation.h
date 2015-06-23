/*
 *  variety_empty_iterator_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_static_types.h"
#include "variety_iterator_implementation.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class empty_iterator_implementation : public virtual iterator_implementation<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::iterator_type iterator_type;
		public:
			empty_iterator_implementation() {}
			virtual ~empty_iterator_implementation() {}
			virtual empty_iterator_implementation* duplicate() const { return new empty_iterator_implementation(); }
		public: 
			// const_forward_interface methods
			virtual void increment() { assert(false); }
			virtual iterator_type& operator++() { assert(false); }
			virtual iterator_type operator++(int) { assert(false); }
		public:
			// const_input_interface methods
			virtual const value_type& operator*() const { assert(false); }
			virtual bool is_valid() const { return false; }
		};		
		
	} // namespace internal
	
	
} // namespace variety