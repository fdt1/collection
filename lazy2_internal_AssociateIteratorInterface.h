/*
 *  lazy2_internal_AssociateIteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"
#include "lazy2_internal_Bridge.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename AssociateTemplate>
		class AssociateIteratorInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			virtual AssociatePrimeType getPrimeAssociate() const = 0;
			virtual AssociatePrimeType* getAddrAssociate() = 0;
			virtual const AssociatePrimeType* getConstAddrAssociate() const = 0;
		};
		
		template <>
		class AssociateIteratorInterface<void> : 
		public virtual Interface
		{
		public:
		};
		
	} // namespace internal
	
} // namespace lazy2