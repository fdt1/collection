/*
 *  lazy3_Predicate.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_Accessor.h"

namespace lazy3 {
	
	
	//--------------------------------------------------------------------------------
	//! @class Predicate is a filter on a flow, Iterator or Collection.
	//! for user usage...
	//--------------------------------------------------------------------------------
	template <typename filter_type, typename auxilary_type = void>
	class Predicate :
	public Accessor<filter_type, bool, auxilary_type>
	{
		friend class internal::GenericAbstractBridge;
	public:
	};
	
	
} // namespace lazy2
