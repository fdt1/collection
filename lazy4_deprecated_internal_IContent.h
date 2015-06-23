/*
 *  lazy4_internal_IContent.h
 *  collection
 *
 *  Created by Francois et Fabienne on 01/09/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy4_internal_Type.h"

namespace lazy4 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IContent is the interface for a data container.
		//--------------------------------------------------------------------------------
		template<typename content_template>
		class IContent
		{
		public:
			typedef typename internal::Type<content_template>::ref_type ref_content_type;
			typedef typename internal::Type<content_template>::const_ref_type const_ref_content_type;
			typedef typename internal::Type<content_template>::parameter_type parameter_content_type;
		
		public:
			//! @return duplicate of the current implementation
			virtual IContent* clone() const = 0;
			
		public:
			//! @return the pointer ID
			virtual const void* getID() const = 0;
			
			//! @return the content
			virtual ref_content_type getContent() = 0;
			
			//! @return the content
			virtual const_ref_content_type getConstContent() const = 0;
			
			//! @return true if initialized
			virtual bool isValid() const = 0;			
		};
				
	} // namespace internal
	
	
} // namespace lazy4
