/*
 *  lazy3_internal_AccessorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_AccessorAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class AccessorBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type, typename auxilary_type>
		class AccessorBridge :
		public Bridge,
		public virtual AccessorAbstractBridge<old_type, new_type, auxilary_type>
		{
			typedef AccessorAbstractBridge<old_type, new_type, auxilary_type> AccessorAbstractBridge;
		public:
			AccessorBridge() {}
			AccessorBridge(const AccessorAbstractBridge& Accessor) : Bridge(Accessor) {}
		};
	
		//--------------------------------------------------------------------------------
		//! @class AccessorBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type>
		class AccessorBridge<old_type, new_type, void> :
		public Bridge,
		public virtual AccessorAbstractBridge<old_type, new_type, void>
		{
		public:
			AccessorBridge() {}
			template<typename any_auxilary_type>
			AccessorBridge(const AccessorAbstractBridge<old_type, new_type, any_auxilary_type>& Accessor) : Bridge(Accessor) {}
		};
		
	} // namespace internal
	
	
} // namespace lazy2
