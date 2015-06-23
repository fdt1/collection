/*
 *  lazy2_internal_Implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		class Implementation :
		public virtual Interface 
		{
		public:
			virtual Implementation* duplicate() const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2