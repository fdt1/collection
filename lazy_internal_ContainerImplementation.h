/*
 *  lazy_internal_ContainerImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_Implementation.h"


namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ContainerTemplate>
		class ContainerImplementation : 
		public virtual InterfaceTemplate,
		public virtual Implementation
		{
		protected:
			typedef typename ValueTraits<ContainerTemplate>::PrimeType ContainerPrimeType;
		private:
			ContainerTemplate _container;
		public:
			ContainerImplementation(ContainerPrimeType& container) : _container(container) {}
		public:
			// Implementation
			virtual ContainerImplementation* duplicate() const { return new ContainerImplementation(*this); }
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy