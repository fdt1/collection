/*
 *  lazy4_internal_IFunctor.h
 *  collection
 *
 *  Created by Francois et Fabienne on 24/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IFunctor is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template>
		class IFunctor
		{
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::const_ref_type const_ref_input_type;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(const_ref_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(const_ref_input_type input) const = 0;
		};
		
	} // namespace internal
	
	
} // namespace lazy4
