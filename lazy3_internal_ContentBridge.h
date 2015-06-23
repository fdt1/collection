/*
 *  lazy3_internal_ContentBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 25/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class AccessorBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<typename content_type>
		class ContentBridge :
		public Bridge,
		public virtual ContentAbstractBridge<content_type>
		{
			typedef ContentAbstractBridge<content_type> ContentAbstractBridge;
		public:
			ContentBridge() {}
			ContentBridge(const ContentAbstractBridge& content) : Bridge(content) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class AccessorBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<>
		class ContentBridge<void> :
		public Bridge,
		public virtual ContentAbstractBridge<void>
		{
		public:
			ContentBridge() {}
			template<typename any_content_type>
			ContentBridge(const ContentAbstractBridge<any_content_type>& content) : Bridge(content) {}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
