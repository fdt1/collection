/*
 *  lazy3_internal_IteratorAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_ModifierAbstractBridge.h"
#include "lazy3_internal_PairAbstractBridge.h"
#include "lazy3_internal_IIterator.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Iterator wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IteratorAbstractBridge :
		public virtual IIterator<first_type, second_type, container_type>,
		public virtual PairAbstractBridge<first_type, second_type>,
		public virtual ContentAbstractBridge<container_type>,
		public virtual GenericAbstractBridge,
		public virtual ModifierAbstractBridge<container_type, IIterator<first_type, second_type, container_type>*>
		{
		public:
			typedef IIterator<first_type, second_type, container_type> IEmbeddedIterator;
		public:
			//! @return the current implementation nested in the Bridge
			const IEmbeddedIterator* getIIterator() const { return dynamic_cast<IEmbeddedIterator*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IEmbeddedIterator* getUniqueIIterator() { return dynamic_cast<IEmbeddedIterator*> (getUniqueImplementation()); } 
			//! @return the current implementation nested in the Bridge
			const IIteratorOnBase* getIIteratorOnBase() const { return dynamic_cast<IIteratorOnBase*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IIteratorOnBase* getUniqueIIteratorOnBase() { return dynamic_cast<IIteratorOnBase*> (getUniqueImplementation()); } 
			
		public: // IIterator
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { if (IIteratorOnBase* Iterator = this->getUniqueIIteratorOnBase()) return Iterator->forward(steps); else return 0; }
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { if (IIteratorOnBase* Iterator = this->getUniqueIIteratorOnBase()) Iterator->flush(); }	
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { if (const IIteratorOnBase* Iterator = this->getIIteratorOnBase()) return Iterator->distance(); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { if (IIteratorOnBase* Iterator = this->getUniqueIIteratorOnBase()) return Iterator->backward(steps); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { if (IIteratorOnBase* Iterator = this->getUniqueIIteratorOnBase()) Iterator->rewind(); }	
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { if (const IIteratorOnBase* Iterator = this->getIIteratorOnBase()) return Iterator->remains(); else return 0; }
		};	
		
	} // namespace internal
	
	
} // namespace lazy2
