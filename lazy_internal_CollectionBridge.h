/*
 *  lazy_internal_CollectionBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_Bridge.h"
#include "lazy_internal_CollectionInterface.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class CollectionBridge :
		public virtual Bridge,
		public virtual CollectionInterface<ValueTemplate, AssociateTemplate>
		{
		};
		
		
	} // namespace internal
	
	
} // namespace lazy