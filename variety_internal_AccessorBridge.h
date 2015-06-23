/*
 *  variety_internal_AccessorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 08/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputAccessorBridge.h"
#include "variety_internal_AccessorInterface.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate>
		class AccessorBridge :
		public virtual InputAccessorBridge<ValueTemplate, PrevValueTemplate>,
		public virtual Bridge
		{
		public:
			typedef AccessorInterface<ValueTemplate, PrevValueTemplate> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety