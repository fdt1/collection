/*
 *  lazy2_internal_IteratorImplementation_std_pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"
// for defintion of pair
#include <utility>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IteratorImplementation<ValueTemplate, AssociateTemplate, std::pair<ValueTemplate,AssociateTemplate> > :
		public virtual IteratorInterface<ValueTemplate>,
		public virtual AssociateIteratorInterface<AssociateTemplate>,
		public InstanceInterface<std::pair<ValueTemplate, AssociateTemplate> >,
		public Implementation
		{
			typedef ValueTemplate InstanceTemplate;
			typedef InstanceTemplate* IteratorTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
			IteratorTemplate _instanceIterator;
		public:
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge), _instanceIterator(&_instanceBridge.getInstance()) {}
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const IteratorTemplate& instanceIterator) : _instanceBridge(instanceBridge), _instanceIterator(instanceIterator) {}
		public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new IteratorImplementation(*this); }			
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { return _instanceIterator == &_instanceBridge.getInstance() ? (++_instanceIterator, 1) : 0; }
			virtual void increment(size_t count) { _instanceIterator += count; }
			virtual ValuePrimeType getPrimeValue() const { return (*_instanceIterator).first; }
			virtual ValuePrimeType* getAddrValue() { return &((*_instanceIterator).first); }
			virtual const ValuePrimeType* getConstAddrValue() const { return &((*_instanceIterator).first); }
			virtual size_t getPosition() const { return _instanceIterator - &_instanceBridge.getInstance(); }
			virtual bool isEnd() const { return _instanceIterator != &_instanceBridge.getInstance(); }
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