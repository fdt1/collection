/*
 *  lazy4_internal_IPair.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/11/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Type.h"

namespace lazy4 {
	
	template <typename first_template, typename second_template>
	class Pair;
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename first_template, typename second_template>
		class IPair
		{
		public:
			typedef typename internal::Type<first_template>::type first_type;
			typedef typename internal::Type<first_template>::const_type const_first_type;
			typedef typename internal::Type<second_template>::type second_type;
			typedef typename internal::Type<second_template>::const_type const_second_type;
			
		public:
			//! @return duplicate of the current implementation
			virtual IPair* clone() const = 0;
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const = 0;
			
			//! @return the first
			virtual first_type getFirst() = 0;
			
			//! @return the first
			virtual const_first_type getConstFirst() const = 0;
			
			//! @return the second
			virtual second_type getSecond() = 0;
			
			//! @return the second
			virtual const_second_type getConstSecond() const = 0;
			
			//! @return true if initialized
			virtual bool isValid() const = 0;			
		};
		
	} // namespace internal
	
	
} // namespace lazy4
