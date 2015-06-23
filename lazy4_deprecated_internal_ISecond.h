/*
 *  lazy4_internal_ISecond.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"


namespace lazy4 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IPairOnsecond is a subdivision interface of IPair.
		//! it is dedicated on second_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename second_template>
		class ISecond
		{
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			typedef typename internal::Type<second_template>::const_ref_type const_ref_second_type;

		public:
			//! @return the second_type value
			virtual second_type getSecond() = 0;
			
			//! @return the second_type const value
			virtual const_second_type getConstSecond() const = 0;
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual size_t findSecond(const_ref_second_type second) = 0;
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param second element to search
			virtual size_t rfindSecond(const_ref_second_type second) = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace lazy4
