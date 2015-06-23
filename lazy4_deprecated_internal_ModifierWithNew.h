/*
 *  lazy4_internal_ModifierWithNew.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_Bridge.h"
#include "lazy4_internal_ModifierBridge.h"
#include "lazy4_internal_contentUtility.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template, typename closure_template, typename new_implementation_template, typename modifier_output_template, typename modifier_input_template>
		class ModifierWithNew :
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<input_template>::prime_type prime_type_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::ContentUtility<closure_template> ContentUtility;
			
		public:
			typedef typename internal::ModifierBridge<modifier_output_template, modifier_input_template, closure_template> ModifierBridge;
			
		public:
			ModifierBridge _modifier;
			
		public:
			ModifierWithNew(const ModifierBridge& modifier) : _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _modifier.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _modifier.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithNew* clone() const { return new ModifierWithNew(*this); }
			
		public: // IModifier
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return new new_implementation_template(prime_type_input_type::Bridge::cast(input), _modifier); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return new new_implementation_template(prime_type_input_type::Bridge::cast(input), _modifier); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_modifier); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_modifier); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4