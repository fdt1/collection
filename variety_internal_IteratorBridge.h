/*
 *  variety_internal_IteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_BasicIteratorBridge.h"
#include "variety_internal_ForwardIteratorBridge.h"
#include "variety_internal_InputIteratorBridge.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class IteratorBridge :
		public virtual InputIteratorBridge<ValueTemplate>,
		public virtual BasicIteratorBridge,
		public virtual ForwardIteratorBridge
		{
		public:
			typedef IteratorInterface<ValueTemplate> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety