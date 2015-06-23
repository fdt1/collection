/*
 *  variety_const_associative_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_const_associative_interface.h"
#include "variety_bridge.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class const_associative_bridge : public virtual bridge, public virtual const_associative_interface<static_types_template> {
		public:
			typedef typename static_types_template::key_type key_type;
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::iterator_type iterator_type;
			typedef const_associative_interface<static_types_template2> interface_type;
		public:
			virtual bool exist(const key_type& key) const { return bridge::find_implementation_interface<interface_type>(true)->exist(key); }
			virtual bool exist(const key_type& key, const value_type& value) const { return bridge::find_implementation_interface<interface_type>(true)->exist(key, value); }
		};
		
	} // namespace internal
	
} // namespace variety