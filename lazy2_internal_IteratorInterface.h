/*
 *  lazy2_internal_IteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"
#include "lazy2_internal_Implementation.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class IteratorInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			virtual size_t incrementUntilEnd(size_t count) = 0;
			virtual void increment(size_t count) = 0;
			virtual ValuePrimeType getPrimeValue() const = 0;
			virtual ValuePrimeType* getAddrValue() = 0;
			virtual const ValuePrimeType* getConstAddrValue() const = 0;
			// FIXME : to move to bidir iterator
			virtual size_t getPosition() const = 0;
			virtual bool isEnd() const = 0;
			/*
			 virtual const Implementation* getCollectionImplementation() const;
			virtual size_t countToEnd() const = 0;
			 virutal int distanceTo(const ValuePrimeType* addr) const;
			 */
		};
		
		// FIXME: shall we implement the specialization of void ?
		
	} // namespace internal
	
} // namespace lazy2