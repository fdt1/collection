/*
 *  variety_internal_ForwardIteratorInterface.h
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
				
		class ForwardIteratorInterface :
		public virtual Implementation 
		{
		public:
			virtual void increment() = 0;
			virtual void increment(int offset) = 0;
			virtual int increment_if_possible(int offset) = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety