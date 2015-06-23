/*
 *  lazy2_internal_CollectionImplementation_std_vector_std_pair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_AssociateCollectionInterface.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_CollectionImplementation.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorImplementation_std_vector_std_pair.h"
#include "lazy2_internal_CollectionImplementation_std_vector.h"
#include "lazy2_internal_InstanceCallback.h"
#include <vector>
#include <utility>


namespace lazy2 {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, typename AllocatorTemplate>
		class CollectionImplementation<ValueTemplate, AssociateTemplate, std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> > :
		public CollectionInterface<ValueTemplate>,
		public AssociateCollectionInterface<AssociateTemplate>,
		public InstanceInterface<std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> >,
		public Implementation
		{
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
			typedef std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate> InstanceTemplate;
			typedef typename std::vector<std::pair<ValueTemplate, AssociateTemplate>, AllocatorTemplate>::iterator IteratorTemplate;
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstRefType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef IteratorImplementation<ValueTemplate, AssociateTemplate, InstanceTemplate> IteratorImplementation;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			explicit CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
			explicit CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge, const ValuePrimeType& value, const AssociatePrimeType& associate) : _instanceBridge(instanceBridge) { _instanceBridge.getInstance().push_back(std::make_pair(value, associate));}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// CollectionInterface
			virtual Implementation* createBeginIterator() const { return new IteratorImplementation(_instanceBridge, ((InstanceTemplate&) _instanceBridge.getInstance()).begin()); }
			virtual Implementation* createEndIterator() const { return new IteratorImplementation(_instanceBridge, ((InstanceTemplate&) _instanceBridge.getInstance()).end()); }
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const  { size_t size = _instanceBridge.getInstance().size(); return index < size ? new IteratorImplementation(_instanceBridge, ((InstanceTemplate&) _instanceBridge.getInstance()).begin() + index) : createEndIterator(); }
			virtual size_t count(size_t until) const { size_t size = _instanceBridge.getInstance().size(); return size < until ? size : until; }
			virtual ValuePrimeType getPrimeValue(size_t index, size_t& count) const { 
				size_t size = _instanceBridge.getInstance().size();
				if (index < size) {
					count = index + 1;
					return _instanceBridge.getInstance()[index].first;
				} else {
					count = size;
					return ValuePrimeType();
				}
			}
			virtual ValuePrimeType* getAddrValue(size_t index, size_t& count) { 
				size_t size = _instanceBridge.getInstance().size();
				if (index < size) {
					count = index + 1;
					return &(_instanceBridge.getInstance()[index].first);
				} else {
					count = size;
					return NULL;
				}
			}
			virtual const ValuePrimeType* getConstAddrValue(size_t index, size_t& count) const { 
				size_t size = _instanceBridge.getInstance().size();
				if (index < size) {
					count = index + 1;
					return &(_instanceBridge.getInstance()[index].first);
				} else {
					count = size;
					return NULL;
				}
			}
		public:
			// AssociateCollection Interface
			virtual AssociatePrimeType getPrimeAssociate(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return _instanceBridge.getInstance()[index].second;
				} else {
					return ValuePrimeType();
				}
			}
			virtual AssociatePrimeType* getAddrAssociate(size_t index, size_t& count) { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance()[index].second);
				} else {
					return NULL;
				}
			}
			virtual const AssociatePrimeType* getConstAddrAssociate(size_t index, size_t& count) const { 
				count = 1;
				if (index == 0) {
					return &(_instanceBridge.getInstance()[index].second);
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