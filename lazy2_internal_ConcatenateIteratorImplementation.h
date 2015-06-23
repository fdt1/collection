/*
 *  lazy2_internal_ConcatenateIteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/04/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
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
		
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate1, typename ContainerTemplate2>
		class ConcatenateIteratorImplementation:
		public IteratorInterface<ValueTemplate>,
		public AssociateIteratorInterface<AssociateTemplate>,
		public InstanceInterface<std::pair<ContainerTemplate1, ContainerTemplate2> >,
		public Implementation
		{
			typedef PublishedBridge<CollectionInterface<ValueTemplate>, ContainerTemplate1 > CollectionBridge1;
			typedef PublishedBridge<CollectionInterface<ValueTemplate>, ContainerTemplate2 > CollectionBridge2;
			typedef std::pair<ContainerTemplate1, ContainerTemplate2> InstanceCollectionPairBridge;
			typedef PublishedBridge<IteratorInterface<ValueTemplate>, typename ContainerTemplate1::Iterator> IteratorBridge1;
			typedef PublishedBridge<IteratorInterface<ValueTemplate>, typename ContainerTemplate2::Iterator> IteratorBridge2;
			// FIXME: shall we change TypedBridge into PublishedBridge ?
			typedef TypedBridge<AccessorCallback<ValueTemplate, AssociateTemplate> > AccessorBridge;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		private:
			InstanceCollectionPairBridge _instanceCollectionPairBridge;
			IteratorBridge1 _iteratorBridge1;
			IteratorBridge2 _iteratorBridge2;
		public:
			explicit ConcatenateIteratorImplementation(const InstanceCollectionPairBridge& instanceCollectionPairBridge, const IteratorBridge1& iteratorBridge1, const IteratorBridge2& iteratorBridge2) : _instanceCollectionPairBridge(instanceCollectionPairBridge), _iteratorBridge1(iteratorBridge1), _iteratorBridge2(iteratorBridge2) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new ConcatenateIteratorImplementation(*this); }
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { size_t skipped = _iteratorBridge1.expose().incrementUntilEnd(count); return skipped == count ? count : skipped + _iteratorBridge2.expose().incrementUntilEnd(count - skipped); }
			virtual void increment(size_t count) { 
				size_t skipped = _iteratorBridge1.expose().incrementUntilEnd(count); 
				if (skipped != count) {
					_iteratorBridge2.expose().increment(count - skipped); 
				}
			}
			virtual ValuePrimeType getPrimeValue() const { return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getPrimeValue() : _iteratorBridge1.expose().getPrimeValue(); }
			virtual ValuePrimeType* getAddrValue() { return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getAddrValue() : _iteratorBridge1.expose().getAddrValue(); }
			virtual const ValuePrimeType* getConstAddrValue() const { return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getConstAddrValue() : _iteratorBridge1.expose().getConstAddrValue(); }
			virtual size_t getPosition() const { return _iteratorBridge1.expose().getPosition() + _iteratorBridge2.expose().getPosition(); }
			virtual bool isEnd() const { return _iteratorBridge2.expose().isEnd(); }
		public:
			// AssociateIterator Interface
			virtual AssociatePrimeType getPrimeAssociate() const { return return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getPrimeAssociate() : _iteratorBridge1.expose().getPrimeAssociate(); }
			virtual AssociatePrimeType* getAddrAssociate() { return return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getAddrAssociate() : _iteratorBridge1.expose().getAddrAssociate(); }
			virtual const AssociatePrimeType* getConstAddrAssociate() const { return return _iteratorBridge1.expose().isEnd() ? _iteratorBridge2.expose().getConstAddrAssociate() : _iteratorBridge1.expose().getConstAddrAssociate(); }
		public:
			// Instance Interface
			// FIXME: shall we send the iterator or the collection ????
			virtual InstanceCollectionPairBridge& getInstance() { return _instanceCollectionPairBridge; }
			virtual const InstanceCollectionPairBridge& getInstance() const { return _instanceCollectionPairBridge; }
		};
		
		
	} // namespace internal
	
} // namespace lazy2