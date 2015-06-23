/*
 *  lazy4_internal_FlowWithFirstAccessor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_IFlow.h"
#include "lazy4_internal_ModifierBridge.h"
#include "lazy4_internal_FlowBridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_FunctorUtility.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template, typename old_first_template, typename closure_template>
		class FlowWithFirstAccessor :
		public IFlow<first_template, second_template, content_template>
		{
		public:
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
			typedef typename internal::FirstUtility<old_first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::FunctorUtility<first_template, old_first_template> FunctorUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			
		public:
			typedef typename internal::FlowBridge<old_first_template, second_template, content_template> FlowBridge;
			typedef typename internal::ModifierBridge<first_template, old_first_template, closure_template> ModifierBridge;
			
		public:
			FlowBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			FlowWithFirstAccessor(const FlowBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _modifier.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstAccessor* clone() const { return new FlowWithFirstAccessor(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstAccessor(_bridge.getOutput(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstAccessor(_bridge.getConstOutput(input), _modifier); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { return _bridge.forward(steps); }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _bridge.distance(); }
			
			//! @return true if the Flow is at the end.
			virtual bool isEnd() const { return _bridge.isEnd(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { return FunctorUtility::getOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FunctorUtility::getConstOutput(_modifier, FirstUtility::getConstFirst(_bridge)); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { 
				if (isValid()) { 
					while (!isEnd()) {
						if (getConstFirst() == first) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_bridge); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_bridge); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { return SecondUtility::findSecond(_bridge, second); }
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				if (isValid()) { 
					while (!isEnd()) {
						if (getConstFirst() == first && getConstSecond() == second) {
							return true;
						}
						if (forward(1) == 0) {
							break;
						}
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
