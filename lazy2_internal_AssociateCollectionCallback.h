/*
 *  lazy2_internal_AssociateAssociateCollectionCallback.h
 *  AssociateCollection
 *
 *  Created by Francois et Fabienne on 10/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_Callback.h"
#include "lazy2_internal_AssociateCollectionInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename AssociateTemplate>
		class AssociateCollectionCallback :
		public virtual Callback,
		public virtual AssociateCollectionInterface<AssociateTemplate>
		{
			typedef AssociateCollectionInterface<AssociateTemplate> AssociateCollectionInterface;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			typedef AssociateCollectionInterface Interface;
		public:
			const AssociateCollectionInterface* getAssociateCollectionInterface() const { return dynamic_cast<const AssociateCollectionInterface*> (getImplementation()); }
			// don't duplicate the implementation in Collection
			AssociateCollectionInterface* getAssociateCollectionInterface() { return const_cast<AssociateCollectionInterface*> (getAssociateCollectionInterface()); }
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { return getAssociateCollectionInterface()->getPrimeAssociate(index, count); }
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { return getAssociateCollectionInterface()->getAddrAssociate(index, count); }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { return getAssociateCollectionInterface()->getConstAddrAssociate(index, count); }
		};
		
	} // namespace internal
	
} // namespace lazy2