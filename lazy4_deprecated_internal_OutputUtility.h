/*
 *  lazy4_internal_OutputUtility.h
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
		template <typename output_template>
		struct OutputUtility
		{
			typedef typename internal::Type<output_template>::ref_type ref_output_type;
			typedef typename internal::Type<output_template>::const_ref_type const_ref_output_type;
			
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static ref_output_type getOutput(bridge_template& bridge) { return static_cast<ref_output_type> (bridge.getImplementation()->getOutput()); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static const_ref_output_type getConstOutput(const bridge_template& bridge) { return static_cast<const_ref_output_type> (bridge.getImplementation()->getConstOutput()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct OutputUtility<void>
		{
			typedef void output_template;
			typedef internal::Type<output_template>::type output_type;
			typedef internal::Type<output_template>::ref_type ref_output_type;
			typedef internal::Type<output_template>::const_ref_type const_ref_output_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static ref_output_type getOutput(bridge_template& bridge) { static output_type output = NULL; return output; }
			
			//! @return the content
			template <typename bridge_template>
			static const_ref_output_type getConstOutput(const bridge_template& bridge) { static output_type output = NULL; return output; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template>
		struct OutputUtility<output_template&>
		{
			typedef typename internal::Type<output_template&>::ref_type ref_output_type;
			typedef typename internal::Type<output_template&>::const_ref_type const_ref_output_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static ref_output_type getOutput(bridge_template& bridge) { return static_cast<ref_output_type> (bridge.getUniqueImplementation()->getOutput()); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static const_ref_output_type getConstOutput(const bridge_template& bridge) { return static_cast<const_ref_output_type> (bridge.getImplementation()->getConstOutput()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename output_template>
		struct OutputUtility<const output_template&>
		{
			typedef typename internal::Type<const output_template&>::ref_type ref_output_type;
			typedef typename internal::Type<const output_template&>::const_ref_type const_ref_output_type;
		public:
			//! @return the output of the functor
			template <typename bridge_template>
			static ref_output_type getOutput(bridge_template& bridge) { return static_cast<ref_output_type> (bridge.getImplementation()->getOutput()); }
			
			//! @return the output of the functor
			template <typename bridge_template>
			static const_ref_output_type getConstOutput(const bridge_template& bridge) { return static_cast<const_ref_output_type> (bridge.getImplementation()->getConstOutput()); }
		};
		
		
	} // namespace internal
	
} // namespace lazy4