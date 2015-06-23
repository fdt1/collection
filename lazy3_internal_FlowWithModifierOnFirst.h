/*
 *  lazy3_internal_FlowWithModifierOnFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_FlowAbstractBridge.h"
#include "lazy3_internal_FlowBridge.h"
#include "lazy3_internal_ModifierBridge.h"
#include "lazy3_internal_IFlow.h"

namespace lazy3 {

	
	namespace internal {
		
	
		//--------------------------------------------------------------------------------
		//! @class FlowWithModifierOnPrime is an implementation of a flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename new_first_type, typename second_type, typename container_type>
		class FlowWithModifierOnFirst : 
		public virtual IFlow<new_first_type, second_type, container_type>,
#if !defined(VALUE_VOID)
		public FlowBridge<void, second_type, container_type>
#else
		public virtual ContentAbstractBridge<container_type>,
		public virtual GenericAbstractBridge,
		public virtual ModifierAbstractBridge<container_type, IFlow<new_first_type, second_type, container_type>*>
#endif
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef ModifierBridge<old_first_type, new_first_type> ModifierBridge;
			typedef ModifierAbstractBridge<old_first_type, new_first_type> ModifierAbstractBridge;
			typedef FlowBridge<void, second_type, container_type> FlowBridge;
#if !defined(VALUE_VOID)
			typedef IPairOnFirst<old_first_type> ICurrentPairOnFirst;
#else
			typedef IPair<old_first_type, second_type> ICurrentPairOnFirst;
#endif
			typedef FlowAbstractBridge<old_first_type, second_type, container_type> OldFlowAbstractBridge;
		public:
			ModifierBridge _modifier;
		public:
			FlowWithModifierOnFirst(const OldFlowAbstractBridge& flow, const ModifierAbstractBridge& modifier) 
			: FlowBridge(flow), _modifier(modifier) {}
		public:
			//! @return the current implementation nested in the Bridge
			const ICurrentPairOnFirst* getICurrentPairOnFirst() const { return dynamic_cast<ICurrentPairOnFirst*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			ICurrentPairOnFirst* getUniqueICurrentPairOnFirst() { return dynamic_cast<ICurrentPairOnFirst*> (this->getUniqueImplementation()); } 
			//! @href lazy3::internal::IFlowOnFirst::getFirst
			virtual new_first_type getFirst()  { return _modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
			//! @href lazy3::internal::IFlowOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return const_cast<FlowWithModifierOnFirst*> (this)->_modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
#if defined(VALUE_VOID)
		public:
			typedef IPair<old_first_type, second_type> IPair;
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
		public:
			//! @return the current implementation nested in the Bridge
			const IPair* getIPair() const { return dynamic_cast<IPair*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IPair* getUniqueIPair() { return dynamic_cast<IPair*> (this->getUniqueImplementation()); } 
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual template_second_type getSecond() { return this->getUniqueIPair()->getSecond(); }
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return this->getIPair()->getConstSecond(); }
#endif
		};


	} // namespace internal
	
	
} // namespace lazy2
