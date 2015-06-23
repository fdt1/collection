/*
 *  lazy4_internal_ModifierWithBooleanNot.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/05/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_Content.h"

namespace lazy4 {
	
	template <typename first_template, typename second_template>
	class Pair;
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class ModifierWithBooleanAnd is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename any_output_template, typename input_template, typename closure_template>
		class ModifierWithBooleanNot : 
		public IModifier<bool, input_template, closure_template>
		{
		public:
			typedef bool output_template;
			
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			
		public:
			typedef typename internal::ModifierBridge<any_output_template, input_template, closure_template> ModifierBridge;
			
		public:
			ModifierBridge _modifier;
			
		public:
			ModifierWithBooleanNot(const ModifierBridge& modifier) : _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _modifier.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _modifier.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithBooleanNot* clone() const { return new ModifierWithBooleanNot(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return !_modifier.getOutput(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return !_modifier.getConstOutput(input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _modifier.getContent(); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _modifier.getConstContent(); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
