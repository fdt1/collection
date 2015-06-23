/*
 *  variety_const_reference_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *base
 */



#pragma once

#include "variety_static_types.h"
#include "variety_adapter.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename base_template>
		class const_reference_implementation : 
		public virtual adapter<static_types_template, base_template>
		{
		public:
			typedef base_template base_type;	
		private:
			const base_type& _base;
		public:
			const_reference_implementation(const base_type& base) : _base(base) {}
			virtual ~const_reference_implementation() {}
			virtual const base_type& get_base() const { return _base; }
			virtual base_type& get_base() { assert(false); }
			virtual const_reference_implementation* duplicate() const { return new const_reference_implementation(_base); }
		};		
		
	} // namespace internal
	
	
} // namespace variety