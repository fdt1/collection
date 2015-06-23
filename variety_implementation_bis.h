/*
 *  variety_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

//#include "variety_unknown.h"


namespace variety {
	
	namespace internal {
		
		class implementation
		{
		public:
			virtual implementation* duplicate() const = 0;
		};
	
	} // namespace internal
	
} // namespace variety