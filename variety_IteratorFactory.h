/*
 *  variety_IteratorFactory.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_internal_AdapterIteratorImplementation.h"
#include "variety_internal_AdapterContainerImplementation.h"
#include "variety_internal_BasicContainerInterface.h"
#include "variety_RandomIterator.h"


namespace variety {
	
	template <typename IteratorTemplate>
	class IteratorFactory : 
	public virtual IteratorTemplate
	{
	public:
		typedef typename IteratorTemplate::ValueType ValueType;
		typedef typename IteratorTemplate::InterfaceType InterfaceType;
		typedef typename IteratorTemplate::BridgeType BridgeType;
	protected:
	public:
		template <typename ContainerTemplate, typename ContainerIteratorTemplate>
		IteratorFactory(const ContainerIteratorTemplate& iter, ContainerTemplate& container, bool copy_container = false) {
			typedef internal::AdapterIteratorImplementation<InterfaceType, ContainerIteratorTemplate, ContainerTemplate> AdapterIteratorImplementationType;
			typedef internal::AdapterContainerImplementation<internal::BasicContainerInterface, ContainerTemplate> AdapterContainerImplementationType;
			typedef internal::AdapterContainerImplementation<internal::BasicContainerInterface, ContainerTemplate&> AdapterContainerRefImplementationType;
			if (copy_container) {
				set_implementation(new AdapterIteratorImplementationType(iter, new AdapterContainerImplementationType(container))); 
			} else {
				set_implementation(new AdapterIteratorImplementationType(iter, new AdapterContainerRefImplementationType(container))); 
			}
		}
		template <typename ContainerTemplate>
		IteratorFactory(ContainerTemplate& container, bool copy_container = false) {
			typedef typename ContainerTemplate::iterator ContainerIteratorTemplate;
			typedef internal::AdapterIteratorImplementation<InterfaceType, ContainerIteratorTemplate, ContainerTemplate> AdapterIteratorImplementationType;
			typedef internal::AdapterContainerImplementation<internal::BasicContainerInterface, ContainerTemplate> AdapterContainerImplementationType;
			typedef internal::AdapterContainerImplementation<internal::BasicContainerInterface, ContainerTemplate&> AdapterContainerRefImplementationType;
			if (copy_container) {
				set_implementation(new AdapterIteratorImplementationType(new AdapterContainerImplementationType(container))); 
			} else {
				set_implementation(new AdapterIteratorImplementationType(new AdapterContainerRefImplementationType(container))); 
			}
		}
	public:
		IteratorFactory() {}
	};
	
	
	
} // namespace variety