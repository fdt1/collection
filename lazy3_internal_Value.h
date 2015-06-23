/*
 *  lazy3_internal_Value.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


namespace lazy3 {
	
	namespace internal {

		//! @class Value guesses the raw types
		template<typename value_type>
		struct Value
		{
			typedef value_type template_type;
			typedef value_type prime_type;
			typedef const value_type& parameter_type;
			typedef const value_type const_type;
			typedef value_type& ref_type;
			typedef const value_type& const_ref_type;
		};
		
		//! @class Value specialization
		template<typename value_type>
		struct Value<value_type&>
		{
			typedef value_type& template_type;
			typedef value_type prime_type;
			typedef value_type& parameter_type;
			typedef const value_type& const_type;
			typedef value_type& ref_type;
			typedef const value_type& const_ref_type;
		};
		
		//! @class Value specialization
		template<typename value_type>
		struct Value<const value_type&>
		{
			typedef const value_type& template_type;
			typedef value_type prime_type;
			typedef const value_type& parameter_type;
			typedef const value_type& const_type;
			typedef const value_type& ref_type;
			typedef const value_type& const_ref_type;
		};
		
		//! @class Value specialization
		template<typename value_type>
		struct Value<const value_type>
		{
			typedef const value_type template_type;
			typedef value_type prime_type;
			typedef const value_type& parameter_type;
			typedef const value_type const_type;
			typedef const value_type& ref_type;
			typedef const value_type& const_ref_type;
		};
		
		//! @class Value specialization
		template<>
		struct Value<void>
		{
			typedef void* value_type;
			typedef value_type template_type;
			typedef value_type prime_type;
			typedef const value_type& parameter_type;
			typedef const value_type const_type;
			typedef value_type& ref_type;
			typedef const value_type& const_ref_type;
		};
		

	
	} // namespace internal

} // namespace lazy2
