/*
 *  lazy2_internal_FlattenCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/02/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_FlattenCollectionImplementation.h"


namespace lazy2 {
	
	//================================================================
	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
	class Collection; 
	
	namespace internal {
		
		//================================================================
		template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_InheritanceTemplate__>
		class FlattenCollection
		{
		};
		
		//================================================================
		template <typename AssociateTemplate, typename ContainerTemplate, typename NestedValueTemplate, bool __ForInternalUseOnly_InheritanceTemplate__, typename NestedAssociateTemplate, typename NestedContainerTemplate, bool __NestedForInternalUseOnly_InheritanceTemplate__>
		class FlattenCollection<Collection<NestedValueTemplate, NestedAssociateTemplate, NestedContainerTemplate, __NestedForInternalUseOnly_InheritanceTemplate__>, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> 
		{
			typedef Collection<NestedValueTemplate, NestedAssociateTemplate, NestedContainerTemplate, __NestedForInternalUseOnly_InheritanceTemplate__> NestedCollectionType;
			typedef Collection<NestedCollectionType, AssociateTemplate, ContainerTemplate, __ForInternalUseOnly_InheritanceTemplate__> SelfType;
			typedef PublishedBridge<CollectionInterface<NestedCollectionType>, SelfType> CollectionBridge;
		public:
			virtual ~FlattenCollection() {}
			Collection<NestedValueTemplate, NestedAssociateTemplate, SelfType, true> flatten() const
			{ 
				Implementation* implementation = new FlattenCollectionImplementation<NestedCollectionType, SelfType>(dynamic_cast<const SelfType&> (*this));
				return Collection<NestedValueTemplate, NestedAssociateTemplate, SelfType, true>(implementation);
			}
		};
		
	} // namespace internal
	
	
} // namespace lazy2
