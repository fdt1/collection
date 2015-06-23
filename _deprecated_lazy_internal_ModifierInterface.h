/*
 *  lazy_internal_ModifierInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Implementation.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class ModifierInterface :
		public virtual Implementation
		{
			static bool is_compatible(const Bridge& bridge) {
				return true;
			}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy