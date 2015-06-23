/*
 *  lazy4_internal_IBackward.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IIteratorOnBase is a subdivision interface of IIterator.
		//--------------------------------------------------------------------------------
		class IBackward
		{
		public:
			//! step backward element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t backward(size_t steps) = 0;
			
			//! make the iterator restart.
			virtual void rewind() = 0;
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const = 0;
			
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual size_t remains() const = 0;
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
