/*
 *  lazy2_internal_AssociateCollectionInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename AssociateTemplate>
		class AssociateCollectionInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const = 0;
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) = 0;
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2