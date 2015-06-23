/*
 *  lazy4_internal_ModifierWithModifier.h
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
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_FunctorUtility.h"



namespace lazy4 {
	
	namespace internal {
		

		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template, typename closure_template, typename old_output_template, typename old_closure_template>
		class ModifierWithModifier :
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::FunctorUtility<output_template, old_output_template> FunctorUtility;
			typedef typename internal::FunctorUtility<old_output_template, input_template> BridgeFunctorUtility;
			typedef typename internal::ContentUtility<closure_template> ContentUtility;
			
		public:
			typedef typename internal::ModifierBridge<old_output_template, input_template, old_closure_template> OldModifierBridge;
			typedef typename internal::ModifierBridge<output_template, old_output_template, closure_template> ModifierBridge;
			
		public:
			OldModifierBridge _bridge;
			ModifierBridge _modifier;
			
		public:
			ModifierWithModifier(const OldModifierBridge& bridge, const ModifierBridge& modifier) : _bridge(bridge), _modifier(modifier) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _modifier.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid() && _modifier.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithModifier* clone() const { return new ModifierWithModifier(*this); }
			
		public: // IModifier
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(_modifier, BridgeFunctorUtility::getConstOutput(_bridge, input)); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(_modifier, BridgeFunctorUtility::getConstOutput(_bridge, input)); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return ContentUtility::getContent(_modifier); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(_modifier); }
		};
	
	} // namespace internal
	
	
} // namespace lazy4