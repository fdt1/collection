/*
 *  lazy4_internal_ClosureUtility.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_IModifier.h"
#include "lazy4_internal_Bridge.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ClosureUtility
		{
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static ref_content_type getClosure(bridge_template& bridge) { return static_cast<ref_content_type> (bridge.getUniqueImplementation()->getClosure()); }
			
			//! @return the content
			template <typename bridge_template>
			static const_ref_content_type getConstClosure(const bridge_template& bridge) { return static_cast<const_ref_content_type> (bridge.getImplementation()->getConstClosure()); }
			
			//! set the content
			//! @param content the new content to set.
			template <typename bridge_output_template, typename bridge_input_template, typename bridge_content_template>
			static ref_content_type setClosure(Bridge<IModifier<bridge_output_template, bridge_input_template, bridge_content_template> >& bridge, parameter_content_type content) { 
				return bridge.getUniqueImplementation()->setClosure(static_cast<typename internal::Type<bridge_content_template>::parameter_type> (content)); 
			}
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct ClosureUtility<void>
		{
			typedef void content_template;
			typedef internal::Type<content_template>::ref_type ref_content_type;
			typedef internal::Type<content_template>::type content_type;
			typedef internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef internal::Type<content_template>::parameter_type parameter_content_type;
			
		public:
			//! @return the content
			template <typename bridge_template>
			static ref_content_type getClosure(bridge_template& bridge) { static content_type content = NULL; return content; }
			
			//! @return the content
			template <typename bridge_template>
			static const_ref_content_type getConstClosure(const bridge_template& bridge) { static content_type content = NULL; return content; }
			
			//! set the content
			//! @param content the new content to set.
			template <typename bridge_template>
			static ref_content_type setClosure(bridge_template& bridge, parameter_content_type ) { static content_type content = NULL; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ClosureUtility<const content_template>
		{
			typedef typename internal::Type<const content_template>::ref_type ref_content_type;
			typedef typename internal::Type<const content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<const content_template>::parameter_type parameter_content_type;
		public:
			//! @return the content
			template <typename bridge_template>
			static ref_content_type getClosure(bridge_template& bridge) { return static_cast<ref_content_type> (bridge.getImplementation()->getConstClosure()); }
			
			//! @return the content
			template <typename bridge_template>
			static const_ref_content_type getConstClosure(const bridge_template& bridge) { return static_cast<const_ref_content_type> (bridge.getImplementation()->getConstClosure()); }
			
			//! set the content
			//! @param content the new content to set.
			template <typename bridge_output_template, typename bridge_input_template, typename bridge_content_template>
			static ref_content_type setClosure(Bridge<IModifier<bridge_output_template, bridge_input_template, bridge_content_template> >& bridge, parameter_content_type content) { 
				return bridge.getUniqueImplementation()->setClosure(static_cast<typename internal::Type<bridge_content_template>::parameter_type> (content)); 
			}
			
		};
		
		
	} // namespace internal
	
} // namespace lazy4