/*
 *  lazy2_internal_ConcatenateCollectionImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/04/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_PublishedBridge.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_ConcatenateIteratorImplementation.h"


namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Collection;
	
	namespace internal {
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate1, typename ContainerTemplate2>
		class ConcatenateCollectionImplementation:
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public InstanceInterface<std::pair<ContainerTemplate1, ContainerTemplate2> >,
		public Implementation
		{
			typedef PublishedBridge<CollectionInterface<ValueTemplate>, ContainerTemplate1 > CollectionBridge1;
			typedef PublishedBridge<CollectionInterface<ValueTemplate>, ContainerTemplate2 > CollectionBridge2;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef std::pair<ContainerTemplate1, ContainerTemplate2> InstancePrimeType;
			typedef ConcatenateIteratorImplementation<ValueTemplate, AssociateTemplate, typename ContainerTemplate1::Iterator, typename ContainerTemplate2::Iterator> ConcatenateIteratorImplementation;
		private:
			InstancePrimeType _collectionBridgePair;
		public:
			explicit ConcatenateCollectionImplementation(const ContainerTemplate1& collectionBridge1, const CollectionBridge2& collectionBridge2) : _collectionBridgePair(std::make_pair(collectionBridge1, collectionBridge2)) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new ConcatenateCollectionImplementation(*this); }
		public:
			// Collection Interface
			virtual Implementation* createBeginIterator() const { return new ConcatenateIteratorImplementation(_collectionBridgePair.first.createBeginIterator(), _collectionBridgePair.second.createBeginIterator()); }
			virtual Implementation* createEndIterator() const { return new ConcatenateIteratorImplementation(_collectionBridgePair.first.expose().createEndIterator(), _collectionBridgePair.second.expose().createEndIterator(), _accessorBridge); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { ContainerTemplate1::Iterator it = _collectionBridgePair.expose().createIndexIterator(index, count); return new ConcatenateIteratorImplementation(it, _collectionBridgePair.expose().createIndexIterator(index - count, count)); }
			virtual size_t count(size_t until) const { size_t firstCount = _collectionBridgePair.first.count(until); return _collectionBridgePair.second.count(until - firstCount) + firstCount;}
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { ValuePrimeType value = _collectionBridgePair.first.getPrimeValue(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getPrimeValue(index - count, count); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { ValuePrimeType* value = _collectionBridgePair.first.getAddrValue(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getAddrValue(index - count, count); }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { const ValuePrimeType* value = _collectionBridgePair.first.getConstAddrValue(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getConstAddrValue(index - count, count); }
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { AssociatePrimeType value = _collectionBridgePair.first.getPrimeAssociate(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getPrimeAssociate(index - count, count); }
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { AssociatePrimeType* value = _collectionBridgePair.first.getAddrAssociate(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getAddrAssociate(index - count, count); }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { AssociatePrimeType* value = _collectionBridgePair.first.getConstAddrAssociate(index, count); return count == index + 1 ? value : _collectionBridgePair.second.getConstAddrAssociate(index - count, count); }
		public:
			// Instance Interface
			// FIXME : interface to enable
			virtual InstancePrimeType& getInstance() { return _collectionBridgePair; }
			virtual const InstancePrimeType& getInstance() const { return _collectionBridgePair; }
		};
		
		
	} // namespace internal
	
} // namespace lazy2