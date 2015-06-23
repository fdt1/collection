/*
 *  lazy2_Generic.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Bridge.h"
#include "lazy2_internal_Implementation.h"

namespace lazy2 {
	
	class Generic :
	protected internal::Bridge
	{
	protected:
		Generic(internal::Implementation* implementation) : internal::Bridge(implementation) {}
		Generic(const internal::Bridge& bridge) : internal::Bridge(bridge) {}
		template <typename InheritOfBridge>
		static InheritOfBridge fabric(internal::Implementation* implementation) {
			return InheritOfBridge(implementation);
		}
	};
	
} // namespace lazy2
