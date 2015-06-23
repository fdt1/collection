/*
 *  variety_input_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
	
		template <typename static_types_template>
		class input_interface : public virtual interface {
		public:
			typedef typename static_types_template::value_type value_type;
		public:	
			virtual const value_type& operator*() const = 0;
			virtual bool is_valid() const = 0;
		};
	
	} // namespace internal
	
} // namespace variety