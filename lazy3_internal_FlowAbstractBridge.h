/*
 *  lazy3_internal_FlowAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_ModifierAbstractBridge.h"
#include "lazy3_internal_PairAbstractBridge.h"
#include "lazy3_internal_IFlow.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow wraps an implementation of a forward Flow.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class FlowAbstractBridge :
		public virtual IFlow<first_type, second_type, container_type>,
		public virtual PairAbstractBridge<first_type, second_type>,
		public virtual ContentAbstractBridge<container_type>,
		public virtual GenericAbstractBridge,
		public virtual ModifierAbstractBridge<container_type, IFlow<first_type, second_type, container_type>*>
		{
		public:
			typedef IFlow<first_type, second_type, container_type> IEmbeddedFlow;
		public:
			//! @return the current implementation nested in the Bridge
			const IEmbeddedFlow* getIFlow() const { return dynamic_cast<IEmbeddedFlow*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IEmbeddedFlow* getUniqueIFlow() { return dynamic_cast<IEmbeddedFlow*> (getUniqueImplementation()); } 
			//! @return the current implementation nested in the Bridge
			const IFlowOnBase* getIFlowOnBase() const { return dynamic_cast<IFlowOnBase*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IFlowOnBase* getUniqueIFlowOnBase() { return dynamic_cast<IFlowOnBase*> (getUniqueImplementation()); } 
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { if (IFlowOnBase* flow = this->getUniqueIFlowOnBase()) return flow->forward(steps); else return 0; }
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { if (IFlowOnBase* flow = this->getUniqueIFlowOnBase()) flow->flush(); }	
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { if (const IFlowOnBase* Flow = this->getIFlowOnBase()) return Flow->distance(); else return 0; }
		};	
		
	} // namespace internal
	
	
} // namespace lazy2
