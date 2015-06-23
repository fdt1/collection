/*
 *  lazy4_internal_IForward.h
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
		class IForward
		{
		public:
			//! remove the front element of the flow.
			//! @return the number of elements stepped.
			//! @param steps number of steps.
			virtual size_t forward(size_t steps) = 0;
			
			//! make the flow empty.
			virtual void flush() = 0;
			
			//! @return true if the iterator is at the end.
			virtual bool isEnd() const = 0;
			
			//! count the distance between the starting point and the current iterator.
			//! @return the distance.
			virtual size_t distance() const = 0;
		};

		
		
		
	} // namespace internal
	
	
} // namespace lazy4
