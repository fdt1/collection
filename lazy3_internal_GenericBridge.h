/*
 *  lazy3_internal_GenericBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_internal_GenericAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class GenericBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		class GenericBridge :
		public Bridge,
		public virtual GenericAbstractBridge 
		{
		public:
			GenericBridge() {}
			GenericBridge(const GenericAbstractBridge& generic) : Bridge(generic) {}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
