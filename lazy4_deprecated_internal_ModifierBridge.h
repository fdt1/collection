/*
 *  lazy4_internal_ModifierBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 29/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_FunctorUtility.h"
#include "lazy4_internal_ContentUtility.h"
#include "lazy4_internal_Bridge.h"

namespace lazy4 {
	
	template<typename output_template, typename input_template, typename closure_template>
	class Modifier;
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class ModifierBridge : 
		public Bridge<IModifier<output_template, input_template, closure_template> >
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
			typedef typename internal::IModifier<output_template, input_template, closure_template>  IEmbeddedModifier;
			typedef typename internal::Bridge<IEmbeddedModifier> Bridge;
		public:
			typedef IEmbeddedModifier interface_type;
			
		public:
			ModifierBridge() {}
			
			ModifierBridge(const IEmbeddedModifier* implementation) : Bridge(implementation) {}
			
			ModifierBridge(const Bridge& bridge) : Bridge(bridge) {}
			
		public:
			inline ModifierBridge& operator= (const IEmbeddedModifier* implementation) { Bridge::operator= (implementation); return *this; }
			
		public:
			//! for compatibility
			static inline const ModifierBridge& cast(const lazy4::Modifier<output_template, input_template, closure_template>& modifier) { return modifier; }
			
			//! for compatibility
			static inline ModifierBridge& cast(lazy4::Modifier<output_template, input_template, closure_template>& modifier) { return modifier; }
			
			//! for compatibility
			static inline const ModifierBridge& cast(const ModifierBridge& modifier) { return modifier; }
			
			//! for compatibility
			static inline ModifierBridge& cast(ModifierBridge& modifier) { return modifier; }
			
		public: // IGeneric
			//! @return the pointer ID
			inline const void* getID() const { if (const IEmbeddedModifier* Modifier = Bridge::getImplementation()) return Modifier->getID(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool isValid() const { const IEmbeddedModifier* generic = Bridge::getImplementation(); return generic && generic->isValid(); }
			
			//! @return duplicate of the nested implementation
			inline IEmbeddedModifier* clone() const { return Bridge::getImplementation()->clone(); }
			
		public:
			//! @return the output of a functor
			inline output_type getOutput(parameter_input_type input) { return FunctorUtility::getOutput(*this, input); }
			
			//! @return the output of a functor
			inline const_output_type getConstOutput(parameter_input_type input) const { return FunctorUtility::getConstOutput(*this, input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			inline ref_content_type getContent() { return ContentUtility::getContent(*this); }
			
			//! @href lazy3::internal::IContent::getConstContent
			inline const_ref_content_type getConstContent() const { return ContentUtility::getConstContent(*this); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
