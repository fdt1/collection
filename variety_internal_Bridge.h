/*
 *  variety_internal_Bridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_Implementation.h"


namespace variety {
	
	namespace internal {
		
		// bridge between an implementation and an implementation
		class Bridge 
		{
		protected:
			//virtual void set_implementation(internal::Implementation* implementation) = 0;
			virtual internal::Implementation* get_implementation() = 0;
		public:
			virtual const internal::Implementation* get_implementation() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety