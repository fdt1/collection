/*
 *  lazy3_Counter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_Collection.h"

namespace lazy3 {
	
	
	//--------------------------------------------------------------------------------
	//! @class Counter is the number of elements in a collection.
	//! for user usage...
	//--------------------------------------------------------------------------------
	class Counter :
	public Collection<void, void, void>
	{
		friend class internal::GenericAbstractBridge;
	public:
	};
	
	
} // namespace lazy2
