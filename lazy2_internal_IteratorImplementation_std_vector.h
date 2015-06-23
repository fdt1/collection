/*
 *  lazy2_internal_IteratorImplementation_gnu_cxx_normal_iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_InstanceCallback.h"
#include <algorithm>
#include <vector>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AllocatorTemplate>
		class IteratorImplementation<ValueTemplate, void, std::vector<ValueTemplate, AllocatorTemplate> > :
		public IteratorInterface<ValueTemplate>,
		public InstanceInterface<std::vector<ValueTemplate, AllocatorTemplate> >,
		public Implementation
		{
			typedef std::vector<ValueTemplate, AllocatorTemplate> InstanceTemplate;
			typedef typename InstanceTemplate::iterator IteratorTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
			IteratorTemplate _instanceIterator;
		public:
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge), _instanceIterator(_instanceBridge.getInstance().begin()) {}
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const ValuePrimeType& value) : _instanceBridge(instanceBridge) { _instanceBridge.getInstance().push_back(value); _instanceIterator = _instanceBridge.getInstance().begin(); }
			explicit IteratorImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const IteratorTemplate& instanceIterator) : _instanceBridge(instanceBridge), _instanceIterator(instanceIterator) {}
	public:
			// Implementation Interface
			virtual Implementation* duplicate() const { return new IteratorImplementation(*this); }			
		public:
			// Iterator Interface
			virtual size_t incrementUntilEnd(size_t count) { count = std::min(count, _instanceBridge.getInstance().size()); _instanceIterator += count; return count; }
			virtual void increment(size_t count) { _instanceIterator += count; }
			virtual ValuePrimeType getPrimeValue() const { return *_instanceIterator; }
			virtual ValuePrimeType* getAddrValue() { return _instanceIterator.operator->(); }
			virtual const ValuePrimeType* getConstAddrValue() const { return _instanceIterator.operator->(); }
			virtual size_t getPosition() const { return _instanceBridge.getInstance().begin() - _instanceIterator; }
			virtual bool isEnd() const { return _instanceIterator == _instanceBridge.getInstance().end(); }
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2