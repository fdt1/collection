/*
 *  variety_const_random_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_const_random_interface.h"
#include "variety_bridge.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class const_random_bridge : public virtual bridge, public virtual const_random_interface<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef const_random_interface<static_types_template2> interface_type;
		public:
			virtual const value_type& at(int index) const { return find_implementation_interface<interface_type>(true)->at(index); }
		};
		
	} // namespace internal
	
} // namespace variety