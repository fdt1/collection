/*
 *  lazy3_internal_IGeneric.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IImplementation.h"
#include "lazy3_internal_IBridge.h"


namespace lazy3 {
		
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IGeneric is the base interface for any lazy objects.
		//--------------------------------------------------------------------------------
		class IGeneric :
		public virtual IImplementation
		{
		public:
			//! @return true if initialized and non-empty 
			virtual bool isValid() const = 0;
			//! @return the bridge when reuse 
			//virtual IBridge reuse() = 0;
			//! @return the bridge when reuse 
			//virtual IBridge clone() = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
