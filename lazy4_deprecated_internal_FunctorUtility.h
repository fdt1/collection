/*
 *  lazy4_internal_FunctorUtility.h
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
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility
		{
		public:
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename input_template>
		struct FunctorUtility<void, input_template>
		{
			typedef void output_template;
			typedef typename internal::Type<output_template>::type output_type;
			typedef typename internal::Type<output_template>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { static output_type output = NULL; return output; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility<output_template&, input_template>
		{
			typedef typename internal::Type<output_template&>::type output_type;
			typedef typename internal::Type<output_template&>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getUniqueImplementation()->getOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template, typename input_template>
		struct FunctorUtility<const output_template&, input_template>
		{
			typedef typename internal::Type<const output_template&>::type output_type;
			typedef typename internal::Type<const output_template&>::const_type const_output_type;
			typedef typename internal::Type<input_template>::parameter_type parameter_input_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static output_type getOutput(bridge_template& bridge, parameter_input_type input) { return (output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static inline const_output_type getConstOutput(const bridge_template& bridge, parameter_input_type input) { return (const_output_type) (bridge.getImplementation()->getConstOutput((typename bridge_template::interface_type::parameter_input_type) (input))); }
		};
		
		
	} // namespace internal
	
} // namespace lazy4