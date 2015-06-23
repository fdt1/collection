/*
 *  lazy4_internal_Type.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once



namespace lazy4 {
	
	template<typename first_template, typename second_template, typename content_template>
	class Iterator;
	
	template<typename first_template, typename second_template, typename content_template>
	class Flow;
	
	template<typename first_template, typename second_template>
	class Pair;
	
	template<typename first_template, typename second_template, typename content_template>
	class Collection;
	
	template<typename first_template, typename second_template, typename closure_template>
	class Modifier;
	
	namespace internal {
		
		template<typename T>
		static inline T& getReference(T* t) { return *t; }
		
		template<typename T>
		static inline const T& getReference(const T* t) { return *t; }
		
		template<typename T>
		static inline T& getReference(T& t) { return t; }
		
		template<typename T>
		static inline const T& getReference(const T& t) { return t; }
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type
		{
			typedef value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef value_template template_type;
			typedef value_template const_template_type;
			typedef const value_template const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<value_template&>
		{
			typedef value_template& type;
			typedef value_template prime_type;
			typedef value_template& parameter_type;
			typedef value_template& template_type;
			typedef const value_template& const_template_type;
			typedef const value_template& const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<const value_template&>
		{
			typedef const value_template& type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef const value_template& template_type;
			typedef const value_template& const_template_type;
			typedef const value_template& const_type;
			typedef const value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef const value_template* pointer_type;
			typedef const value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<typename value_template>
		struct Type<const value_template>
		{
			typedef const value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef const value_template template_type;
			typedef const value_template const_template_type;
			typedef const value_template const_type;
			typedef const value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef const value_template* pointer_type;
			typedef const value_template* const const_pointer_type;
		};
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type<value_template*>
		{
			typedef value_template* type;
			typedef value_template* prime_type;
			typedef value_template* const& parameter_type;
			typedef value_template* template_type;
			typedef value_template* const_template_type;
			typedef value_template* const const_type;
			typedef value_template*& ref_type;
			typedef value_template* const& const_ref_type;
			typedef value_template* pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value guesses the raw types
		template<typename value_template>
		struct Type<value_template* const>
		{
			typedef value_template* const type;
			typedef value_template* prime_type;
			typedef value_template* const& parameter_type;
			typedef value_template* template_type;
			typedef value_template* const const_template_type;
			typedef value_template* const const_type;
			typedef value_template* const& ref_type;
			typedef value_template* const& const_ref_type;
			typedef value_template* const pointer_type;
			typedef value_template* const const_pointer_type;
		};
		
		//! @class Value specialization
		template<>
		struct Type<void>
		{
			typedef void* value_template;
			typedef value_template type;
			typedef value_template prime_type;
			typedef const value_template& parameter_type;
			typedef void template_type;
			typedef void const_template_type;
			typedef const value_template const_type;
			typedef value_template& ref_type;
			typedef const value_template& const_ref_type;
			typedef value_template pointer_type;
			typedef value_template const const_pointer_type;
		};
		
		
		//! @class Value specialization
		template<typename value_template>
		struct NestedType
		{
			typedef void first_type;
			typedef void second_type;
			typedef void content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Collection<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Iterator<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Flow<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<lazy4::Modifier<first_template, second_template, closure_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<lazy4::Pair<first_template, second_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Collection<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Iterator<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<lazy4::Flow<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<lazy4::Modifier<first_template, second_template, closure_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<lazy4::Pair<first_template, second_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Collection<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Iterator<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Flow<first_template, second_template, content_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<const lazy4::Modifier<first_template, second_template, closure_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<const lazy4::Pair<first_template, second_template>& >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Collection<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Iterator<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename content_template>
		struct NestedType<const lazy4::Flow<first_template, second_template, content_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef content_template content_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template, typename closure_template>
		struct NestedType<const lazy4::Modifier<first_template, second_template, closure_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
			typedef closure_template closure_type;
		};
		
		//! @class Value specialization
		template<typename first_template, typename second_template>
		struct NestedType<const lazy4::Pair<first_template, second_template> >
		{
			typedef first_template first_type;
			typedef second_template second_type;
		};
		
		
	} // namespace internal
	
} // namespace lazy4
