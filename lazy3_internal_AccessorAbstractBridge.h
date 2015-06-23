/*
 *  lazy3_internal_AccessorAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_ModifierAbstractBridge.h"
#include "lazy3_internal_IAccessor.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IAccessor is the interface for a Accessor.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type>
		class AccessorAbstractBridge :
		public virtual IAccessor<old_type, new_type, auxilary_type>,
		public virtual ModifierAbstractBridge<old_type, new_type>,
		public virtual ContentAbstractBridge<auxilary_type>
		{
			
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
