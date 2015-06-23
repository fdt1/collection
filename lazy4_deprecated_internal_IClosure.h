/*
 *  lazy4_internal_IClosure.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Iclosure is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename closure_template>
		class IClosure
		{
			typedef typename internal::Type<closure_template>::ref_type ref_closure_type;
			typedef typename internal::Type<closure_template>::const_ref_type const_ref_closure_type;
			typedef typename internal::Type<closure_template>::parameter_type parameter_closure_type;
			
		public:
			//! @return the closure
			virtual ref_closure_type getClosure() = 0;
			
			//! @return the closure
			virtual const_ref_closure_type getConstClosure() const = 0;
			
			//! set the closure
			//! @param closure the new closure to set.
			virtual ref_closure_type setClosure(parameter_closure_type closure) = 0;
		};
		
	} // namespace internal
	
	
} // namespace lazy4
