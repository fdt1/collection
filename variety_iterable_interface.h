/*
 *  variety_iterable_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 16/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template>
		class iterable_interface : public virtual interface {
		public:
			typedef typename static_types_template::iterator_type iterator_type;
		public:	
			virtual iterator_type begin() const = 0;
			virtual iterator_type end() const = 0;
			virtual size_t size() const = 0;
		};
		
	} // namespace internal
	
} // namespace variety