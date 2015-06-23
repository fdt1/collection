/*
 *  variety_internal_AdapterIteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 26/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "variety_internal_AdapterIterator.h"
#include "variety_internal_GenericTraits.h"
#include "variety_internal_AdapterContainerImplementation.h"
#include "variety_internal_Implementation.h"
// for shared_ptr
#include <tr1/memory> 


namespace variety {
	
		
	namespace internal {
#if 0		
		template <typename InterfaceTemplate, typename IteratorTemplate, typename ContainerTemplate>
		class AdapterIteratorImplementation : 
		public virtual InterfaceTemplate,
		public virtual AdapterIterator<typename GenericTraits<IteratorTemplate>::ValueType, typename GenericTraits<ContainerTemplate>::ValueType>,
		public virtual SharedImplementation<AdapterContainerInterface<ContainerTemplate> >
		{
		protected:
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef typename GenericTraits<IteratorTemplate>::ValueType IteratorType;
			typedef AdapterContainerInterface<ContainerTemplate> ContainerImplementationType;
			typedef SharedImplementation<AdapterContainerInterface<ContainerTemplate> > SharedContainerImplementationType;
			typedef AdapterIterator<typename GenericTraits<IteratorTemplate>::ValueType, typename GenericTraits<ContainerTemplate>::ValueType> AdapterIterator;
		private:
			IteratorType _iterator;
		public:
			AdapterIteratorImplementation(const IteratorType& iter, const SharedContainerImplementationType shared_container_implementation) : SharedContainerImplementationType(shared_container_implementation), _iterator(iter)  {}
			AdapterIteratorImplementation(const SharedContainerImplementationType shared_container_implementation) : SharedContainerImplementationType(shared_container_implementation) { AdapterIterator::restart(); }
			virtual ~AdapterIteratorImplementation() {}
		public:
			// Implementation
			virtual AdapterIteratorImplementation* duplicate() const { return new AdapterIteratorImplementation(*this); }
			virtual std::string get_name() const { return typeid(AdapterIteratorImplementation).name(); }
		public:
			// AdapterIteratorInterface
			virtual ContainerType& get_container() { return SharedContainerImplementationType::get_implementation()->get_container(); }
			virtual const ContainerType& get_container() const { return SharedContainerImplementationType::get_implementation()->get_container(); }
			virtual IteratorType& get_iterator() { return _iterator; }
			virtual const IteratorType& get_iterator() const { return _iterator; }
		};		
#else
		template <typename InterfaceTemplate, typename IteratorTemplate, typename ContainerTemplate>
		class AdapterIteratorImplementation : 
		public virtual InterfaceTemplate,
		public virtual AdapterIterator<typename GenericTraits<IteratorTemplate>::ValueType, typename GenericTraits<ContainerTemplate>::ValueType>
		{
		protected:
			typedef typename GenericTraits<ContainerTemplate>::ValueType ContainerType;
			typedef typename GenericTraits<IteratorTemplate>::ValueType IteratorType;
			typedef AdapterContainerInterface<ContainerTemplate> ContainerImplementationType;
			typedef SharedImplementation<AdapterContainerInterface<ContainerTemplate> > SharedContainerImplementationType;
			typedef AdapterIterator<typename GenericTraits<IteratorTemplate>::ValueType, typename GenericTraits<ContainerTemplate>::ValueType> AdapterIterator;
		private:		
			SharedContainerImplementationType _shared_implementation;
			IteratorType _iterator;
		public:
			AdapterIteratorImplementation(const IteratorType& iter, const SharedContainerImplementationType& shared_container_implementation) : _shared_implementation(shared_container_implementation), _iterator(iter)  {}
			AdapterIteratorImplementation(const SharedContainerImplementationType& shared_container_implementation) : _shared_implementation(shared_container_implementation) { AdapterIterator::restart(); }
			virtual ~AdapterIteratorImplementation() {}
		public:
			// Implementation
			virtual AdapterIteratorImplementation* duplicate() const { return new AdapterIteratorImplementation(_iterator, _shared_implementation); }
			virtual std::string get_name() const { return typeid(AdapterIteratorImplementation).name(); }
		public:
			// AdapterIteratorInterface
			virtual ContainerType& get_container() { return _shared_implementation.get_implementation()->get_container(); }
			virtual const ContainerType& get_container() const { return _shared_implementation.get_implementation()->get_container(); }
			virtual IteratorType& get_iterator() { return _iterator; }
			virtual const IteratorType& get_iterator() const { return _iterator; }
		};		
#endif	
	} // namespace internal
	
	
	
} // namespace variety