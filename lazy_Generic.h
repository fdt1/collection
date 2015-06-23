/*
 *  lazy_Generic.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Bridge.h"
#include "lazy_internal_Implementation.h"


namespace lazy {
	
	class Generic :
	protected virtual internal::Bridge
	{
	protected:
		Generic() {}
	};
	
} // namespace lazy

