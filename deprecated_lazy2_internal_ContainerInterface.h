/*
 *  lazy2_internal_ContainerInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 28/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ContainerTemplate>
		class ContainerInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<ContainerTemplate>::PrimeType ContainerPrimeType;
		public:
			virtual ContainerPrimeType getContainer(size_t index, size_t& count) const = 0;
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) = 0;
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2