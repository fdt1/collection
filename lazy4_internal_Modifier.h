/*
 *  lazy4_internal_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Content.h"

namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template, bool is_bridge_template = true>
		struct FunctorUtility
		{
		public:
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename input_template>
		struct FunctorUtility<void, input_template, true>
		{
			typedef void output_template;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility<output_template&, input_template, true>
		{
			typedef typename internal::Type<output_template&>::type output_type;
			typedef typename internal::Type<output_template&>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getUniqueImplementation()->getOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility<const output_template&, input_template, true>
		{
			typedef typename internal::Type<const output_template&>::type output_type;
			typedef typename internal::Type<const output_template&>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		

		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility<typename output_template, typename input_template, false>
		{
		public:
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (new bridge_template((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (new bridge_template((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename input_template>
		struct FunctorUtility<void, input_template, false>
		{
			typedef void output_template;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct FunctorUtility<void, void, false>
		{
			typedef void output_template;
			typedef void input_template;
			typedef internal::Type<output_template>::type output_type;
			typedef internal::Type<output_template>::const_type const_output_type;
			typedef internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template>
		struct FunctorUtility<output_template, void, false>
		{
			typedef void input_template;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (new bridge_template()); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (new bridge_template()); }
		};
		

		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class IModifier :
		public IContent<closure_template>
		{
		public:
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return duplicate of the current implementation
			virtual IModifier* clone() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
		};
		
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
			inline const void* where() const { if (const IEmbeddedModifier* Modifier = Bridge::getImplementation()) return Modifier->where(); else return NULL; }
			
			//! @href lazy3::internal::IGeneric::isValid
			inline bool good() const { const IEmbeddedModifier* generic = Bridge::getImplementation(); return generic && generic->good(); }
			
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
			virtual const void* where() const { return _modifier.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good() && _modifier.good(); }
			
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
			virtual const void* where() const { return _modifier.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _modifier.good(); }
			
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
			virtual const void* where() const { return _bridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _bridge.good(); }
			
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
			virtual const void* where() const { return _contentBridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _contentBridge.good() && _functionBridge.good(); }
			
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
			virtual const void* where() const { return _functionBridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _functionBridge.good(); }
			
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
			virtual const void* where() const { return _contentBridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _contentBridge.good(); }
			
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
			virtual const void* where() const { return _contentBridge.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _contentBridge.good(); }
			
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
			virtual const void* where() const { return closure_template::Bridge::cast(_closure).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return closure_template::Bridge::cast(_closure).good() && _left.good() && _right.good(); }
			
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
			virtual const void* where() const { return _modifier.where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return _modifier.good(); }
			
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
		
		//--------------------------------------------------------------------------------
		//! @class ModifierWithBooleanOr is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename left_output_template, typename right_output_template, typename input_template, typename left_closure_template, typename right_closure_template>
		class ModifierWithBooleanOr : 
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
			ModifierWithBooleanOr(const LeftModifierBridge& left, const RightModifierBridge& right) : _left(left), _right(right), _closure(_left.getContent(), _right.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return closure_template::Bridge::cast(_closure).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return closure_template::Bridge::cast(_closure).good() && _left.good() && _right.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithBooleanOr* clone() const { return new ModifierWithBooleanOr(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return _left.getOutput(input) || _right.getOutput(input); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return _left.getConstOutput(input) || _right.getConstOutput(input); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _closure; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _closure; }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class ModifierWithBooleanXor is an implementation of a Iterator to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename left_output_template, typename right_output_template, typename input_template, typename left_closure_template, typename right_closure_template>
		class ModifierWithBooleanXor : 
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
			ModifierWithBooleanXor(const LeftModifierBridge& left, const RightModifierBridge& right) : _left(left), _right(right), _closure(_left.getContent(), _right.getContent()) {}
			
		public: // IGeneric
			//! @return the pointer ID
			virtual const void* where() const { return closure_template::Bridge::cast(_closure).where(); }
			
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool good() const { return closure_template::Bridge::cast(_closure).good() && _left.good() && _right.good(); }
			
			//! @return duplicate of the nested implementation
			virtual ModifierWithBooleanXor* clone() const { return new ModifierWithBooleanXor(*this); }
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) { return (_left.getOutput(input) != false) ^ (_right.getOutput(input) != false); }
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const { return (_left.getConstOutput(input) != false) ^ (_right.getConstOutput(input) != false); }
			
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_content_type getContent() { return _closure; }
			
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_content_type getConstContent() const { return _closure; }
		};
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy4
