/*
 *  lazy3_internal_IBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IImplementation.h"
// for shared_ptr
#include <tr1/memory> 

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IBridge is the interface of a Bridge.
		//! Bridge hides an implementation and shared allocation
		//! strategy.
		//--------------------------------------------------------------------------------
		class IBridge
		{
		public:
			virtual ~IBridge() {}
		public:
			//! @return the current implementation nested in the Bridge
			virtual IImplementation* getImplementation() const = 0;
			//! @return a duplicate of the current implementation nested in the Bridge
			virtual IImplementation* duplicateImplementation() const = 0;
			//! @return the current implementation nested in the Bridge
			//! if the implementation is shared by other bridges then it is duplicate 
			//! and set in the current Bridge
			virtual IImplementation* getUniqueImplementation() = 0;
			//! unallocate the previous implementation if any and set the new implementation
			//! @param implementation the new implementation to be set
			virtual IImplementation* setImplementation(IImplementation* implementation) = 0;
			//! @return count the number of Bridges that share the current implementation
			virtual size_t countUse() const = 0;
			//! @return true if the current implementation isn't shared by other Bridges
			virtual bool isUniqueImplementation() const = 0;
			//! @return the count ref object
			virtual const std::tr1::shared_ptr<IImplementation>& getSharedImplementation() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace lazy