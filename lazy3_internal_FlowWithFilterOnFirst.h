/*
 *  lazy3_internal_FlowWithFilterOnFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/09/12.
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
		//! @class FlowWithFilterOnFirstOnBase is a subdivision interface of FlowWithFilterOnFirst.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class FlowWithFilterOnFirstOnBase :
		public FlowBridge<first_type, second_type, container_type>
		{
		public:
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef FlowBridge<first_type, second_type, container_type> FlowBridge;
			typedef FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
			typedef IFlow<first_type, second_type, container_type> IFlow;
		public:
			ModifierBridge _modifier;
			size_t _distance;
		public:
			FlowWithFilterOnFirstOnBase(const FlowAbstractBridge& flow, const ModifierAbstractBridge& modifier) 
			: FlowBridge(flow), _modifier(modifier), _distance(flow.distance()) {}
		public:
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps)  { 
				/* search the next element that match the predicate */
				IFlow* flowBase = this->getUniqueIFlow(); 
				size_t count = 0;
				while (steps != count && flowBase->isValid()) {
					if (_modifier.change(flowBase->getConstFirst())) ++count; 
					flowBase->forward(1);
				} 
				_distance += count;
				return count;
			}
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { 
				/* search the first element that match the predicate */
				IFlow* flowBase = const_cast<FlowWithFilterOnFirstOnBase*> (this)->getUniqueIFlow(); 
				while (flowBase->isValid()) {
					if (const_cast<FlowWithFilterOnFirstOnBase*> (this)->_modifier.change(flowBase->getConstFirst())) return true;
					flowBase->forward(1); 
				} 
				return false;
			}
			//! @href lazy3::internal::IPairOnFirst::getFirst
			virtual first_type getFirst() { 
				/* search the next element that match the predicate */
				IFlow* flowBase = this->getUniqueIFlow(); 
				while (flowBase->isValid()) {
					if (const_cast<FlowWithFilterOnFirstOnBase*> (this)->_modifier.change(flowBase->getConstFirst())) break;
					flowBase->forward(1); 
				} 
				return flowBase->getFirst();
			}
			//! @href lazy3::internal::IPairOnFirst::getConstFirst
			virtual const_first_type getConstFirst() const { 
				/* search the next element that match the predicate */
				IFlow* flowBase = const_cast<FlowWithFilterOnFirstOnBase*> (this)->getUniqueIFlow(); 
				while (flowBase->isValid()) {
					if (const_cast<FlowWithFilterOnFirstOnBase*> (this)->_modifier.change(flowBase->getConstFirst())) break;
					flowBase->forward(1); 
				} 
				return flowBase->getConstFirst();
			}
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _distance; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithFilterOnFirst is an implementation of IFlow to filter 
		//! first typed values.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class FlowWithFilterOnFirst :
		public FlowWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type>
		{
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef FlowBridge<first_type, second_type, container_type> FlowBridge;
			typedef FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
			typedef FlowWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> FlowWithFilterOnFirstOnBase;
			typedef IFlow<first_type, second_type, container_type> IFlow;
		public:
			FlowWithFilterOnFirst(const FlowAbstractBridge& flow, const ModifierAbstractBridge& modifier) 
			: FlowWithFilterOnFirstOnBase(flow, modifier) {}
		public:
			//! @href lazy3::internal::IPairOnSecond::getSecond
			virtual second_type getSecond(size_t steps) { 
				/* search the next element that match the predicate */
				IFlow* flowBase = this->getUniqueIFlow(); 
				while (flowBase->isValid()) {
					if (const_cast<FlowWithFilterOnFirstOnBase*> (this)->_modifier.change(flowBase->getConstFirst())) break;
					flowBase->forward(1); 
				} 
				return flowBase->getSecond();
			}
			//! @href lazy3::internal::IPairOnSecond::getConstSecond
			virtual const_second_type getConstSecond() const  { 
				/* search the next element that match the predicate */
				IFlow* flowBase = this->getUniqueIFlow(); 
				while (flowBase->isValid()) {
					if (const_cast<FlowWithFilterOnFirstOnBase*> (this)->_modifier.change(flowBase->getConstFirst())) break;
					flowBase->forward(1); 
				} 
				return flowBase->getConstSecond();
			}
			
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithFilterOnFirst<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename container_type>
		class FlowWithFilterOnFirst<first_type, test_type, void, container_type> :
		public FlowWithFilterOnFirstOnBase<first_type, test_type, void, container_type>
		{
			typedef void second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef FlowBridge<first_type, second_type, container_type> FlowBridge;
			typedef FlowAbstractBridge<first_type, second_type, container_type> FlowAbstractBridge;
			typedef FlowWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> FlowWithFilterOnFirstOnBase;
		public:
			FlowWithFilterOnFirst(const FlowAbstractBridge& flow, const ModifierAbstractBridge& modifier) 
			: FlowWithFilterOnFirstOnBase(flow, modifier) {}
		};
		

		
		
	} // namespace internal
	
	
} // namespace lazy3
