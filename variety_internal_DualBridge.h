/*
 *  variety_internal_DualBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_Implementation.h"
#include "variety_internal_Bridge.h"


namespace variety {
	
	namespace internal {
		
		// bridge between an implementation and an implementation
		class DualBridge :
		public virtual Bridge
		{
		protected:
			virtual void set_dual_implementation(internal::Implementation* implementation) = 0;
			virtual internal::Implementation* get_dual_implementation() = 0;
		public:
			virtual const internal::Implementation* get_dual_implementation() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety