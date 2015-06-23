/*
 *  lazy2_internal_CollectionBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Callback.h"
#include "lazy2_internal_CollectionInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class CollectionCallback :
		public virtual Callback,
		public virtual CollectionInterface<ValueTemplate>
		{
			typedef CollectionInterface<ValueTemplate> CollectionInterface;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			typedef CollectionInterface Interface;
		public:
			const CollectionInterface* getCollectionInterface() const { return dynamic_cast<const CollectionInterface*> (getImplementation()); }
			// don't duplicate the implementation in Collection
			CollectionInterface* getCollectionInterface() { return const_cast<CollectionInterface*> (getCollectionInterface()); }
		public:
			// Iterator Interface
			virtual Implementation* createBeginIterator() const { return getCollectionInterface()->createBeginIterator(); }
			virtual Implementation* createEndIterator() const { return getCollectionInterface()->createEndIterator(); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { return getCollectionInterface()->createIndexIterator(index, count); }
			virtual size_t count(size_t until) const { return getCollectionInterface()->count(until); }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { return getCollectionInterface()->getPrimeValue(index, count); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { return getCollectionInterface()->getAddrValue(index, count); }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { return getCollectionInterface()->getConstAddrValue(index, count); }
		};
		
	} // namespace internal
	
} // namespace lazy2