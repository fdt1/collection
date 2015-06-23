/*
 *  lazy2_internal_IteratorImplementation_std_vector_std_pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_IteratorImplementation_std_vector.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_AssociateIteratorInterface.h"
#include "lazy2_internal_InstanceCallback.h"
#include <algorithm>
#include <vector>
#include <utility>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename AllocatorTemplate>
		class IteratorImplementation<ValueTemplate, AssociateTemplate, std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> > :
		public IteratorInterface<ValueTemplate>,
		public AssociateIteratorInterface<AssociateTemplate>,
		public InstanceInterface<std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> >,
		public Implementation
		{
			typedef std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> InstanceTemplate;
			typedef typename InstanceTemplate::iterator IteratorTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
			IteratorTemplate _instanceIterator;
		public:
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge), _instanceIterator(_instanceBridge.getInstance().begin()) {}
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const ValuePrimeType& value, const AssociatePrimeType& associate) : _instanceBridge(instanceBridge) { _instanceBridge.getInstance().push_back(std::make_pair(value, associate)); _instanceIterator = _instanceBridge.getInstance().begin(); }
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const IteratorTemplate& instanceIterator) : _instanceBridge(instanceBridge), _instanceIterator(instanceIterator) {}
		public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new IteratorImplementation(*this); }			
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { count = std::min(count, _instanceBridge.getInstance().size()); _instanceIterator += count; return count; }
			virtual void increment(size_t count) { _instanceIterator += count; }
			virtual ValuePrimeType getPrimeValue() const { return (*_instanceIterator).first; }
			virtual ValuePrimeType* getAddrValue() { return &((*_instanceIterator).first); }
			virtual const ValuePrimeType* getConstAddrValue() const { return &((*_instanceIterator).first); }
			virtual size_t getPosition() const { return _instanceBridge.getInstance().begin() - _instanceIterator; }
			virtual bool isEnd() const { return _instanceIterator == _instanceBridge.getInstance().end(); }
		public:
			// AssociateIterator Interface
			virtual AssociatePrimeType getPrimeAssociate() const { return (*_instanceIterator).second; }
			virtual AssociatePrimeType* getAddrAssociate() { return &((*_instanceIterator).second); }
			virtual const AssociatePrimeType* getConstAddrAssociate() const { return &((*_instanceIterator).second); }
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2