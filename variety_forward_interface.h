/*
 *  variety_forward_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class forward_interface : public interface {
		public:
			typedef typename static_types_template::iterator_type iterator_type;
		public:	
			// preincrement
			virtual iterator_type& operator++() = 0;
			// postincrement
			virtual iterator_type operator++(int) = 0;
			// preincrement
			virtual void increment() = 0;
		};
		
	}
		
	
} // namespace variety