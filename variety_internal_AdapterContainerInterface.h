/*
 *  variety_internal_AdapterContainerInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_GenericTraits.h"
#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
		
		template <typename ContainerTemplate>
		class AdapterContainerInterface :
		public virtual Implementation
		{
		public:
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
		public:
			virtual ContainerType& get_container() = 0;
			virtual const ContainerType& get_container() const = 0;
		};
		
	} // namespace internal
	
	
} // namespace variety