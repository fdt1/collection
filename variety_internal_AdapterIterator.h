/*
 *  variety_internal_AdapterIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_AdapterIteratorInterface.h"

namespace variety {
	
	namespace internal {
		
		template <typename IteratorTemplate, typename ContainerTemplate>
		class AdapterIterator :
		public virtual AdapterIteratorInterface<IteratorTemplate, ContainerTemplate>
		{
		public:
			typedef AdapterIterator<IteratorTemplate, ContainerTemplate> SelfType;
		private:
			AdapterIterator();
			AdapterIterator(const SelfType&);
			AdapterIterator& operator= (const SelfType&);
		};
		
		
	} // namespace internal
	
	
} // namespace variety