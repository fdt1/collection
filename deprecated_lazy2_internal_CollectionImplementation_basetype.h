/*
 *  lazy2_internal_CollectionImplementation_basetype.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation_basetype.h"
#include "lazy2_internal_IteratorImplementation.h"
#include "lazy2_internal_InstanceCallback.h"
#include "lazy2_internal_CollectionImplementation.h"

namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class CollectionImplementation<ValueTemplate, void, ValueTemplate> :
		public CollectionInterface<ValueTemplate>,
		public Implementation
		{
			typedef void AssociateTemplate;
			typedef ValueTemplate InstanceTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return new IteratorImplementation(_instanceBridge, (InstanceTemplate*) &(_instanceBridge.getInstance())); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(_instanceBridge, (InstanceTemplate*) &(_instanceBridge.getInstance()) + 1); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const { count = 1; return index == 0 ? createBeginIterator() : createEndIterator(); }
			virtual size_t count(size_t until) const { return until != 0; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return _instanceBridge.getInstance();
				} else {
					return ValuePrimeType();
				}
			}
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance());
				} else {
					return NULL;
				}
			}
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance());
				} else {
					return NULL;
				}
			}
		};
		
	} // namespace internal
	
} // namespace lazy2