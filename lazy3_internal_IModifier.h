/*
 *  lazy3_internal_IModifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IGeneric.h"
#include "lazy3_internal_Value.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class IModifier is the interface for a flow.
		//--------------------------------------------------------------------------------
		template<typename old_type, typename new_type>
		class IModifier :
		public virtual IGeneric
		{
			typedef typename internal::Value<old_type>::parameter_type parameter_old_type;
		public:
			//! @return the new value.
			//! @param old_value the value to change.
			virtual new_type change(parameter_old_type old_value) = 0;
		};
		
#if !defined(VALUE_VOID)
		//--------------------------------------------------------------------------------
		//! @class IModifier specialization.
		//--------------------------------------------------------------------------------
		template<typename old_type>
		class IModifier<old_type, void> :
		public virtual IGeneric
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IModifier specialization.
		//--------------------------------------------------------------------------------
		template<typename new_type>
		class IModifier<void, new_type> :
		public virtual IGeneric
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IModifier specialization.
		//--------------------------------------------------------------------------------
		template<>
		class IModifier<void, void> :
		public virtual IGeneric
		{};
#endif
		
		
	} // namespace internal
	
	
} // namespace lazy2
