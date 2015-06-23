/*
 *  lazy3_internal_IAdapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IContent.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IAdapter is the interface of an adapter. An adapter wraps all methods 
		//! of the container to match a given interface.
		//--------------------------------------------------------------------------------
		template<typename container_type, typename interface_type>
		class IAdapter : 
		public virtual interface_type,
		public virtual IContent<container_type>
		{
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
