/*
 *  lazy2_internal_PublishedBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 29/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy2_internal_Bridge.h"

namespace lazy2 {
	
	class Generic;
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename TypedBridgeTemplate = Bridge>
		class PublishedBridge :
		public TypedBridgeTemplate
		{
		public:
			PublishedBridge(const Generic& generic) : TypedBridgeTemplate(generic) {
#if defined(DEBUG)
				assert(dynamic_cast<const InterfaceTemplate*> (Generic::getImplementation()));
#endif
			}
			PublishedBridge(Implementation* implementation) : TypedBridgeTemplate(implementation) {
#if defined(DEBUG)
				assert(dynamic_cast<const InterfaceTemplate*> (implementation));
#endif
			}
		public:
			//FIXME: the following expose are useless !!!!
			InterfaceTemplate& expose() { return *this; }
			const InterfaceTemplate& expose() const { return *this; }
		};
		
	} // namespace internal
	
	
} // namespace lazy