/*
 *  variety_internal_PtrDiffIteratorInterface.h
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
				
		class PtrDiffIteratorInterface :
		public virtual Implementation 
		{
		public:
			virtual int diff(const PtrDiffIteratorInterface& other) const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety