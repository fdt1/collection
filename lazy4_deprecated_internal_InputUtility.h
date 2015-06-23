/*
 *  lazy4_internal_InputUtility.h
 *  collection
 *
 *  Created by Francois et Fabienne on 22/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IModifier.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename input_template>
		struct InputUtility
		{
			typedef typename internal::Type<input_template>::ref_type ref_input_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! set the content
			//! @param content the new content to set.
			template <typename bridge_output_template, typename bridge_input_template, typename bridge_auxilary_template>
			static ref_input_type setInput(Bridge<IModifier<bridge_output_template, bridge_input_template, bridge_auxilary_template> >& bridge, parameter_input_type input) { 
				return bridge.getUniqueImplementation()->setInput(static_cast<typename internal::Type<bridge_input_template>::parameter_type> (input)); 
			}
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct InputUtility<void>
		{
			typedef void input_template;
			typedef internal::Type<input_template>::type input_type;
			typedef internal::Type<input_template>::ref_type ref_input_type;
			typedef internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! set the content
			//! @param content the new content to set.
			template <typename bridge_template>
			static ref_input_type setInput(bridge_template& bridge, parameter_input_type ) { static input_type input = NULL; return input; }
		};
		
	} // namespace internal
	
} // namespace lazy4