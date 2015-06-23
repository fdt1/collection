/*
 *  lazy2_internal_AssociateIteratorCallback.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_AssociateIteratorInterface.h"
#include "lazy2_internal_Callback.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename AssociateTemplate>
		class AssociateIteratorCallback :
		public virtual Callback,
		public virtual AssociateIteratorInterface<AssociateTemplate>
		{
			typedef AssociateIteratorInterface<AssociateTemplate> AssociateIteratorInterface;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			typedef AssociateIteratorInterface Interface;
		public:
			const AssociateIteratorInterface* getAssociateIteratorInterface() const { return dynamic_cast<const AssociateIteratorInterface*> (getImplementation()); }
			AssociateIteratorInterface* getAssociateIteratorInterface() { return dynamic_cast<AssociateIteratorInterface*> (getUniqueImplementation()); }
		public:
			// AssociateIterator Interface
			virtual AssociatePrimeType getPrimeAssociate() const { return getAssociateIteratorInterface()->getPrimeAssociate(); }
			virtual AssociatePrimeType* getAddrAssociate() { return getAssociateIteratorInterface()->getAddrAssociate(); }
			virtual const AssociatePrimeType* getConstAddrAssociate() const { return getAssociateIteratorInterface()->getConstAddrAssociate(); }
		};
		
		template <>
		class AssociateIteratorCallback<void> :
		public virtual Callback,
		public virtual AssociateIteratorInterface<void>
		{
			typedef void AssociateTemplate;
			typedef AssociateIteratorInterface<AssociateTemplate> AssociateIteratorInterface;
		public:
#ifdef DEBUG
			AssociateIteratorCallback() { checkImplementation(); }
#endif
		public:
			const AssociateIteratorInterface* getAssociateIteratorInterface() const { return dynamic_cast<const AssociateIteratorInterface*> (getImplementation()); }
			AssociateIteratorInterface* getAssociateIteratorInterface() { return dynamic_cast<AssociateIteratorInterface*> (getUniqueImplementation()); }
			void checkImplementation() const { assert(getAssociateIteratorInterface()); }
		public:
			// AssociateIterator Interface
			/* empty */
		};
		
	} // namespace internal
	
} // namespace lazy2