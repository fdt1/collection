/*
 *  output_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_output_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
	
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class output_bridge : public virtual bridge, public virtual output_interface<static_types_template> {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef output_interface<static_types_template2> interface_type;
		public:	
			virtual value_type& operator*() { return find_implementation_interface<interface_type>(true)->operator*(); }
		};
	
	}
	
} // namespace variety