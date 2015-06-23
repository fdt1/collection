/*
 *  variety_internal_BasicContainerBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */




#pragma once

#include "variety_internal_BasicContainerInterface.h"
#include "variety_internal_Bridge.h"


namespace variety {
	
	namespace internal {
		
		class BasicContainerBridge :
		public virtual Bridge,
		public virtual BasicContainerInterface
		{
		public:
			typedef BasicContainerInterface InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			// TODO: FIXME: to fill ...
			virtual size_t size() const { return get_interface().size(); }
			virtual Implementation* begin() const { return get_interface().begin(); }
			virtual Implementation* begin() { return get_interface().begin(); }
			virtual Implementation* end() const { return get_interface().end(); }
			virtual Implementation* end() { return get_interface().end(); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety