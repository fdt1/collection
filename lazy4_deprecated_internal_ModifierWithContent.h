/*
 *  lazy4_internal_ModifierWithContent.h
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
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class ModifierWithContent : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
		public:
			Content<closure_template> _contentBridge;
			Content<output_template> _outputBridge;
			
		public:
			ModifierWithContent() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithContent* clone() const { return new ModifierWithContent(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return _outputBridge.getContent(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return _outputBridge.getConstContent(); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _contentBridge.getContent(); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _contentBridge.getConstContent(); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
