/*
 *  lazy2_internal_IteratorImplementation_basetype.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class IteratorImplementation<ValueTemplate, void, ValueTemplate> :
		public virtual IteratorInterface<ValueTemplate>,
		public Implementation
		{
			typedef ValueTemplate InstanceTemplate;
			typedef InstanceTemplate* IteratorTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
			IteratorTemplate _instanceIterator;
		public:
			IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge), _instanceIterator(&_instanceBridge.getInstance()) {}
			IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const IteratorTemplate& instanceIterator) : _instanceBridge(instanceBridge), _instanceIterator(instanceIterator) {}
		public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new IteratorImplementation(*this); }			
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { return _instanceIterator == &_instanceBridge.getInstance() ? (++_instanceIterator, 1) : 0; }
			virtual void increment(size_t count) { _instanceIterator += count; }
			virtual ValuePrimeType getPrimeValue() const { return *_instanceIterator; }
			virtual ValuePrimeType* getAddrValue() { return _instanceIterator; }
			virtual const ValuePrimeType* getConstAddrValue() const { return _instanceIterator; }
			virtual size_t getPosition() const { return _instanceIterator - &_instanceBridge.getInstance(); }
			virtual bool isEnd() const { return _instanceIterator != &_instanceBridge.getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2