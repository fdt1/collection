/*
 *  lazy4_internal_FlowWithFirstDynamicCast.h
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
#include "lazy4_internal_DynamicCast.h"

namespace lazy4 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithStaticCast is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template, 
		typename old_first_template>
		class FlowWithFirstDynamicCast : 
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
			typedef typename internal::FirstUtility<first_template> FirstUtility;
			typedef typename internal::SecondUtility<second_template> SecondUtility;
			typedef typename internal::ContentUtility<content_template> ContentUtility;
			typedef typename internal::PairUtility<first_template, second_template> PairUtility;
			typedef typename internal::FunctorUtility<internal::IFlow<old_first_template, second_template, content_template>*, input_template> FunctorUtility;
			
		public:
			typedef typename internal::FlowBridge<old_first_template, second_template, content_template> FlowBridge;
			typedef typename internal::DynamicCast<first_template, old_first_template> DynamicCast;
			
		public:
			FlowBridge _bridge;
			
		public:
			FlowWithFirstDynamicCast(const FlowBridge& bridge) : _bridge(bridge) {}
			
			FlowWithFirstDynamicCast() {}
			
		public:		
			//! @return true if a valid element
			//! @href lazy3::internal::IPairOnFirst::first
			inline bool isMatch() const { return DynamicCast::isMatch(_bridge.getConstFirst()); }
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithFirstDynamicCast* clone() const { return new FlowWithFirstDynamicCast(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithFirstDynamicCast(FunctorUtility::getOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithFirstDynamicCast(FunctorUtility::getConstOutput(_bridge, input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				size_t count = 0;
				if (isValid()) {
					while (!_bridge.isEnd() && count != steps) {
						if (isMatch()) {
							++count;
						}
						if (_bridge.forward(1) == 0) {
							break;
						}
					}
				}
				return count;
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _bridge.flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { 
				FlowWithFirstDynamicCast* newFlow = clone();
				size_t count = newFlow->backward(-1 /* maximum size */);
				delete newFlow;
				return count;
			}			
			
			//! @return true if the Flow is at the end.
			virtual bool isEnd() const {
				if (!isValid()) {
					return true;
				}
				
				// search one that matches
				while (!_bridge.isEnd() && !isMatch()) {
					if (const_cast<FlowWithFirstDynamicCast*> (this)->forward(1) == 0) {
						return true;
					}
				}
				return false;
			}
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return DynamicCast::convert(_bridge.getFirst()); 
			}
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { 
				while (!isMatch()) {
					if (const_cast<FlowWithFirstDynamicCast*>(this)->forward(1) == 0) {
						break;
					}
				}
				return DynamicCast::convert(_bridge.getConstFirst()); 
			}
			
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
			virtual second_type getSecond() { 
				while (!isMatch()) {
					if (forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getSecond(_bridge); 
			}
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { 
				while (!isMatch()) {
					if (const_cast<FlowWithFirstDynamicCast*>(this)->forward(1) == 0) {
						break;
					}
				}
				return SecondUtility::getConstSecond(_bridge); 
			}
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { 
				while (_bridge.findSecond(second)) {
					if (isMatch()) {
						return true;
					}
					if (forward(1) == 0) {
						break;
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
				if (isValid()) { 
					while (!isEnd()) {
						if (isMatch() && getConstFirst() == first && getConstSecond() == second) {
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
