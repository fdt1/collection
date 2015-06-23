/*
 *  variety_internal_PtrDiffIteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_PtrDiffIteratorInterface.h"
#include "variety_internal_Bridge.h"


namespace variety {
	
	namespace internal {
		
		class PtrDiffIteratorBridge :
		public virtual Bridge,
		public virtual PtrDiffIteratorInterface
		{
		public:
			typedef PtrDiffIteratorInterface InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual int diff(const PtrDiffIteratorInterface& other) const { return get_interface().diff(other); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety