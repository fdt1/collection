/*
 *  lazy2_internal_Callback.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Interface.h"
#include "lazy2_internal_Implementation.h"


namespace lazy2 {
	
	namespace internal {
		
		// callback on an implementation
		class Callback :
		public virtual Interface 
		{
		public:
			virtual const Implementation* getImplementation() const = 0;
			virtual Implementation* getduplicateImplementation() const = 0;
			virtual Implementation* getUniqueImplementation() = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace lazy