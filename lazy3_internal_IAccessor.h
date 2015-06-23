/*
 *  lazy3_internal_IAccessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IModifier is the interface for a flow.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type>
		class IAccessor :
		public virtual IContent<auxilary_type>,
		public virtual IModifier<old_type, new_type>
		{};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
