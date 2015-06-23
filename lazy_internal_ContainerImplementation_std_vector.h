/*
 *  lazy_internal_ContainerImplementation_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once



#include "variety_internal_ContainerImplementation.h"
#include "lazy_internal_Implementation.h"
#include "lazy_internal_ValueTraits.h"
#include <vector>

namespace lazy {
	
	namespace internal {
		
		template <typename InterfaceTemplate, typename ValueTemplate, typename AllocatorTemplate>
		class ContainerImplementation<InterfaceTemplate, std::vector<ValueTemplate, AllocatorTemplate> > :
		public virtual InterfaceTemplate,
		public virtual Implementation
		{
		protected:
			typedef std::vector<ValueTemplate, AllocatorTemplate> ContainerTemplate;
			typedef typename ValueTraits<ContainerTemplate>::PrimeType ContainerPrimeType;
			typedef IteratorImplementation<typename InterfaceTemplate::IteratorInterface, std::_Rb_tree_const_iterator<ValueTemplate>, ContainerTemplate> IteratorImplementationType;
		private:
			ContainerTemplate _container;
		public:
			ContainerImplementation(ContainerPrimeType& container) : _container(container) {}
		public:
			// Implementation
			virtual ContainerImplementation* duplicate() const { return new ContainerImplementation(*this); }
		public:
			// BasicContainerInterface
			virtual size_t get_size() const { return _container.size(); }
			// IterableInterface
			virtual Implementation* get_begin() const { return new IteratorImplementationType(_container.begin(), this); }
			/* FIXME :
			 virtual Implementation* begin() const { return new AdapterIteratorImplementationType(get_container().begin(), this); }
			 virtual Implementation* begin() { return new AdapterIteratorImplementationType(get_container().begin(), this); }
			 virtual Implementation* end() const { return new AdapterIteratorImplementationType(get_container().end(), this); }
			 virtual Implementation* end() { return new AdapterIteratorImplementationType(get_container().end(), this); }
			 */
		};
		
		
	} // namespace internal
	
	
} // namespace lazy