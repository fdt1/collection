/*
 *  variety_collection_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_const_associative_interface.h"
#include "variety_const_random_interface.h"
#include "variety_iterable_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class collection_interface : 
		public virtual const_random_interface<static_types_template>, 
		public virtual const_associative_interface<static_types_template>,
		public virtual iterable_interface<static_types_template> 
		{
		};
		
	} // namespace internal
	
} // namespace variety