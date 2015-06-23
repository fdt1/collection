/*
 *  variety_iterable_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 16/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_iterable_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class iterable_bridge : public virtual bridge, public virtual iterable_interface<static_types_template> {
		public:
			typedef typename static_types_template::iterator_type iterator_type;
			typedef iterable_interface<static_types_template2> interface_type;
		public:
			virtual iterator_type begin() const { return find_implementation_interface<interface_type>(true)->begin(); }
			virtual iterator_type end() const { return find_implementation_interface<interface_type>(true)->end(); }
			virtual size_t size() const { return find_implementation_interface<interface_type>(true)->size(); }
		};
		
	} // namespace internal
	
	
} // namespace variety