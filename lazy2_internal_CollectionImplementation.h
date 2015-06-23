
/*
 *  lazy2_internal_CollectionImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"

namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename InstanceTemplate>
		class CollectionImplementation:
		public virtual CollectionInterface<ValueTemplate>,
		public virtual AssociateCollectionInterface<AssociateTemplate>,
		public virtual InstanceInterface<InstanceTemplate>,
		public Implementation
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			explicit CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return createEndIterator(); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(_instanceBridge); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const  { count = 0; return createEndIterator(); }
			virtual size_t count(size_t until) const { return 0; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { count = 0; return ValuePrimeType(); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { count = 0; return NULL; }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { count = 0; return NULL; }
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { count = 0; return AssociatePrimeType(); }
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { count = 0; return NULL; }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const  { count = 0; return NULL; } 
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
			
	} // namespace internal
	
} // namespace lazy2