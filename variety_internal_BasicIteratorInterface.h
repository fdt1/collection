/*
 *  variety_internal_BasicIteratorInterface.h
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
		
		
		class BasicIteratorInterface :
		public virtual Implementation
		{
		public:
			virtual bool is_equal(const BasicIteratorInterface& other) const = 0;
			virtual bool is_valid() const = 0;
			virtual void restart() = 0;
		};

		
	} // namespace internal
	
	
} // namespace variety