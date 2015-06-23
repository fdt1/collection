/*
 *  lazy2_internal_CollectionImplementation_void.h
 *  collection
 *
 *  Created by Francois et Fabienne on 18/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation_void.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"
#include "lazy2_internal_CollectionImplementation.h"

namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class CollectionImplementation<ValueTemplate, AssociateTemplate, void> :
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public Implementation
		{
			typedef void InstanceTemplate;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			CollectionImplementation() {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { return createBeginIterator(); }
			virtual size_t count(size_t until) const { return 0; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { count = 0; return ValuePrimeType(); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { count = 0; return NULL; }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { count = 0; return NULL; }
		public:
			// AssociateCollectionInterface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { count = 0; return AssociatePrimeType(); }
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { count = 0; return NULL; }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { count = 0; return NULL; }
		};
		
		template <typename ValueTemplate>
		class CollectionImplementation<ValueTemplate, void, void> :
		public CollectionInterface<ValueTemplate>,
		public Implementation
		{
			typedef void InstanceTemplate;
			typedef void AssociateTemplate;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			CollectionImplementation() {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { return createBeginIterator(); }
			virtual size_t count(size_t until) const { return 0; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { count = 0; return ValuePrimeType(); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { count = 0; return NULL; }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { count = 0; return NULL; }
		};
		
	} // namespace internal
	
} // namespace lazy2