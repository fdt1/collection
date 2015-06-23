/*
 *  variety_mutable_random_interface.h
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
		class mutable_random_interface : public virtual interface {
		public:
			typedef typename static_types_template::value_type value_type;
			typedef typename static_types_template::iterator_type iterator_type;
		public:
			virtual value_type& at(int index) = 0;
			virtual iterator_type push_back(const value_type& value) = 0;
		};
		
	} // namespace internal
	
	
} // namespace variety