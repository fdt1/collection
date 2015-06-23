/*
 *  lazy2_internal_AccessorImplementation.h
 *  Accessor
 *
 *  Created by Francois et Fabienne on 09/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_AccessorInterface.h"
#include "lazy2_internal_InstanceCallback.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_Implementation.h"

namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename InstanceTemplate>
		class AccessorImplementation:
		public AccessorInterface<ValueTemplate, AssociateTemplate>,
		public InstanceInterface<InstanceTemplate>,
		public Implementation
		{
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef TypedBridge<InstanceCallback<InstanceTemplate> > InstanceBridge;
		public:
			InstanceBridge _instanceBridge;
		public:
			explicit AccessorImplementation(const InstanceBridge& instanceBridge) : _instanceBridge(instanceBridge) {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new AccessorImplementation(*this); }			
		public:
			// AccessorInterface
			virtual ValuePrimeType getPrimeValueFromAssociate(const AssociatePrimeType& associate) const { return _instanceBridge.getInstance()(associate); }
			// FIXME : NULL pointer!
			virtual ValuePrimeType* getAddrValueFromAssociate(const AssociatePrimeType& associate) { return NULL; }
			virtual const ValuePrimeType* getConstAddrValueFromAssociate(const AssociatePrimeType& associate) const { return NULL; }
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2