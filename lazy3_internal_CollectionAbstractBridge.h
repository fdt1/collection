/*
 *  lazy3_internal_CollectionAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_PairAbstractBridge.h"
#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_ICollection.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_ModifierAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
				
		//--------------------------------------------------------------------------------
		//! @class CollectionAbstractBridge wraps an implementation of a collection.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class CollectionAbstractBridge :
		public virtual ICollection<first_type, second_type, container_type>,
		public virtual PairAbstractBridge<first_type, second_type>,
		public virtual ContentAbstractBridge<container_type>,
		public virtual GenericAbstractBridge,
		public virtual ModifierAbstractBridge<container_type, ICollection<first_type, second_type, container_type>*>
		{
		public:
			typedef ICollection<first_type, second_type, container_type> IEmbeddedCollection;
		public:
			//! @return the current implementation nested in the Bridge
			const IEmbeddedCollection* getICollection() const { return dynamic_cast<IEmbeddedCollection*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IEmbeddedCollection* getUniqueICollection() { return dynamic_cast<IEmbeddedCollection*> (getUniqueImplementation()); } 
			//! @return the current implementation nested in the Bridge
			const ICollectionOnBase* getICollectionOnBase() const { return dynamic_cast<ICollectionOnBase*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			ICollectionOnBase* getUniqueICollectionOnBase() { return dynamic_cast<ICollectionOnBase*> (getUniqueImplementation()); } 
			
		public: // ICollection
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { if (ICollectionOnBase* Collection = this->getUniqueICollectionOnBase()) return Collection->forward(steps); else return 0; }
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { if (ICollectionOnBase* Collection = this->getUniqueICollectionOnBase()) Collection->flush(); }	
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { if (const ICollectionOnBase* Collection = this->getICollectionOnBase()) return Collection->distance(); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { if (ICollectionOnBase* Collection = this->getUniqueICollectionOnBase()) return Collection->backward(steps); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { if (ICollectionOnBase* Collection = this->getUniqueICollectionOnBase()) Collection->rewind(); }	
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { if (const ICollectionOnBase* Collection = this->getICollectionOnBase()) return Collection->remains(); else return 0; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
