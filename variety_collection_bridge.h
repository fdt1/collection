/*
 *  variety_collection_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_const_associative_bridge.h"
#include "variety_const_random_bridge.h"
#include "variety_iterable_bridge.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class collection_bridge : 
		public virtual const_random_bridge<static_types_template, static_types_template2>, 
		public virtual const_associative_bridge<static_types_template, static_types_template2>, 
		public virtual iterable_bridge<static_types_template, static_types_template2> 
		{
		public:
			typedef iterable_bridge<static_types_template, static_types_template2> bridge_type;
		public:
			/*
			implementation* get_implementation() const { return bridge_type::get_implementation(); }
			void set_implementation(implementation* impl) { bridge_type::set_implementation(impl); }
			
			template <typename unknown_template>
			unknown_template* find_implementation_interface(bool abort = false) const { 
				unknown_template* (*f) (bool);
				f = &bridge_type::find_implementation_interface<unknown_template>;
				return bridge_type::find_implementation_interface<unknown_template>(abort); 
			}
			 */
		};
		
	} // namespace internal
	
} // namespace variety