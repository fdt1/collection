/*
 *  variety_internal_AdapterContainer.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_AdapterContainerInterface.h"

namespace variety {
	
	namespace internal {
		
		template <typename ContainerTemplate>
		class AdapterContainer :
		public virtual AdapterContainerInterface<ContainerTemplate>
		{
		public:
			typedef AdapterContainer<ContainerTemplate> SelfType;
		private:
			AdapterContainer();
			AdapterContainer(const SelfType&);
			AdapterContainer& operator= (const SelfType&);
		};
		
		
	} // namespace internal
	
	
} // namespace variety