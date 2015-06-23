/*
 *  variety_mutable_random_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_mutable_random_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class mutable_random_bridge : public virtual bridge, public virtual mutable_random_interface<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef mutable_random_interface<static_types_template2> interface_type;
		public:
			virtual value_type& at(int index) { return find_implementation_interface<interface_type>(true)->at(index); }
			virtual iterator_type& push_back(const value_type& value) { return find_implementation_interface<interface_type>(true)->).push_back(value); }
		};
		
	} // namespace internal
	
	
} // namespace variety