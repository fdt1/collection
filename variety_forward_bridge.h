/*
 *  variety_forward_bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_forward_interface.h"
#include "variety_bridge.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename static_types_template2 = static_types_template>
		class forward_bridge : public virtual bridge, public virtual forward_interface<static_types_template> {
		public:
			typedef typename static_types_template::iterator_type iterator_type;
			typedef forward_interface<static_types_template2> interface_type;
		public:	
			virtual iterator_type& operator++() { increment(); return dynamic_cast<iterator_type&> (*this); }
			virtual iterator_type operator++(int) { iterator_type it = dynamic_cast<iterator_type&> (*this); increment(); return it; }
		protected:
			virtual void increment() { find_implementation_interface<interface_type>(true)->increment(); }
		};
	
	} // namespace internal
	
} // namespace variety