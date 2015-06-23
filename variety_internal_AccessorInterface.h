/*
 *  variety_internal_AccessorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 08/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputAccessorInterface.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class AccessorInterface :
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>
		{
		public:
			static bool is_compatible(const Implementation* implementation) {
				return dynamic_cast<const InputAccessorInterface<ValueTemplate, PrevValueTemplate>*> (implementation) != NULL;
			}
		};
		
		
	} // namespace internal
	
	
} // namespace variety