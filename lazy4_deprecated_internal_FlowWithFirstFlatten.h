/*
 *  lazy4_internal_FlowWithFirstFlatten.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IFlow.h"
#include "lazy4_internal_FlowBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"



namespace lazy4 {
	
	template<typename first_template, typename second_template, typename content_template>
	class Flow;
		
	
	namespace internal {
				
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithFirstFlatten is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename container_first_template, typename other_second_template, typename content_template>
		class FlowWithFirstFlatten :
		public IFlow<typename internal::NestedType<container_first_template>::first_type, typename internal::NestedType<container_first_template>::second_type, content_template>
		{
		public:
			typedef typename internal::NestedType<container_first_template>::first_type first_template;
			typedef typename internal::NestedType<container_first_template>::second_type second_template;
			typedef typename internal::NestedType<container_first_template>::content_type other_content_template;
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;			
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::FlowBridge<container_first_template, other_second_template, content_template> FlowBridge;
			typedef typename internal::FlowBridge<first_template, second_template, other_content_template> NestedFlowBridge;
			typedef typename lazy4::Flow<first_template, second_template, other_content_template> NestedFlow;
			typedef typename internal::FlowBridge<NestedFlow, other_second_template, content_template> FlowFlowBridge;
			typedef typename internal::FlowBridge<NestedFlow&, other_second_template, content_template> RefFlowFlowBridge;
			typedef typename internal::FlowBridge<const NestedFlow&, other_second_template, content_template> ConstRefFlowFlowBridge;
			typedef typename internal::FlowBridge<const NestedFlow, other_second_template, content_template> ConstFlowFlowBridge;
			
			
		public:
			FlowBridge _bridge;
			NestedFlowBridge _nested;
			
		public:
			FlowWithFirstFlatten(const FlowBridge& bridge) : _bridge(bridge), _nested(getNestedFlow(_bridge)) {}
			
		public:			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(FlowFlowBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(RefFlowFlowBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(ConstFlowFlowBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
			
			//! cast for compatibility
			static inline NestedFlowBridge getNestedFlow(ConstRefFlowFlowBridge& bridge) { 
				while (!bridge.isEnd()) {
					NestedFlowBridge nested = NestedFlowBridge::cast(bridge.getFirst());
					if (!nested.isEnd()) {
						return nested;
					}
					bridge.forward(1);
				}
				return NULL;
			}
						
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _nested.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _nested.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstFlatten* clone() const { return new FlowWithFirstFlatten(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstFlatten(_bridge.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstFlatten(_bridge.getConstOutput(input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = _nested.forward(steps);	
				while (count != steps) {
					if (_bridge.forward(1) == 0) {
						return count;
					}
					_nested = getNestedFlow(_bridge);
					count += _nested.forward(steps - count);
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); _nested = getNestedFlow(_bridge); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				size_t count = _nested.distance();	
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.backward(1) != 0) {
					count += getNestedCollection(newFlowBridge).size();
				}
				return count;
			} 
			
			//! @return true if the Flow is at the end.
			virtual bool isEnd() const { return _bridge.isEnd(); } 
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return _nested.getFirst(); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return _nested.getConstFirst(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { 
				if (_nested.findFirst(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					if (_nested.findFirst(first)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool rfindFirst(const_ref_first_type first) { 
				if (_nested.rfindFirst(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					_nested.flush();
					if (_nested.rfindFirst(first)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return _nested.getSecond(); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return _nested.getConstSecond(); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { 
				if (_nested.findSecond(second)) {
					return true;
				}
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.forward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					if (_nested.findSecond(second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool rfindSecond(const_ref_second_type second) { 
				if (_nested.rfindSecond(second)) {
					return true;
				}
				FlowBridge newFlowBridge = _bridge;
				while (newFlowBridge.backward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					_nested.flush();
					if (_nested.rfindSecond(second)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				if (_nested.findFirst(first)) {
					return true;
				}
				while (_bridge.forward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					if (_nested.findPair(first, second)) {
						return true;
					}
				}
				return false;
			}
			
			//! iterate backward until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool rfindPair(const_ref_first_type first, const_ref_second_type second) { 
				if (_nested.rfindFirst(first)) {
					return true;
				}
				while (_bridge.backward(1) != 0) {
					_nested = getNestedFlow(_bridge);
					_nested.flush();
					if (_nested.rfindPair(first, second)) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
