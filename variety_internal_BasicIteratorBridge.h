/*
 *  variety_internal_BasicIteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_Bridge.h"


namespace variety {
	
	namespace internal {
		
		class BasicIteratorBridge :
		public virtual Bridge,
		public virtual BasicIteratorInterface
		{
		public:
			typedef BasicIteratorInterface InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual bool is_equal(const BasicIteratorInterface& other) const { return get_interface().is_equal(other); }
			virtual bool is_valid() const { return get_interface().is_valid(); }
			virtual void restart() { get_interface().restart(); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety