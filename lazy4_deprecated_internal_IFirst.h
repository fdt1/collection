/*
 *  lazy4_internal_IFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_Bridge.h"


namespace lazy4 {
	
	namespace internal {
		

		//--------------------------------------------------------------------------------
		//! @class IPairOnFirst is a subdivision interface of IPair.
		//! it is dedicated on first_type parameter.
		//! It is used to specialize on void type.
		//--------------------------------------------------------------------------------
		template<typename first_template>
		class IFirst
		{
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<first_template>::const_ref_type const_ref_first_type;
		
		public:
			//! @return the first_type value
			virtual first_type getFirst() = 0;
			
			//! @return the first_type const value
			virtual const_first_type getConstFirst() const = 0;
			
			//! iterate until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual size_t findFirst(const_ref_first_type first) = 0;
			
			//! iterate backward until we reach a given element.
			//! @return the number of elements stepped.
			//! @param first element to search
			virtual size_t rfindFirst(const_ref_first_type first) = 0;
		};
				
		
	} // namespace internal
	
	
} // namespace lazy4
