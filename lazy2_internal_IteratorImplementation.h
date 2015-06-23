/*
 *  lazy2_internal_IteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_InstanceCallback.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_AssociateIteratorInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename InstanceTemplate>
		class IteratorImplementation:
		public IteratorInterface<ValueTemplate>,
		public AssociateIteratorInterface<AssociateTemplate>,
		public InstanceInterface<InstanceTemplate>,
		public Implementation
		{
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
		public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new IteratorImplementation(*this); }			
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { return 0; }
			virtual void increment(size_t count) {}
			virtual ValuePrimeType getPrimeValue() const { return ValuePrimeType(); }
			virtual ValuePrimeType* getAddrValue() { return NULL; }
			virtual const ValuePrimeType* getConstAddrValue() const { return NULL; }
			virtual size_t getPosition() const { return 0; }
			virtual bool isEnd() const { return true; }
		public:
			// AssociateIterator Interface
			virtual AssociatePrimeType getPrimeAssociate() const { return AssociatePrimeType(); }
			virtual AssociatePrimeType* getAddrAssociate() { return NULL; }
			virtual const AssociatePrimeType* getConstAddrAssociate() const { return NULL; }
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
		
		
	} // namespace internal
	
} // namespace lazy2