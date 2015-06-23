/*
 *  variety_internal_BackwardIteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
				
		class BackwardIteratorInterface :
		public virtual Implementation 
		{
		public:
			virtual void decrement() = 0;
			virtual void decrement(int offset) = 0;
			virtual int decrement_if_possible(int offset) = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety