/*
 *  variety_internal_AdapterIteratorInterface.h
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
		
		template <typename IteratorTemplate, typename ContainerTemplate>
		class AdapterIteratorInterface :
		public virtual Implementation
		{
		public:
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef typename GenericTraits<IteratorTemplate>::ValueType IteratorType;
		public:
			virtual ContainerType& get_container() = 0;
			virtual const ContainerType& get_container() const = 0;
			virtual IteratorType& get_iterator() = 0;
			virtual const IteratorType& get_iterator() const = 0;
		};
		
		
	} // namespace internal
	
	
} // namespace variety