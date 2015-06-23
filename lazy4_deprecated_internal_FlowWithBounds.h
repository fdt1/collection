/*
 *  lazy4_internal_FlowWithBounds.h
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
	
	
	namespace internal {
				
		
		//--------------------------------------------------------------------------------
		//! @class FlowWithBounds is an implementation of a Flow to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename     first_template, typename     second_template, typename     content_template>
		class FlowWithBounds : 
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
			
		public:
			typedef typename internal::FlowBridge<first_template, second_template, content_template> FlowBridge;
			
		public:
			FlowBridge _begin;
			FlowBridge _end;
			FlowBridge _current;
			
		public:
			FlowWithBounds(const FlowBridge& begin, const FlowBridge& end) : _begin(begin), _end(end), _current(begin) {}
			
			FlowWithBounds() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _current.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _begin.isValid() && _end.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual FlowWithBounds* clone() const { return new FlowWithBounds(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new FlowWithBounds(_begin.getOutput(input), _end.getOutput(input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new FlowWithBounds(_begin.getConstOutput(input), _end.getConstOutput(input)); }
			
		public: // IFlow
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { 
				if (!isValid()) {
					return 0;
				}
				size_t count = 0;
				const void* endID = _end.getID();
				for (; count != steps && _current.getID() != endID; ++count) {
					_current.forward(1);
				}
				
				return count; 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { _current = _end; }	
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { return _current.distance() - _begin.distance(); }
			
			//! @return true if the Flow is at the end.
			virtual bool isEnd() const { return _current.getID() == _end.getID(); }
			
		public:
			//! @href lazy3::internal::IPairOnFirst::first
			virtual first_type getFirst()  { return FirstUtility::getFirst(_current); }
			
			//! @href lazy3::internal::IPairOnFirst::first
			virtual const_first_type getConstFirst() const { return FirstUtility::getConstFirst(_current); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual bool findFirst(const_ref_first_type first) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (FirstUtility::getConstFirst(_current) == first) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
		public:
			//! @href lazy3::internal::IPairOnSecond::second
			virtual second_type getSecond() { return SecondUtility::getSecond(_current); }
			
			//! @href lazy3::internal::IPairOnSecond::second
			virtual const_second_type getConstSecond() const { return SecondUtility::getConstSecond(_current); }
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual bool findSecond(const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
		public:
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { 
				if (!isValid()) {
					return false;
				}
				const void* endID = _end.getID();
				while (_current.getID() != endID) {
					if (FirstUtility::getConstFirst(_current) == first && SecondUtility::getConstSecond(_current) == second) {
						return true;
					}
					_current.forward(1);
				}
				
				return false; 
			}
			
			
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_current); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_current); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
