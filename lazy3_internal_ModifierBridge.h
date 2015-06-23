/*
 *  lazy3_internal_ModifierBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_ModifierAbstractBridge.h"
#include "lazy3_internal_Bridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class ModifierBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type>
		class ModifierBridge :
		public Bridge,
		public virtual ModifierAbstractBridge<old_type, new_type>
		{
			typedef ModifierAbstractBridge<old_type, new_type> ModifierAbstractBridge;
		public:
			ModifierBridge() {}
			ModifierBridge(const ModifierAbstractBridge& modifier) : Bridge(modifier) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierBridge specialization.
		//--------------------------------------------------------------------------------
		template<typename new_type>
		class ModifierBridge<void, new_type> :
		public Bridge,
		public virtual ModifierAbstractBridge<void, new_type>
		{
		public:
			ModifierBridge() {}
			template<typename any_old_type, typename any_new_type>
			ModifierBridge(const ModifierAbstractBridge<any_old_type, any_new_type>& modifier) : Bridge(modifier) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierBridge specialization.
		//--------------------------------------------------------------------------------
		template<typename old_type>
		class ModifierBridge<old_type, void> :
		public Bridge,
		public virtual ModifierAbstractBridge<old_type, void>
		{
		public:
			ModifierBridge() {}
			template<typename any_old_type, typename any_new_type>
			ModifierBridge(const ModifierAbstractBridge<any_old_type, any_new_type>& modifier) : Bridge(modifier) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class ModifierBridge specialization.
		//--------------------------------------------------------------------------------
		template<>
		class ModifierBridge<void, void> :
		public Bridge,
		public virtual ModifierAbstractBridge<void, void>
		{
		public:
			ModifierBridge() {}
			template<typename any_old_type, typename any_new_type>
			ModifierBridge(const ModifierAbstractBridge<any_old_type, any_new_type>& modifier) : Bridge(modifier) {}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
