/*
 *  variety_internal_AdapterContainer_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "variety_internal_AdapterContainer.h"
#include "variety_internal_GenericTraits.h"
#include "variety_internal_AdapterContainerInterface.h"
#include "variety_internal_BasicContainerInterface.h"
#include "variety_internal_AdapterIteratorImplementation.h"
#include "variety_internal_RandomIteratorInterface.h"
#include <vector>

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AllocatorTemplate>
		class AdapterContainer<std::vector<ValueTemplate, AllocatorTemplate> > :
		public virtual AdapterContainerInterface<std::vector<ValueTemplate, AllocatorTemplate> >,
		public virtual BasicContainerInterface
		{
		protected:
			typedef std::vector<ValueTemplate, AllocatorTemplate> ContainerTemplate;
			typedef AdapterContainer<ContainerTemplate> SelfType;
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef AdapterIteratorImplementation<RandomIteratorInterface<ValueTemplate>, __gnu_cxx::__normal_iterator<ValueTemplate, ContainerTemplate>, ContainerTemplate> AdapterIteratorImplementationType;
		public:
			// AdapterContainerInterface
			virtual ContainerType& get_container() = 0;
			virtual const ContainerType& get_container() const = 0;
		public:
			// BasicContainerInterface
			virtual size_t size() const { return get_container().size(); }
			/* FIXME :
			virtual Implementation* begin() const { return new AdapterIteratorImplementationType(get_container().begin(), this); }
			virtual Implementation* begin() { return new AdapterIteratorImplementationType(get_container().begin(), this); }
			virtual Implementation* end() const { return new AdapterIteratorImplementationType(get_container().end(), this); }
			virtual Implementation* end() { return new AdapterIteratorImplementationType(get_container().end(), this); }
			 */
		};
		
		
	} // namespace internal
	
	
} // namespace variety