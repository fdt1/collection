/*
 *  lazy2_internal_TypedBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_Bridge.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename CallbackTemplate, typename TypedBridgeTemplate = Bridge>
		class TypedBridge :
		public CallbackTemplate,
		public TypedBridgeTemplate
		{
		public:
			TypedBridge(Implementation* implementation) : TypedBridgeTemplate(implementation) {
#if defined(DEBUG)
				assert(dynamic_cast<const typename CallbackTemplate::Interface*> (implementation));
#endif
			} 
			TypedBridge(const Bridge& bridge) : TypedBridgeTemplate(bridge) {
#if defined(DEBUG)
				assert(dynamic_cast<const typename CallbackTemplate::Interface*> (bridge.getImplementation()));
#endif
	}  
		};
		
	} // namespace internal
	
	
} // namespace lazy