/*
 *  lazy3_internal_EntityAdapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IEntity.h"
#include "lazy3_internal_ContentElement.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter wraps all methods of the container to match 
		//! a given interface.
		//! Only specializations on container_type sets the behavior.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class EntityAdapter 
		{
		};
				
	} // namespace internal
	
	
} // namespace lazy3
