/*
 *  variety_adapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_interface.h"
#include "variety_static_types.h"


namespace variety {
	
	namespace internal {
		
		template <typename static_types_template, typename base_template>
		class adapter : public virtual interface {
		private:
			adapter();
			adapter(const adapter&);
			adapter& operator=(const adapter&);
		};
		
	} // namespace internal
	
	
} // namespace variety