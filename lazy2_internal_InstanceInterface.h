/*
 *  lazy2_internal_InstanceInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename InstanceTemplate>
		class InstanceInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
		public:
			virtual InstancePrimeType& getInstance() = 0;
			virtual const InstancePrimeType& getInstance() const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2