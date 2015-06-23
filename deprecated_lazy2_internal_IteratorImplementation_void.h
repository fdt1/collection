/*
 *  lazy2_internal_IteratorImplementation_void.h
 *  collection
 *
 *  Created by Francois et Fabienne on 18/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_AssociateIteratorInterface.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IteratorImplementation<ValueTemplate, AssociateTemplate, void> :
		public virtual IteratorInterface<ValueTemplate>,
		public virtual AssociateIteratorInterface<AssociateTemplate>,
		public Implementation
		{
			typedef void InstanceTemplate;
			typedef InstanceTemplate* IteratorTemplate;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			IteratorImplementation() {}
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
		};
		
		template <typename ValueTemplate>
		class IteratorImplementation<ValueTemplate, void, void> :
		public virtual IteratorInterface<ValueTemplate>,
		public Implementation
		{
			typedef void InstanceTemplate;
			typedef void AssociateTemplate;
			typedef InstanceTemplate* IteratorTemplate;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			IteratorImplementation() {}
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
		};
		
	} // namespace internal
	
} // namespace lazy2