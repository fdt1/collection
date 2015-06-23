/*
 *  variety_internal_ForwardIteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_Bridge.h"

namespace variety {
	
	namespace internal {
		
		class ForwardIteratorBridge :
		public virtual Bridge,
		public virtual ForwardIteratorInterface
		{
		public:
			typedef ForwardIteratorInterface InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual void increment() { get_interface().increment(); }
			virtual void increment(int offset) { get_interface().increment(offset); }
			virtual int increment_if_possible(int offset) { return get_interface().increment_if_possible(offset); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety