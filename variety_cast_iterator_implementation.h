/*
 *  variety_cast_iterator_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 22/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_static_types.h"
#include "variety_iterator_bridge.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class cast_iterator_implementation : 
		public virtual implementation,
		public virtual iterator_bridge<static_types_template, static_types_template2> 
		{
		public:
			typedef iterator_bridge<static_types_template, static_types_template2> bridge_type;
		public:
			cast_iterator_implementation() : bridge_type() {}
			cast_iterator_implementation(implementation* impl) : bridge_type() { bridge_type::set_implementation(impl); }
			virtual ~cast_iterator_implementation() {}
			virtual cast_iterator_implementation* duplicate() const { return new cast_iterator_implementation(bridge_type::get_implementation()->duplicate()); }
		};		
		
	} // namespace internal
	
	
} // namespace variety