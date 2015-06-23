/*
 *  lazy2_internal_FlattenIteratorImplementation.h
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
#include "lazy2_internal_IteratorInterface.h"
#include "lazy2_internal_IteratorCallback.h"
#include "lazy2_internal_CollectionInterface.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_Interface.h"
#include "lazy2_internal_AssociateIteratorCallback.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename CollectionTemplate, typename ContainerTemplate>
		class FlattenIteratorImplementation:
		public IteratorInterface<typename CollectionTemplate::ValueType>,
		public InstanceInterface<ContainerTemplate>,
		public Implementation
		{
			typedef typename CollectionTemplate::ValueType ValueTemplate;
			typedef typename ValueTraits<ValueTemplate>::PrimeType ValuePrimeType;
			typedef typename ValueTraits<ContainerTemplate>::PrimeType InstancePrimeType;
			typedef CollectionCallback<CollectionTemplate> InstanceCollectionTemplate;
			typedef IteratorCallback<CollectionTemplate> InstanceTemplate;
			typedef CollectionInterface<ValueTemplate> NestedCollectionInterface;
			typedef IteratorInterface<CollectionTemplate> IteratorInterface;
			typedef PublishedBridge<CollectionInterface<CollectionTemplate>, ContainerTemplate > InstanceCollectionBridge;
		private:
			// FIXME : reduce _instanceMasterIteratorBridge shall contain _instanceCollectionBridge !
			InstanceCollectionBridge _instanceCollectionBridge;
			TypedBridge<InstanceTemplate> _instanceMasterIteratorBridge;
			TypedBridge<IteratorCallback<ValueTemplate> > _instanceAuxIteratorBridge;
		public:
			explicit FlattenIteratorImplementation(const InstanceCollectionBridge& instanceCollectionBridge, 
										  const TypedBridge<InstanceTemplate>& instanceMasterIteratorBridge, 
										  const TypedBridge<IteratorCallback<ValueTemplate> >& instanceAuxIteratorBridge) 
			: _instanceCollectionBridge(instanceCollectionBridge), 
			_instanceMasterIteratorBridge(instanceMasterIteratorBridge), 
			_instanceAuxIteratorBridge(instanceAuxIteratorBridge) {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new FlattenIteratorImplementation(*this); }
		public:
			// Iterator interface
			virtual size_t incrementUntilEnd(size_t count) { 
				size_t inc = 0;
				while (count!= 0 && !_instanceMasterIteratorBridge.isEnd()) {
					size_t incAux = _instanceAuxIteratorBridge.incrementUntilEnd(count);
					if (incAux != 0) {
						count -= incAux;
						inc += incAux;
						if (count == 0) {
							break;
						}
					}
					if (!_instanceMasterIteratorBridge.incrementUntilEnd(1)) {
						break;
					}
					CollectionTemplate nestedCollection = _instanceMasterIteratorBridge.getPrimeValue();
					
					// go through Interface object the only common accessible class
					Interface* nestedCollectionVoidPt = static_cast<Interface*> (&nestedCollection);
					NestedCollectionInterface* nestedCollectionInterface = dynamic_cast<NestedCollectionInterface*> (nestedCollectionVoidPt);					
					_instanceAuxIteratorBridge = nestedCollectionInterface->createBeginIterator();
				}
				return inc;
			}
			virtual void increment(size_t count) {
				while (count!= 0) {
					size_t incAux = _instanceAuxIteratorBridge.incrementUntilEnd(count);
					if (incAux != 0) {
						count -= incAux;
						if (count == 0) {
							break;
						}
					}
					_instanceMasterIteratorBridge.incrementUntilEnd(1);
					
					CollectionTemplate nestedCollection = _instanceMasterIteratorBridge.getPrimeValue();

					// go through Interface object the only common accessible class
					Interface* nestedCollectionVoidPt = static_cast<Interface*> (&nestedCollection);
					NestedCollectionInterface* nestedCollectionInterface = dynamic_cast<NestedCollectionInterface*> (nestedCollectionVoidPt);					
					_instanceAuxIteratorBridge = nestedCollectionInterface->createBeginIterator();
				}
			}
			virtual ValuePrimeType getPrimeValue() const { return _instanceAuxIteratorBridge.getPrimeValue(); }
			virtual const ValuePrimeType* getConstAddrValue() const { return _instanceAuxIteratorBridge.getConstAddrValue(); }
			virtual ValuePrimeType* getAddrValue() { return _instanceAuxIteratorBridge.getAddrValue(); }	
			virtual size_t getPosition() const { 
				// initialization
				Implementation* iteratorImplementationBegin = _instanceCollectionBridge/*.expose()*/.createBeginIterator();
				IteratorInterface* iteratorInterfaceBegin = dynamic_cast<IteratorInterface*> (iteratorImplementationBegin);
				
				size_t refMasterPosition = _instanceMasterIteratorBridge.getPosition();
				size_t position = _instanceAuxIteratorBridge.getPosition();
				
				// count sizes of previous collections
				for (size_t masterPosition = 0; masterPosition != refMasterPosition; ++masterPosition) {
					CollectionTemplate nestedCollectionBegin = iteratorInterfaceBegin->getPrimeValue();
					// go through Interface to bypass protected inheritance!!!
					Interface& nestedInterfaceBegin = static_cast<Interface&> (nestedCollectionBegin);
					position += (dynamic_cast<NestedCollectionInterface&> (nestedInterfaceBegin)).count();
					// update for next iteration
					iteratorInterfaceBegin->increment(1);
				} 
				
				delete (iteratorImplementationBegin);
				return position;
			}			
			virtual bool isEnd() const { return _instanceMasterIteratorBridge.isEnd(); }
		public:
			// Instance Interface
			virtual InstancePrimeType& getInstance() { return _instanceCollectionBridge; }
			virtual const InstancePrimeType& getInstance() const { return _instanceCollectionBridge; }
		};
		
		
	} // namespace internal
	
} // namespace lazy2