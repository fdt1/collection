/*
 *  lazy4_Modifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 29/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Modifier.h"


namespace lazy4 {
	
	
	//--------------------------------------------------------------------------------
	//! @class IteratorWithStaticCast is an implementation of a Iterator to overwrite 
	//! the first type accessor.
	//--------------------------------------------------------------------------------
	template<typename output_template = void, typename input_template = void, typename closure_template = void>
	class Modifier : 
	protected internal::ModifierBridge<output_template, input_template, closure_template>
	{
		friend class internal::ModifierBridge<output_template, input_template, closure_template>;

	public:
		typedef typename internal::Type<input_template>::type input_type;
		typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		typedef typename internal::Type<output_template>::type output_type;
		typedef typename internal::Type<output_template>::const_type const_output_type;
		typedef typename internal::Type<closure_template>::type closure_type;
		typedef typename internal::Type<closure_template>::ref_type ref_closure_type;
		typedef typename internal::Type<closure_template>::const_ref_type const_ref_closure_type;
		typedef typename internal::Type<closure_template>::parameter_type parameter_closure_type;
		
	public:
		typedef output_type (*function_with_const_ref_closure_type) (parameter_input_type input, const_ref_closure_type closure);
		typedef output_type (*function_with_closure_type) (input_type input, const_ref_closure_type closure);
		typedef output_type (*function_type_const_ref) (parameter_input_type input);
		typedef output_type (*function_type) (input_type input);
		
	public:
		typedef typename internal::IModifier<output_template, input_template, closure_template> Implementation;
		typedef typename internal::ModifierBridge<output_template, input_template, closure_template> Bridge;
		
	public:
		//! default constructor
		Modifier()
		: Bridge(new internal::ModifierWithFunction<output_template, input_template, closure_template, void>()) {}

		//! constructor with a function
		template <typename function_template>
		Modifier(function_template function) 
		: Bridge(new internal::ModifierWithFunction<output_template, input_template, closure_template, function_template>(function)) {}
		
		//! constructor with a function
		template<typename function_template>
		Modifier(function_template function, parameter_closure_type closure) 
		: Bridge(new internal::ModifierWithFunction<output_template, input_template, closure_template, function_template>(function, closure)) {}
		
		//! constructor that convert into other templates
		template <typename any_output_template, typename any_input_template, typename any_closure_template>
		Modifier(const Modifier<any_output_template, any_input_template, any_closure_template>& anyModifier)
		: Bridge(new internal::ModifierWithStaticCast<output_template, input_template, closure_template, 
				 typename Modifier<any_output_template, any_input_template, any_closure_template>::Bridge>(Modifier<any_output_template, any_input_template, any_closure_template>::Bridge::cast(anyModifier))) {}
		
		//! internal constructor
		Modifier(Implementation* implementation, bool, bool) : Bridge(implementation) {}
		
	public:
		//! @href lazy3::internal::IClosure::getClosure
		ref_closure_type closure() { return Bridge::getContent(); }
		
		//! @href lazy3::internal::IClosure::getConstClosure
		const_ref_closure_type closure() const { return Bridge::getConstContent(); }
		
		//! @return the validity of the current Modifier. 
		bool good() const { return Bridge::good(); }
		
	public:
		//! @return the output of a functor
		output_type operator() (parameter_input_type input) { return Bridge::getOutput(input); }
		
		//! @return the output of a functor
		const_output_type operator() (parameter_input_type input) const { return Bridge::getConstOutput(input); }
		
		//! cast operator which converts in a more agnostic type
		operator Modifier<output_template> () { return Modifier<output_template>(new internal::ModifierWithStaticCast<output_template, void, void, 
			typename Modifier<output_template, input_template, closure_template>::Bridge>(*this), true, true); }
		
		//! cast operator which converts in a more agnostic type
		operator Modifier<output_template, input_template> () const { return Modifier<output_template, input_template>(new internal::ModifierWithStaticCast<output_template, input_template, void,
			typename Modifier<output_template, input_template, closure_template>::Bridge>(*this), true, true); }
		
		template<typename any_output_template, typename any_closure_template>
		Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> > operator &&(const Modifier<any_output_template, input_template, any_closure_template>& modifier) const {
			return Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> >(new internal::ModifierWithBooleanAnd<output_template, any_output_template, input_template, closure_template, any_closure_template>(*this, Modifier<any_output_template, input_template, any_closure_template>::Bridge::cast(modifier)), true, true);
		}
		
		template<typename any_output_template, typename any_closure_template>
		Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> > operator ||(const Modifier<any_output_template, input_template, any_closure_template>& modifier) const {
			return Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> >(new internal::ModifierWithBooleanOr<output_template, any_output_template, input_template, closure_template, any_closure_template>(*this, Modifier<any_output_template, input_template, any_closure_template>::Bridge::cast(modifier)), true, true);
		}
		
		template<typename any_output_template, typename any_closure_template>
		Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> > operator ^(const Modifier<any_output_template, input_template, any_closure_template>& modifier) const {
			return Modifier<bool, input_template, Pair<typename internal::Type<closure_template>::ref_type, typename internal::Type<any_closure_template>::ref_type> >(new internal::ModifierWithBooleanXor<output_template, any_output_template, input_template, closure_template, any_closure_template>(*this, Modifier<any_output_template, input_template, any_closure_template>::Bridge::cast(modifier)), true, true);
		}
		
		Modifier<bool, input_template, closure_template> operator !() const {
			return Modifier<bool, input_template, closure_template>(new internal::ModifierWithBooleanNot<output_template, input_template, closure_template>(*this), true, true);
		}
		
	public:
		template<typename new_output_template, typename new_closure_template>
		Modifier<new_output_template, input_template, new_closure_template> 
		serialize(const Modifier<new_output_template, output_template, new_closure_template>& modifier) const { 
			return Modifier<new_output_template, input_template, new_closure_template>(new internal::ModifierWithModifier<new_output_template, input_template, new_closure_template, output_template, closure_template>(*this, Modifier<new_output_template, output_template, new_closure_template>::Bridge::cast(modifier)), true, true); 
		}
		
	};

	
	
	
	
} // namespace lazy4
