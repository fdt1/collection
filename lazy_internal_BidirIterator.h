/*
 *  lazy_internal_BidirIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy_internal_IBidirIterator.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class BidirIterator : 
		public virtual IBidirIterator<ValueTemplate, AssociateTemplate>
		{
		protected:
			typedef typename IBidirIterator<ValueTemplate, AssociateTemplate> IBidirIterator;
		public:
			const IBidirIterator& getBridgeToBidirIterator() const { return dynamic_cast<const IBidirIterator&> (getBridgeToGeneric()); }
			IBidirIterator& getBridgeToBidirIterator() { return dynamic_cast<IBidirIterator&> (getBridgeToGeneric()); }
		public:
			// --- interface of IBidirIterator ---
			virtual size_t decrementAt(size_t index) { return getBridgeToBidirIterator().decrementAt(index); }
			virtual Bridge getReverse() const { return getBridgeToBidirIterator().getReverse(); }
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy