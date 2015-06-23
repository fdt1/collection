/*
 *  lazy_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 13/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Implementation.h"
// for shared_ptr
#include <tr1/memory> 


namespace lazy {
	
	namespace internal {
		
		// bridge between an implementation
		class Bridge :
		{
		public:
			virtual ~Bridge() {}
		public:
			virtual const Implementation* get_implementation() const = 0;
			virtual Implementation* get_duplicated_implementation() const = 0;
			virtual Implementation* get_unshared_implementation() const = 0;
			virtual void set_implementation(Implementation* implementation) = 0;
			virtual void set_implementation(const Bridge& bridge) = 0;
			bool is_shared_implementation() const { return count_implementation_use() > 1; }
			virtual size_t count_implementation_use() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace lazy