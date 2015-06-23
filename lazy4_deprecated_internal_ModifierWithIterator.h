/*
 *  lazy4_internal_ModifierWithIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/03/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_FunctorUtility.h"
#include "lazy4_internal_contentUtility.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_IteratorBridge.h"

namespace lazy4 {
	
	template <typename first_template, typename second_template, typename container_template>
	class Iterator;
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename first_template,     typename second_template,     typename content_template>
		class ModifierWithIterator : 
		public IModifier<lazy4::Iterator<first_template, second_template, content_template>, content_template, content_template>
		{
		public:
			typedef lazy4::Iterator<first_template, second_template, content_template> output_template;
			typedef content_template input_template;
			typedef content_template closure_template;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::FunctorUtility<output_template, input_template> FunctorUtility;
			typedef typename internal::ContentUtility<closure_template> ContentUtility;
		public:
			typedef typename internal::IteratorBridge<first_template, second_template, content_template> IteratorBridge;
			
		public:
			IteratorBridge _bridge;
			
		public:
			ModifierWithIterator(const IteratorBridge& bridge) : _bridge(bridge) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithIterator* clone() const { return new ModifierWithIterator(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(_bridge, input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(_bridge, input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_bridge); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_bridge); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
