/*
 *  variety_iterator_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_forward_interface.h"
#include "variety_input_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class iterator_interface : 
		public virtual forward_interface<static_types_template>, 
		public virtual input_interface<static_types_template> 
		{
		};
		
	} // namespace internal
	
} // namespace variety