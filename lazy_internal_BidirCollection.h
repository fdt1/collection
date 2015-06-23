/*
 *  lazy_internal_BidirCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 15/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_IBidirCollection.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class BidirCollection : 
		public virtual IBidirCollection<ValueTemplate, AssociateTemplate>,
		public virtual BidirIterator<ValueTemplate, AssociateTemplate>
		{
		protected:
			typedef typename ICollection<ValueTemplate, AssociateTemplate> ICollection;
			typedef typename IBidirIterator<ValueTemplate, AssociateTemplate> IBidirIterator;
		public:
			const IBidirIterator& getBridgeToBidirIterator() const { return dynamic_cast<const IBidirIterator&> (getBridgeToGeneric()); }
			IBidirIterator& getBridgeToBidirIterator() { return dynamic_cast<IBidirIterator&> (getBridgeToGeneric()); }
			const ICollection& getBridgeToCollection() const { return dynamic_cast<const ICollection&> (getBridgeToGeneric()); }
			ICollection& getBridgeToCollection() { return dynamic_cast<ICollection&> (getBridgeToGeneric()); }
		public:
			// --- interface of ICollection ---
			virtual Bridge getBegin() const { return getBridgeToCollection().getBegin(); }		
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy