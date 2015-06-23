/*
 *  variety_input_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_input_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class input_bridge : public virtual internal::bridge, public virtual internal::input_interface<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef input_interface<static_types_template2> interface_type;
		public:	
			virtual const value_type& operator*() const { return find_implementation_interface<interface_type>(true)->operator*(); }
			virtual bool is_valid() const { return find_implementation_interface<interface_type>(true)->is_valid(); }
		};
		
	}
	
} // namespace variety