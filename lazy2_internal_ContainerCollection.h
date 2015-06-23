/*
 *  lazy2_internal_ContainerCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_InstanceCallback.h"


namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Collection; 
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate>
	class Accessor;
	
	namespace internal {
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate>
		class ContainerCollection
		{
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class ContainerCollection<ValueTemplate, AssociateTemplate, void>
		{
		};
		
		//================================================================
		template <typename ValueTemplate, typename ContainerTemplate>
		class ContainerCollection<ValueTemplate, void, ContainerTemplate> :
		protected InstanceCallback<ContainerTemplate>
		{
			typedef typename internal::ValueTraits<ContainerTemplate>::PrimeType ContainerPrimeType;
			typedef InstanceCallback<ContainerTemplate> InstanceCallback;
		public:
			const ContainerPrimeType& inner() const { return InstanceCallback::getInstance(); }
			ContainerPrimeType& inner() { return InstanceCallback::getInstance(); }
		public:
		};
		
		//================================================================
		template <typename ValueTemplate>
		class ContainerCollection<ValueTemplate, void, void>
		{
		};
		
	} // namespace internal
	
	
} // namespace lazy2
