/*
 *  lazy2_internal_AccessorCallback.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Callback.h"
#include "lazy2_internal_AccessorInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class AccessorCallback :
		public virtual Callback,
		public virtual AccessorInterface<ValueTemplate, AssociateTemplate>
		{
			typedef AccessorInterface<ValueTemplate, AssociateTemplate> AccessorInterface;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			typedef AccessorInterface Interface;
		public:
			const AccessorInterface* getAccessorInterface() const { return dynamic_cast<const AccessorInterface*> (getImplementation()); }
			AccessorInterface* getAccessorInterface() { return dynamic_cast<AccessorInterface*> (getUniqueImplementation()); }
		public:
			// Accessor Interface
			virtual ValuePrimeType getPrimeValueFromAssociate(const AssociatePrimeType& associate) const { return getAccessorInterface()->getPrimeValueFromAssociate(associate); }
			virtual ValuePrimeType* getAddrValueFromAssociate(const AssociatePrimeType& associate) { return getAccessorInterface()->getAddrValueFromAssociate(associate); }
			virtual const ValuePrimeType* getConstAddrValueFromAssociate(const AssociatePrimeType& associate) const { return getAccessorInterface()->getConstAddrValueFromAssociate(associate); }
		};
		
	} // namespace internal
	
} // namespace lazy2