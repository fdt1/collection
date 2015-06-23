/*
 *  lazy2_internal_FlattenCollectionImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_PublishedBridge.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_FlattenIteratorImplementation.h"


namespace lazy2 {

	namespace internal {
		
		template <typename CollectionTemplate, typename ContainerTemplate>
		class FlattenCollectionImplementation:
		public CollectionInterface<typename CollectionTemplate::ValueType>,
		public InstanceInterface<ContainerTemplate>,
		public Implementation
		{
			typedef typename CollectionTemplate::ValueType ValueTemplate;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<ContainerTemplate>::PrimeType InstancePrimeType;
			typedef IteratorInterface<CollectionTemplate> IteratorInterface;
			typedef CollectionCallback<CollectionTemplate> InstanceTemplate;
			typedef CollectionInterface<ValueTemplate> NestedCollectionInterface;
			typedef PublishedBridge<NestedCollectionInterface, CollectionTemplate> NestedCollectionType;
			typedef FlattenIteratorImplementation<CollectionTemplate, ContainerTemplate> IteratorImplementation;
			typedef PublishedBridge<CollectionInterface<CollectionTemplate>, ContainerTemplate > CollectionBridge;
		private:
			CollectionBridge _instanceCollectionBridge;
			
		public:
			explicit FlattenCollectionImplementation(const CollectionBridge& instanceCollectionBridge) : _instanceCollectionBridge(instanceCollectionBridge) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new FlattenCollectionImplementation(*this); }
		public:
			// Collection interface
			virtual Implementation* createBeginIterator() const {
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin);
				NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
				Implementation* nestedIteratorImplementationBegin = nestedCollectionBegin.createBeginIterator();
				return new IteratorImplementation(_instanceCollectionBridge, iteratorImplementationBegin, nestedIteratorImplementationBegin);
			}
			virtual Implementation* createEndIterator() const
			{
				Implementation* iteratorInterfaceEnd = _instanceCollectionBridge.createEndIterator(); 
				return new IteratorImplementation(_instanceCollectionBridge, iteratorInterfaceEnd, NULL);
			}
			virtual Implementation* createIndexIterator(size_t index, size_t& count) const 
			{
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin); 
				
				
				while (!iteratorInterfaceBegin->isEnd()) {
					size_t countIter;
					NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					Implementation* iter = nestedCollectionBegin.createIndexIterator(index, countIter);
					count += countIter;
					if (countIter == index + 1) {
						delete (iteratorImplementationBegin);
						return iter;						
					}
					
					// update for next iteration
					index -= countIter;
					iteratorInterfaceBegin->increment(1);
				}
				
				delete (iteratorImplementationBegin);
				return createEndIterator();
			}
			virtual size_t count(size_t until) const { 
				if (until == 0) {
					return 0;
				}
				
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin); 
				size_t accumulator = 0;
				
				while (!iteratorInterfaceBegin->isEnd()) {
					NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					size_t size = nestedCollectionBegin.count(until);
					accumulator += size;
					if (size == until) {
						break;
					}
					
					// update for next iteration
					until -= size;
					iteratorInterfaceBegin->increment(1);
				}
				
				delete (iteratorImplementationBegin);
				return accumulator;
			}
			virtual ValueTemplate getPrimeValue(size_t index, size_t& count) const {
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin); 
				
				
				while (!iteratorInterfaceBegin->isEnd()) {
					size_t countIter;
					NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					ValueTemplate value = nestedCollectionBegin.getPrimeValue(index, countIter);
					count += countIter;
					if (countIter == index + 1) {
						delete (iteratorImplementationBegin);
						return value;						
					}
					
					// update for next iteration
					index -= countIter;
					iteratorInterfaceBegin->increment(1);
				}
				
				delete (iteratorImplementationBegin);
				return ValueTemplate();
			}
			virtual const ValueTemplate* getConstAddrValue(size_t index, size_t& count) const {
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin); 
				
				
				while (!iteratorInterfaceBegin->isEnd()) {
					size_t countIter;
					NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					const ValueTemplate* value = nestedCollectionBegin.getConstAddrValue(index, countIter);
					count += countIter;
					if (countIter == index + 1) {
						delete (iteratorImplementationBegin);
						return value;						
					}
					
					// update for next iteration
					index -= countIter;
					iteratorInterfaceBegin->increment(1);
				}
				
				delete (iteratorImplementationBegin);
				return NULL;
			}
			virtual ValueTemplate* getAddrValue(size_t index, size_t& count) {
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin); 
				
				
				while (!iteratorInterfaceBegin->isEnd()) {
					size_t countIter;
					NestedCollectionType nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					ValueTemplate* value = nestedCollectionBegin.getAddrValue(index, countIter);
					count += countIter;
					if (countIter == index + 1) {
						delete (iteratorImplementationBegin);
						return value;						
					}
					
					// update for next iteration
					index -= countIter;
					iteratorInterfaceBegin->increment(1);
				}
				
				delete (iteratorImplementationBegin);
				return NULL;
			}
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceCollectionBridge; }
			virtual const InstancePrimeType& getInstance() const { return _instanceCollectionBridge; }
		};
		
		
	} // namespace internal
	
} // namespace lazy2