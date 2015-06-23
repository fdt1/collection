/*
 *  variety_cast_collection_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 22/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_static_types.h"
#include "variety_collection_bridge.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class cast_collection_implementation : 
		public virtual implementation,
		public virtual collection_bridge<static_types_template, static_types_template2> 
		{
		public:
			typedef collection_bridge<static_types_template, static_types_template2> bridge_type;
		public:
			cast_collection_implementation() : bridge_type() {}
			cast_collection_implementation(implementation* impl) : bridge_type(impl) {}
			virtual ~cast_collection_implementation() {}
			virtual cast_collection_implementation* duplicate() const { return new cast_collection_implementation(bridge_type::get_implementation()->duplicate()); }
		};		
		
	} // namespace internal
	
	
} // namespace variety