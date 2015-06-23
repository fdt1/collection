/*
 *  lazy_internal_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy_internal_ICollection.h"
#include "lazy_internal_Bridge.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class ICollection :
		public virtual ICollection<ValueTemplate, AssociateTemplate>
		{
		protected:
			typedef typename ICollection<ValueTemplate, AssociateTemplate> ICollection;
		public:
			const ICollection& getBridgeToCollection() const { return dynamic_cast<const ICollection&> (getBridgeToGeneric()); }
			ICollection& getBridgeToCollection() { return dynamic_cast<ICollection&> (getBridgeToGeneric()); }
		public:
			// --- interface of ICollection ---
			virtual Bridge getBegin() const { return getBridgeToCollection().getBegin(); }		
		};
		
		
	} // namespace internal
	
	
} // namespace lazy