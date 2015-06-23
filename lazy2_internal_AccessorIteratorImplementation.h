/*
 *  lazy2_internal_AccessorIteratorImplementation.h
 *  Iterator
 *
 *  Created by Francois et Fabienne on 09/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_PublishedBridge.h"
#include "lazy2_internal_AccessorCallback.h"
#include "lazy2_internal_IteratorCallback.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_AssociateIteratorInterface.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate>
		class AccessorIteratorImplementation:
		public IteratorInterface<ValueTemplate>,
		public AssociateIteratorInterface<AssociateTemplate>,
		public InstanceInterface<ContainerTemplate>,
		public Implementation
		{
			typedef PublishedBridge<IteratorInterface<AssociateTemplate>, ContainerTemplate> IteratorBridge;
			// FIXME: shall we change TypedBridge into PublishedBridge ?
			typedef TypedBridge<AccessorCallback<ValueTemplate, AssociateTemplate> > AccessorBridge;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef typename ValueTraits<ContainerTemplate>::PrimeType InstancePrimeType;
		private:
			IteratorBridge _iteratorBridge;
			AccessorBridge _accessorBridge;
		public:
			explicit AccessorIteratorImplementation(const IteratorBridge& IteratorBridge, const AccessorBridge& accessorBridge) : _iteratorBridge(IteratorBridge), _accessorBridge(accessorBridge) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new AccessorIteratorImplementation(*this); }
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { return _iteratorBridge.expose().incrementUntilEnd(count); }
			virtual void increment(size_t count) { _iteratorBridge.expose().increment(count); }
			virtual ValuePrimeType getPrimeValue() const { return _accessorBridge.getPrimeValueFromAssociate(_iteratorBridge.expose().getPrimeValue()); }
			virtual ValuePrimeType* getAddrValue() { return _accessorBridge.getAddrValueFromAssociate(*_iteratorBridge.expose().getAddrValue()); }
			virtual const ValuePrimeType* getConstAddrValue() const { return _accessorBridge.getConstAddrValueFromAssociate(*_iteratorBridge.expose().getConstAddrValue()); }
			virtual size_t getPosition() const { return _iteratorBridge.expose().getPosition(); }
			virtual bool isEnd() const { return _iteratorBridge.expose().isEnd(); }
		public:
			// AssociateIterator Interface
			virtual AssociatePrimeType getPrimeAssociate() const { return _iteratorBridge.expose().getPrimeValue(); }
			virtual AssociatePrimeType* getAddrAssociate() { return _iteratorBridge.expose().getAddrValue(); }
			virtual const AssociatePrimeType* getConstAddrAssociate() const { return _iteratorBridge.expose().getConstAddrValue(); }
		public:
			// Instance Interface
			// FIXME: shall we send the iterator or the collection ????
			virtual InstancePrimeType& getInstance() { return _iteratorBridge; }
			virtual const InstancePrimeType& getInstance() const { return _iteratorBridge; }
		};
		
		
	} // namespace internal
	
} // namespace lazy2