/*
 *  lazy4_internal_ModifierWithBooleanAnd.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/05/14.
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
		template<typename left_output_template, typename right_output_template, typename input_template, typename left_closure_template, typename right_closure_template>
		class ModifierWithBooleanAnd : 
		public IModifier<bool, input_template,
		lazy4::Pair<typename internal::Type<left_closure_template>::ref_type, typename internal::Type<right_closure_template>::ref_type> >
		{
		public:
			typedef lazy4::Pair<typename internal::Type<left_closure_template>::ref_type, typename internal::Type<right_closure_template>::ref_type> closure_template;
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
			typedef typename internal::ModifierBridge<left_output_template, input_template, left_closure_template> LeftModifierBridge;
			typedef typename internal::ModifierBridge<right_output_template, input_template, right_closure_template> RightModifierBridge;

		public:
			LeftModifierBridge _left;
			RightModifierBridge _right;
			closure_template _closure;
			
		public:
			ModifierWithBooleanAnd(const LeftModifierBridge& left, const RightModifierBridge& right) : _left(left), _right(right), _closure(_left.getContent(), _right.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return closure_template::Bridge::cast(_closure).getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return closure_template::Bridge::cast(_closure).isValid() && _left.isValid() && _right.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithBooleanAnd* clone() const { return new ModifierWithBooleanAnd(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return _left.getOutput(input) && _right.getOutput(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return _left.getConstOutput(input) && _right.getConstOutput(input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _closure; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _closure; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
