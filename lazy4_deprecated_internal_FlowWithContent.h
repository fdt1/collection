/*
 *  lazy4_internal_FlowWithContent.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IFlow.h"
#include "lazy4_internal_Content.h"


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Flow to specialize
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template, typename content_template>
		class FlowWithContent : 
		public IFlow<first_template, second_template, content_template>
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::prime_type prime_first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::prime_type prime_second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::prime_type prime_content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class Flow specialization
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class FlowWithContent<first_template, second_template, void> : 
		public IFlow<first_template, second_template, void>
		{
		public:
			typedef void content_template;
			typedef typename internal::IFlow<first_template, second_template, content_template> IEmbeddedFlow;
			typedef content_template input_template;
			typedef IEmbeddedFlow* output_template;
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
			typedef typename internal::Type<first_template>::parameter_type parameter_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;
			typedef typename internal::Type<second_template>::parameter_type parameter_second_type;
			typedef typename internal::Type<content_template>::type content_type;
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			
		public:
			Content<first_template> _firstContent;
			Content<second_template> _secondContent;
			bool _isBegin;
			
		public:
			FlowWithContent() : _isBegin(false) {}
			
			FlowWithContent(parameter_first_type first, parameter_second_type second) : _firstContent(first), _secondContent(second), _isBegin(true) {}
			
			FlowWithContent(parameter_first_type first) : _firstContent(first), _isBegin(true) {}
			
			FlowWithContent(const Content<first_template>& firstContent, const Content<second_template>& secondContent) : _firstContent(firstContent), _secondContent(secondContent), _isBegin(true) {}
			
		public:
			//! @href lazy3::internal::ICommon::clone
			virtual FlowWithContent* clone() const { return new FlowWithContent(*this); }			
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return clone(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return clone(); }
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const { return isValid() ? _firstContent.getID() : NULL; }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return _firstContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return _firstContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::findFirst implementation.
			virtual bool findFirst(const_ref_first_type first) { if (isValid() && _isBegin && _firstContent.getContent() == first) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual second_type getSecond() { return _secondContent.getContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return _secondContent.getConstContent(); }
			
			//! @href lazy3::internal::IPairOnFirst::findSecond implementation.
			virtual bool findSecond(const_ref_second_type second) { if (isValid() && _isBegin && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! iterate until we reach a given pair.
			//! @return the number of elements stepped.
			//! @param first element to search
			//! @param second element to search
			virtual bool findPair(const_ref_first_type first, const_ref_second_type second) { if (isValid() && _isBegin && _firstContent.getContent() == first && _secondContent.getContent() == second) { _isBegin = true; return true; } else { _isBegin = false; return false; } }
			
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _firstContent.isValid() && _secondContent.isValid(); }
			
			//! @return true if the iterator is at the beginning.
			virtual bool isBegin() const { return isValid() && _isBegin; }
			
			//! @return true if the Flow is at the end.
			virtual bool isEnd() const { return !isValid() || !_isBegin; }
			
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (steps && isValid() && _isBegin) { 
					_isBegin = false; 
					return 1; 
				} else { 
					return 0; 
				} 
			}
			
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { forward(1); }
			
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { return isValid() && this->isBegin() == false; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() { static content_type content; return content; }
			
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { static content_type content; return content; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
