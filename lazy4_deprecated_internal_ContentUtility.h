/*
 *  lazy4_internal_ContentUtility.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy4_internal_Type.h"
#include "lazy4_internal_Bridge.h"


namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ContentUtility
		{
		public:
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;

		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { return (ref_content_type) (bridge.getUniqueImplementation()->getContent()); }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { return (const_ref_content_type) (bridge.getImplementation()->getConstContent()); }

		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <>
		struct ContentUtility<void>
		{
			typedef void content_template;
			typedef internal::Type<content_template>::ref_type ref_content_type;
			typedef internal::Type<content_template>::type content_type;
			typedef internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef internal::Type<content_template>::parameter_type parameter_content_type;

		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { static content_type content = NULL; return content; }
		
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { static content_type content = NULL; return content; }
		};
		
		//--------------------------------------------------------------------------------
		//! @class Implementation class is the pointer version of any lazy object
		//--------------------------------------------------------------------------------
		template <typename content_template>
		struct ContentUtility<const content_template>
		{
			typedef typename internal::Type<const content_template>::ref_type ref_content_type;
			typedef typename internal::Type<const content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<const content_template>::parameter_type parameter_content_type;
		public:
			//! @return the content
			template <typename bridge_template>
			static inline ref_content_type getContent(bridge_template& bridge) { return (ref_content_type) (bridge.getImplementation()->getConstContent()); }
			
			//! @return the content
			template <typename bridge_template>
			static inline const_ref_content_type getConstContent(const bridge_template& bridge) { return (const_ref_content_type) (bridge.getImplementation()->getConstContent()); }
		};
		
		
	} // namespace internal
	
} // namespace lazy4