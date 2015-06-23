/*
 *  lazy4_internal_ModifierWithFunctionClosure.h
 *  collection
 *
 *  Created by Francois et Fabienne on 29/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
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
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ModifierWithFunctionClosure : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::type function_type;
		public:
			Content<function_template> _functionBridge;
			Content<closure_template> _contentBridge;
			
		public:
			ModifierWithFunctionClosure(function_type function, parameter_content_type Content) : _functionBridge(function), _contentBridge(Content) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid() && _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunctionClosure* clone() const { return new ModifierWithFunctionClosure(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return (*_functionBridge.getConstContent())(input, getConstContent()); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return (_functionBridge.getConstContent())(input, getConstContent()); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _contentBridge.getContent(); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _contentBridge.getConstContent(); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ModifierWithFunctionClosure<output_template, input_template, closure_template, function_template*> : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template*>::type function_type;
		public:
			Content<function_template*> _functionBridge;
			Content<closure_template> _contentBridge;
			
		public:
			ModifierWithFunctionClosure(function_type function, parameter_content_type Content) : _functionBridge(function), _contentBridge(Content) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid() && _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunctionClosure* clone() const { return new ModifierWithFunctionClosure(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return (*_functionBridge.getConstContent())(input, getConstContent()); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return (*_functionBridge.getConstContent())(input, getConstContent()); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _contentBridge.getContent(); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _contentBridge.getConstContent(); }
		};
		
#if 0
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class ModifierWithFunctionClosure<output_template, input_template, closure_template, <input_template>::*> : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::prime_type foo;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template*>::type function_type;
		public:
			Content<function_template*> _functionBridge;
			Content<closure_template> _contentBridge;
			
		public:
			ModifierWithFunctionClosure(function_type function, parameter_content_type Content) : _functionBridge(function), _contentBridge(Content) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid() && _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunctionClosure* clone() const { return new ModifierWithFunctionClosure(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return (*_functionBridge.getConstContent())(input, getConstContent()); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return (*_functionBridge.getConstContent())(input, getConstContent()); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _contentBridge.getContent(); }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _contentBridge.getConstContent(); }
		};
#endif
		
	} // namespace internal
	
	
} // namespace lazy4
