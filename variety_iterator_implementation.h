/*
 *  variety_iterator_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_static_types.h"
#include "variety_implementation_bis.h"
#include "variety_iterator_interface.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class iterator_implementation : 
		public virtual implementation, 
		public virtual iterator_interface<static_types_template>
		{
		public:
			typedef iterator_implementation<static_types_template> implementation_type;
		public:
			virtual implementation_type* duplicate() const = 0;
		};		
			
	} // namespace internal
		
		
} // namespace variety