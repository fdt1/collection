/*
 *  lazy3_internal_IFlow.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_IPair.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_IGeneric.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IFlowOnBase is a subdivision interface of Iflow.
		//--------------------------------------------------------------------------------
		class IFlowOnBase :
		public virtual IGeneric
		{
		public:
			//! remove the front element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t forward(size_t steps) = 0;
			//! make the flow empty.
			virtual void flush() = 0;
			//! count the distance between the starting point and the current iterator.
			//! @return the distance.
			virtual size_t distance() const = 0;
		};
		
		//--------------------------------------------------------------------------------
		//! @class IFlow is the interface for a flow.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IFlow :
		public virtual IContent<container_type>,
		public virtual IPair<first_type, second_type>,
		public virtual IFlowOnBase,
		public virtual IModifier<container_type, IFlow<first_type, second_type, container_type>*>
		{
		};
		

		
	} // namespace internal
	
	
} // namespace lazy2
