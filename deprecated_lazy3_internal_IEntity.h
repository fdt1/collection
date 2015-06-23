/*
 *  lazy3_internal_IEntity.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_IPair.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_IFlow.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IEntityOnBase is a subdivision interface of IEntity.
		//--------------------------------------------------------------------------------
		class IEntityOnBase :
		public virtual IIteratorOnBase
		{
		public:
		};
		
		//--------------------------------------------------------------------------------
		//! @class IEntity is the interface for an Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IEntity :
		public virtual IContent<container_type>,
		public virtual IPair<first_type, second_type>,
		public virtual IEntityOnBase,
		public virtual IModifier<container_type, IEntity<first_type, second_type, container_type>*>
		{
			//! @return the relatives of the current element.
			virtual IEntity* relatives() const = 0;
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
