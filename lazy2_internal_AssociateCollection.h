/*
 *  lazy2_internal_AssociateCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_AssociateCollectionCallback.h"


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
		class AssociateCollection
		{
			typedef Collection<ValueTemplate, AssociateTemplate, ContainerTemplate, true> SelfType;
			typedef typename internal::ValueTraits<AssociateTemplate>::PrimeType AssociatePrimeType;
		public:
		};
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate>
		class AssociateCollection<ValueTemplate, AssociateTemplate, void> :
		protected AssociateCollectionCallback<AssociateTemplate>
		{
		};
		
		//================================================================
		template <typename ValueTemplate, typename ContainerTemplate>
		class AssociateCollection<ValueTemplate, void, ContainerTemplate>
		{
		};
		
		//================================================================
		template <typename ValueTemplate>
		class AssociateCollection<ValueTemplate, void, void>
		{
		};
		
	} // namespace internal
	
	
} // namespace lazy2
