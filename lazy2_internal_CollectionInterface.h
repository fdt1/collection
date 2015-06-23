/*
 *  lazy2_internal_CollectionInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 08/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Interface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class CollectionInterface : 
		public virtual Interface
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			virtual Implementation* createBeginIterator() const = 0;
			virtual Implementation* createEndIterator() const = 0;
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const = 0;
			virtual size_t count(size_t until = -1) const = 0;
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const = 0;
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) = 0;
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const = 0;
		};
		
	} // namespace internal
	
} // namespace lazy2