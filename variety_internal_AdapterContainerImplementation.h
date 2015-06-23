/*
 *  variety_internal_AdapterContainerImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "variety_internal_GenericTraits.h"
#include "variety_internal_AdapterContainer.h"
#include "variety_internal_Implementation.h"


namespace variety {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ContainerTemplate>
		class AdapterContainerImplementation : 
		public virtual InterfaceTemplate,
		public virtual AdapterContainer<typename GenericTraits<ContainerTemplate>::ValueType>,
		public virtual Implementation
		{
		protected:
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
		private:
			// use ContainerTemplate in place of ContainerType to add a '&' if needed!
			ContainerTemplate _container;
		public:
			AdapterContainerImplementation(ContainerType& container) : _container(container) {}
			virtual ~AdapterContainerImplementation() {}
		public:
			// Implementation
			virtual AdapterContainerImplementation* duplicate() const { return new AdapterContainerImplementation(*this); }
			virtual std::string get_name() const { return typeid(AdapterContainerImplementation).name(); }
		public:
			// AdapterIteratorInterface
			virtual ContainerType& get_container() { return _container; }
			virtual const ContainerType& get_container() const { return _container; }
		};		
		
	} // namespace internal
	
	
	
} // namespace variety