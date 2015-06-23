/*
 *  container_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "implementation.h"

namespace variety {
		
	class implementation : public implementation {
	public:
		virtual const char* name() const = 0;
	};
		
	
} // namespace variety