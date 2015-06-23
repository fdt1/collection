/*
 *  lazy3_internal_IPair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IGeneric.h"

namespace lazy3 {
	
	namespace internal {
		
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class IPairOnFirst is a subdivision interface of IPair.
		//! it is dedicated on first_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class IPairOnFirst :
		public virtual IGeneric
		{
			typedef typename internal::Value<first_type>::const_type const_first_type;
		public:
			//! @return the first_type value
			virtual first_type getFirst() = 0;
			//! @return the first_type const value
			virtual const_first_type getConstFirst() const = 0;
		};
		
		//--------------------------------------------------------------------------------
		//! @class IPairOnSecond is a subdivision interface of IPair.
		//! it is dedicated on second_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class IPairOnSecond :
		public virtual IGeneric
		{
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
		public:
			//! @return the second_type value
			virtual template_second_type getSecond() = 0;
			//! @return the second_type const value
			virtual const_second_type getConstSecond() const = 0;
		};
		
#if 1
		//--------------------------------------------------------------------------------
		//! @class IPairOnFirst<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<>
		class IPairOnFirst<void> :
		public virtual IGeneric
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IPairOnSecond<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<>
		class IPairOnSecond<void> :
		public virtual IGeneric
		{};
#endif
		
		//--------------------------------------------------------------------------------
		//! @class IPair is the interface for a pair.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class IPair :
		public virtual IPairOnFirst<first_type>,
		public virtual IPairOnSecond<second_type>
		{
		};
#else
		//--------------------------------------------------------------------------------
		//! @class IPair is the interface for a pair.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class IPair :
		public virtual IGeneric
		{
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef typename internal::Value<first_type>::template_type template_first_type;
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
		public:
			//! @return the first_type value
			virtual template_first_type getFirst() = 0;
			//! @return the first_type const value
			virtual const_first_type getConstFirst() const = 0;
			//! @return the second_type value
			virtual template_second_type getSecond() = 0;
			//! @return the second_type const value
			virtual const_second_type getConstSecond() const = 0;
		};
#endif
		
		
	} // namespace internal
	
	
} // namespace lazy2
