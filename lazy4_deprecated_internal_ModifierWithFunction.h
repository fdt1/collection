/*
 *  lazy4_internal_ModifierWithFunction.h
 *  collection
 *
 *  Created by Francois et Fabienne on 02/10/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_Content.h"

namespace lazy4 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ApplyFunctionWithClosure {
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input, ref_content_type closure) { return function(input, closure); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename return_template, typename class_template, typename parameter_template>
		class ApplyFunctionWithClosure<output_template, input_template, closure_template, return_template (class_template::*) (parameter_template)> {
		public:
			typedef output_template (class_template::*function_template) (parameter_template);
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input, ref_content_type closure) { return (getReference(input).*function)(closure); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename return_template, typename class_template, typename parameter_template>
		class ApplyFunctionWithClosure<output_template, input_template, closure_template, return_template (class_template::*) (parameter_template) const> {
		public:
			typedef output_template (class_template::*function_template) (parameter_template) const;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input, ref_content_type closure) { return (getReference(input).*function)(closure); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ApplyFunction {
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input) { return function(input); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename return_template, typename class_template>
		class ApplyFunction<output_template, input_template, closure_template, return_template (class_template::*) ()> {
		public:
			typedef output_template (class_template::*function_template) ();
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input) { return (getReference(input).*function)(); }
		};
		
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename return_template, typename class_template>
		class ApplyFunction<output_template, input_template, closure_template, return_template (class_template::*) () const> {
		public:
			typedef output_template (class_template::*function_template) () const;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<function_template>::ref_type ref_function_type;
			
		public:
			//! @return the output of a functor
			static output_type getOutput(ref_function_type function, parameter_input_type input) { return (getReference(input).*function)(); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ModifierWithFunction : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::parameter_type parameter_function_type;
		public:
			typedef ApplyFunctionWithClosure<output_template, input_template, closure_template, function_template> ApplyFunctionWithClosure;
		public:
			Content<function_template> _functionBridge;
			Content<closure_template> _contentBridge;
			
		public:
			ModifierWithFunction(parameter_function_type function, parameter_content_type Content) : _functionBridge(function), _contentBridge(Content) {}

			ModifierWithFunction(parameter_function_type function) : _functionBridge(function) {}
			
			ModifierWithFunction() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid() && _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return ApplyFunctionWithClosure::getOutput(_functionBridge.getContent(), input, getContent()); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return ApplyFunctionWithClosure::getOutput(const_cast<ModifierWithFunction*> (this)->_functionBridge.getContent(), input, const_cast<ModifierWithFunction*> (this)->getContent()); }
			
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
		template<typename output_template, typename input_template, typename function_template>
		class ModifierWithFunction<output_template, input_template, void, function_template> : 
		public IModifier<output_template, input_template, void>
		{
		public:
			typedef void closure_template;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::parameter_type parameter_function_type;
		public:
			typedef ApplyFunction<output_template, input_template, closure_template, function_template> ApplyFunction;

		public:
			Content<function_template> _functionBridge;
			
		public:
			ModifierWithFunction(parameter_function_type function) : _functionBridge(function) {}
			
			ModifierWithFunction() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _functionBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return ApplyFunction::getOutput(_functionBridge.getContent(), input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return ApplyFunction::getOutput(const_cast<ModifierWithFunction*> (this)->_functionBridge.getContent(), input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { static Content_type content; return content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { static Content_type content; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class ModifierWithFunction<output_template, input_template, closure_template, void> : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef void function_template;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::parameter_type parameter_function_type;
			
		public:
			Content<closure_template> _contentBridge;
			Content<output_template> _outputBridge;
			
		public:
			ModifierWithFunction() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
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
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template>
		class ModifierWithFunction<output_template, input_template, void, void> : 
		public IModifier<output_template, input_template, void>
		{
		public:
			typedef void function_template;
			typedef void closure_template;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::parameter_type parameter_function_type;
			
		public:
			Content<closure_template> _contentBridge;
			Content<output_template> _outputBridge;
			
		public:
			ModifierWithFunction() {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _contentBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _contentBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
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
		
#if 0
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template, typename function_template>
		class ModifierWithFunction<output_template, input_template, closure_template, function_template*> : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template*>::type function_type;
		public:
			Content<function_template*> _functionBridge;
			
		public:
			ModifierWithFunction(function_type function) : _functionBridge(function) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _functionBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return (*_functionBridge.getConstContent())(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return (*_functionBridge.getConstContent())(input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { static Content_type content; return content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { static Content_type content; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class ModifierWithFunction<output_template, input_template, closure_template, output_template (input_template::*) ()> : 
		public IModifier<output_template, input_template, closure_template>
		{
		public:
			typedef output_template (input_template::*function_template) () ;
		public:
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<closure_template>::type Content_type;
			typedef typename internal::Type<closure_template>::ref_type ref_content_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_content_type;
			typedef typename internal::Type<function_template>::type function_type;
		public:
			Content<function_template> _functionBridge;
			
		public:
			ModifierWithFunction(function_type function) : _functionBridge(function) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* getID() const { return _functionBridge.getID(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { return _functionBridge.isValid(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithFunction* clone() const { return new ModifierWithFunction(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) {
				function_template f = _functionBridge.getConstContent();
				return getReference(input).*(_functionBridge.getConstContent())(); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return getReference(input).*(_functionBridge.getConstContent())(); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { static Content_type content; return content; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { static Content_type content; return content; }
		};
#endif
		
	} // namespace internal
	
	
} // namespace lazy4
