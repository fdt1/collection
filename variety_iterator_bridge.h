/*
 *  variety_iterator_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_forward_bridge.h"
#include "variety_input_bridge.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class iterator_bridge : 
		public virtual forward_bridge<static_types_template, static_types_template2>, 
		public virtual input_bridge<static_types_template, static_types_template2> 
		{
		};
		
	} // namespace internal
	
} // namespace variety