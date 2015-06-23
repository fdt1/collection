/*
 *  lazy4_internal_ModifierWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_FunctorUtility.h"
#include "lazy4_internal_contentUtility.h"
#include "lazy4_internal_Bridge.h"

namespace lazy4 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template,     typename input_template,     typename closure_template, typename embedded_bridge_template>
		class ModifierWithStaticCast : 
		public IModifier<output_template, input_template, closure_template>
		{
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
			typedef embedded_bridge_template ModifierBridge;
			
		public:
			ModifierBridge _bridge;
			
		public:
			ModifierWithStaticCast(const ModifierBridge& bridge) : _bridge(bridge) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _bridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _bridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithStaticCast* clone() const { return new ModifierWithStaticCast(*this); }
			
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
