/*
 *  lazy3_internal_IContent.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_internal_IGeneric.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename content_type>
		class IContent :
		public virtual IGeneric
		{
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
		public:
			//! @return the content
			virtual ref_content_type getContent() const = 0;
			//! duplicate the content if shared
			//! @return the content
			virtual ref_content_type getUniqueContent() = 0;
			//! @return the content
			virtual const_ref_content_type getConstContent() const = 0;
			//! set the content
			//! @param content the new content to set.
			virtual const_ref_content_type setContent(parameter_content_type content) = 0;
		};
	
	
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class IContent<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<>
		class IContent<void> :
		public virtual IGeneric
		{};
#endif	
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
