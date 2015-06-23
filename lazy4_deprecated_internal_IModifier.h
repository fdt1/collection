/*
 *  lazy4_internal_IModifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 22/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IContent.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename output_template, typename input_template, typename closure_template>
		class IModifier :
		public IContent<closure_template>
		{
		public:
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;

		public:
			//! @return duplicate of the current implementation
			virtual IModifier* clone() const = 0;
			
		public:
			//! @return the output of a functor
			virtual output_type getOutput(parameter_input_type input) = 0;
			
			//! @return the output of a functor
			virtual const_output_type getConstOutput(parameter_input_type input) const = 0;
		};
		
	} // namespace internal
	
	
} // namespace lazy4
