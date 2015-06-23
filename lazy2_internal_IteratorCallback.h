/*
 *  lazy2_internal_IteratorCallback.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_Callback.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class IteratorCallback :
		public virtual Callback,
		public virtual IteratorInterface<ValueTemplate>
		{
			typedef IteratorInterface<ValueTemplate> IteratorInterface;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			typedef IteratorInterface Interface;
		public:
			const IteratorInterface* getIteratorInterface() const { return dynamic_cast<const IteratorInterface*> (getImplementation()); }
			IteratorInterface* getIteratorInterface() { return dynamic_cast<IteratorInterface*> (getUniqueImplementation()); }
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { return getIteratorInterface()->incrementUntilEnd(count); }
			virtual void increment(size_t count) { getIteratorInterface()->increment(count); }
			virtual ValuePrimeType getPrimeValue() const { return getIteratorInterface()->getPrimeValue(); }
			virtual ValuePrimeType* getAddrValue() { return getIteratorInterface()->getAddrValue(); }
			virtual const ValuePrimeType* getConstAddrValue() const { return getIteratorInterface()->getConstAddrValue(); }
			virtual size_t getPosition() const { return getIteratorInterface()->getPosition(); }
			virtual bool isEnd() const { return getIteratorInterface()->isEnd(); }
		};
		
	} // namespace internal
	
} // namespace lazy2