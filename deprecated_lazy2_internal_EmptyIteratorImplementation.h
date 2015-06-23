/*
 *  lazy2_internal_EmptyIteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 24/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_AssociateIteratorInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class EmptyIteratorImplementation :
		public IteratorInterface<ValueTemplate>,
		public AssociateIteratorInterface<AssociateTemplate>,
		public Implementation
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			EmptyIteratorImplementation() {}
		public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new EmptyIteratorImplementation(*this); }			
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
		
	} // namespace internal
	
} // namespace lazy2