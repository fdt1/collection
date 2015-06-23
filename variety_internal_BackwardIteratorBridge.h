/*
 *  variety_internal_BackwardIteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_BackwardIteratorInterface.h"
#include "variety_internal_Bridge.h"


namespace variety {
	
	namespace internal {
		
		class BackwardIteratorBridge :
		public virtual Bridge,
		public virtual BackwardIteratorInterface
		{
		public:
			typedef BackwardIteratorInterface InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		public:
			virtual void decrement() { get_interface().decrement(); }
			virtual void decrement(int offset) { get_interface().decrement(offset); }
			virtual int decrement_if_possible(int offset) { return get_interface().decrement_if_possible(offset); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety