/*
 *  lazy4_internal_FlowBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IFlow.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_FirstUtility.h"
#include "lazy4_internal_SecondUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_PairUtility.h"
#include "lazy4_internal_FunctorUtility.h"

namespace lazy4 {
	
	template<typename first_template, typename second_template, typename container_template>
	class Flow;
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow wraps an implementation of a forward Flow.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class FlowBridge :
		public Bridge<IFlow<first_template, second_template, content_template> >
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
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
		public:
			typedef typename internal::IFlow<first_template, second_template, content_template> IFlow;
			typedef typename internal::IModifier<IFlow*, content_template, content_template> IModifier;
			typedef typename internal::Bridge<IEmbeddedFlow> Bridge;
			
		public:
			typedef IEmbeddedFlow interface_type;
			
		public:
			FlowBridge() {}
			
			FlowBridge(const IEmbeddedFlow* implementation) : Bridge(implementation) {}
			
			FlowBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline FlowBridge& operator= (const IEmbeddedFlow* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const FlowBridge& cast(const lazy4::Flow<first_template, second_template, content_template>& Flow) { return Flow; }
			
			//! for compatibility
			static inline FlowBridge& cast(lazy4::Flow<first_template, second_template, content_template>& Flow) { return Flow; }
			
			//! for compatibility
			static inline const FlowBridge& cast(const FlowBridge& Flow) { return Flow; }
			
			//! for compatibility
			static inline FlowBridge& cast(FlowBridge& Flow) { return Flow; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedFlow* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedFlow* clone() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->clone(); else return NULL; }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			inline size_t forward(size_t steps) { if (IEmbeddedFlow* Flow = Bridge::getUniqueImplementation()) return Flow->forward(steps); else return 0; }
			
			//! @href lazy3::internal::IFlowOnBase::flush
			inline void flush() { if (IEmbeddedFlow* Flow = Bridge::getUniqueImplementation()) Flow->flush(); }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			inline size_t distance() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->distance(); else return 0; }
			
			//! @return true if the Flow is at the end.
			inline bool isEnd() const { if (const IEmbeddedFlow* Flow = Bridge::getImplementation()) return Flow->isEnd(); else return true; }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			inline first_type getFirst() { return FirstUtility::getFirst(*this); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			inline const_first_type getConstFirst() const { return FirstUtility::getConstFirst(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool findFirst(const_ref_first_type first) { return FirstUtility::findFirst(*this, first); }
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			inline second_type getSecond() { return SecondUtility::getSecond(*this); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			inline const_second_type getConstSecond() const { return SecondUtility::getConstSecond(*this); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			inline bool findSecond(const_ref_second_type second) { return SecondUtility::findSecond(*this, second); }
			
		public:
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			inline bool findPair(const_ref_first_type first, const_ref_second_type second) { return PairUtility::findPair(*this, first, second); }
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};	
		
	} // namespace internal
	
	
} // namespace lazy4
