/*
 *  lazy3_internal_IIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/13.
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
		//! @class IIteratorOnBase is a subdivision interface of IIterator.
		//--------------------------------------------------------------------------------
		class IIteratorOnBase :
		public virtual IFlowOnBase
		{
		public:
			//! step backward element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t backward(size_t steps) = 0;
			//! make the iterator restart.
			virtual void rewind() = 0;
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual size_t remains() const = 0;
		};
		
		//--------------------------------------------------------------------------------
		//! @class IIterator is the interface for an iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IIterator :
		public virtual IContent<container_type>,
		public virtual IPair<first_type, second_type>,
		public virtual IIteratorOnBase,
		public virtual IModifier<container_type, IIterator<first_type, second_type, container_type>*>
		{
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
