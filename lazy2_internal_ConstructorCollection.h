/*
 *  lazy2_internal_ConstructorCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 24/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_Bridge.h"
#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_CollectionImplementation.h"
#include "lazy2_internal_InstanceImplementation.h"
#include <vector>
#include <utility>


namespace lazy2 {
	
	namespace internal {
	
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, typename ConstructorArgumentTemplate>
		class ConstructorCollection : 
		public Bridge
		{
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ContainerTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(container))) {}
			explicit ConstructorCollection(const std::pair<ValueTemplate, AssociateTemplate>& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename ContainerTemplate, typename ConstructorArgumentTemplate>
		class ConstructorCollection<ValueTemplate, void, ContainerTemplate, ConstructorArgumentTemplate> : 
		public Bridge
		{
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ContainerTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(container))) {}
			explicit ConstructorCollection(const ValueTemplate& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(), value)) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename ConstructorArgumentTemplate>
		class ConstructorCollection<ValueTemplate, void, ValueTemplate, ConstructorArgumentTemplate> : 
		public Bridge
		{
			typedef ValueTemplate ContainerTemplate;
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ContainerTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ContainerTemplate>(new internal::InstanceImplementation<ContainerTemplate>(container))) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ConstructorArgumentTemplate>
		class ConstructorCollection<ValueTemplate, AssociateTemplate, void, ConstructorArgumentTemplate> : 
		public Bridge
		{
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const std::pair<ValueTemplate, AssociateTemplate> & value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>(), value)) {}
		};
		
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class ConstructorCollection<ValueTemplate, AssociateTemplate, void, std::pair<ValueTemplate, AssociateTemplate> > : 
		public Bridge
		{
			typedef std::vector<std::pair<ValueTemplate, AssociateTemplate> > ConstructorArgumentTemplate;
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const std::pair<ValueTemplate, AssociateTemplate>& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>(), value)) {}
		};
		
		//================================================================
		template <typename ValueTemplate, typename ConstructorArgumentTemplate>
		class ConstructorCollection<ValueTemplate, void, void, ConstructorArgumentTemplate> : 
		public Bridge
		{
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const ValueTemplate& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(), value)) {}
		};
		
		//================================================================
		template <typename ValueTemplate>
		class ConstructorCollection<ValueTemplate, void, void, ValueTemplate> : 
		public Bridge
		{
			typedef std::vector<ValueTemplate> ConstructorArgumentTemplate;
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const ValueTemplate& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>(), value)) {}
		};

		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class ConstructorCollection<ValueTemplate, AssociateTemplate, void, void> : 
		public Bridge
		{
			typedef std::vector<std::pair<ValueTemplate, AssociateTemplate> > ConstructorArgumentTemplate;
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const std::pair<ValueTemplate, AssociateTemplate>& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, AssociateTemplate, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>(), value)) {}
		};
		
		//================================================================
		template <typename ValueTemplate>
		class ConstructorCollection<ValueTemplate, void, void, void> : 
		public Bridge
		{
			typedef std::vector<ValueTemplate> ConstructorArgumentTemplate;
		public:
			explicit ConstructorCollection() : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>())) {}
			explicit ConstructorCollection(Collection<ValueTemplate, void, void, false>& collection) : Bridge(collection) {}
			explicit ConstructorCollection(const ConstructorArgumentTemplate& container) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<const ConstructorArgumentTemplate&>(container))) {}
			explicit ConstructorCollection(const ValueTemplate& value) : Bridge(new typename internal::CollectionImplementation<ValueTemplate, void, ConstructorArgumentTemplate>(new internal::InstanceImplementation<ConstructorArgumentTemplate>(), value)) {}
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2

