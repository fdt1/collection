/*
 *  lazy2_internal_EmptyCollectionImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 24/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */




#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_EmptyIteratorImplementation.h"
#include <vector>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class EmptyCollectionImplementation :
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public Implementation
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef EmptyIteratorImplementation<ValueTemplate, AssociateTemplate> IteratorImplementation;
		public:
			EmptyCollectionImplementation() {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new EmptyCollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const  { return new IteratorImplementation(); }
			virtual size_t count(size_t until) const { return 0; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { return ValuePrimeType(); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { return NULL; }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { return NULL; }
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { return AssociatePrimeType(); }													
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { return NULL; }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { return NULL; }
		};
		
	} // namespace internal
	
} // namespace lazy2