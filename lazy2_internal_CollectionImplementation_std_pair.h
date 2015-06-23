/*
 *  lazy2_internal_CollectionImplementation_std_pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_CollectionImplementation.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation_std_vector.h"
#include "lazy2_internal_InstanceCallback.h"
// for defintion of pair
#include <utility>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class CollectionImplementation<ValueTemplate, AssociateTemplate, std::pair<ValueTemplate, AssociateTemplate> > :
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public InstanceInterface<std::pair<ValueTemplate, AssociateTemplate> >,
		public Implementation
		{
			typedef std::pair<ValueTemplate, AssociateTemplate> InstanceTemplate;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			explicit CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
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
					return _instanceBridge.getInstance().first;
				} else {
					return ValuePrimeType();
				}
			}
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance().first);
				} else {
					return NULL;
				}
			}
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance().first);
				} else {
					return NULL;
				}
			}
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return _instanceBridge.getInstance().second;
				} else {
					return ValuePrimeType();
				}
			}
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance().second);
				} else {
					return NULL;
				}
			}
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance().second);
				} else {
					return NULL;
				}
			}
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceBridge.getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return _instanceBridge.getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2