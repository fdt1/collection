/*
 *  variety_std_reverse_iterator_adapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 28/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "variety_static_types.h"
#include "variety_adapter.h"
#include <iterator>


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename iterator_template>
		class adapter<static_types_template, std::reverse_iterator<iterator_template> > : 
		public virtual adapter<static_types_template, iterator_template>
		{
		};
		
	} // namespace internal
	
	
} // namespace variety