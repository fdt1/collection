/*
 *  lazy2_internal_AccessorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class AccessorInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			virtual ValuePrimeType getPrimeValueFromAssociate(const AssociatePrimeType& associate) const = 0;
			virtual ValuePrimeType* getAddrValueFromAssociate(const AssociatePrimeType& associate) = 0;
			virtual const ValuePrimeType* getConstAddrValueFromAssociate(const AssociatePrimeType& associate) const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2