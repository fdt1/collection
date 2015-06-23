/*
 *  variety_container_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_implementation.h"


namespace variety {
	
	namespace internal {
		
		class container_implementation : public virtual implementation {
		public:
			implementation* duplicate() const = 0;
		};
		
		template <typename container_template>
		class container_implementation : public virtual implementation {
		public:
			typedef container_template container_type;	
		private:
			const container_type& _container;
		public:
			virtual const container_type& get_container() const { return _container; }
		};
		
	} // namespace internal
	
} // namespace variety