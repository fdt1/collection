/*
 *  variety_internal_BasicContainerInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once
#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
				
		class BasicContainerInterface :
		public virtual Implementation
		{
		public:
			// TODO: FIXME: to fill ...
			virtual size_t size() const = 0;
			/* FIXME:
			virtual Implementation* begin() const = 0;
			virtual Implementation* begin() = 0;
			virtual Implementation* end() const = 0;
			virtual Implementation* end() = 0;
			 */
		};
		
		
	} // namespace internal
	
	
} // namespace variety