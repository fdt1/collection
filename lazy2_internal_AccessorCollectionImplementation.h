/*
 *  lazy2_internal_AccessorCollectionImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_PublishedBridge.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_AccessorCallback.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_AccessorIteratorImplementation.h"


namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Collection;
	
	namespace internal {
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate>
		class AccessorCollectionImplementation:
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public InstanceInterface<ContainerTemplate>,
		public Implementation
		{
			typedef PublishedBridge<CollectionInterface<AssociateTemplate>, ContainerTemplate > CollectionBridge;
			typedef TypedBridge<AccessorCallback<ValueTemplate, AssociateTemplate> > AccessorBridge;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef typename ValueTraits<ContainerTemplate>::PrimeType InstancePrimeType;
			typedef AccessorIteratorImplementation<ValueTemplate, AssociateTemplate, typename ContainerTemplate::Iterator> AccessorIteratorImplementation;
		private:
			CollectionBridge _collectionBridge;
			AccessorBridge _accessorBridge;
		public:
			explicit AccessorCollectionImplementation(const CollectionBridge& collectionBridge, const AccessorBridge& accessorBridge) : _collectionBridge(collectionBridge), _accessorBridge(accessorBridge) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new AccessorCollectionImplementation(*this); }
		public:
			// Collection Interface
			virtual Implementation* createBeginIterator() const { return new AccessorIteratorImplementation(_collectionBridge.createBeginIterator(), _accessorBridge); }
			virtual Implementation* createEndIterator() const { return new AccessorIteratorImplementation(_collectionBridge.expose().createEndIterator(), _accessorBridge); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { return new AccessorIteratorImplementation(_collectionBridge.expose().createIndexIterator(index, count), _accessorBridge); }
			virtual size_t count(size_t until) const { return _collectionBridge.count(until); }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { return _accessorBridge.getPrimeValueFromAssociate(_collectionBridge.expose().getPrimeValue(index , count)); }
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { return _accessorBridge.getAddrValueFromAssociate(*_collectionBridge.expose().getAddrValue(index , count)); }
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { return _accessorBridge.getConstAddrValueFromAssociate(*_collectionBridge.expose().getConstAddrValue(index , count)); }
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { return _collectionBridge.expose().getPrimeValue(index, count); }
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { return _collectionBridge.expose().getAddrValue(index, count); }
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { return _collectionBridge.expose().getConstAddrValue(index, count); }
		public:
			// Instance Interface
			// FIXME : interface to enable
			virtual InstancePrimeType& getInstance() { return _collectionBridge; }
			virtual const InstancePrimeType& getInstance() const { return _collectionBridge; }
		};
		
						
	} // namespace internal
	
} // namespace lazy2