/*
 *  variety_mutable_associative_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_mutable_associative_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class mutable_associative_bridge : public virtual bridge, public virtual mutable_associative_interface<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef mutable_associative_interface<static_types_template2> interface_type;
		public:
			virtual iterator_type insert(const key_type& key, const value_type& value) { return find_implementation_interface<interface_type>(true)->insert(key, value); }
			virtual iterator_type insert(const key_type& key) { return find_implementation_interface<interface_type>(true)->insert(key); }
		};
		
	} // namespace internal
	
	
} // namespace variety