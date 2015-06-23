/*
 *  variety_static_types.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

namespace variety {
	
	namespace internal {
		
		template <typename value_type_template, typename key_type_template, typename iterator_type_template>
		class static_types {
		public:
			typedef key_type_template key_type;
			typedef value_type_template value_type;
			typedef iterator_type_template iterator_type;
		};
				
	} // namespace internal
	
} // namespace variety