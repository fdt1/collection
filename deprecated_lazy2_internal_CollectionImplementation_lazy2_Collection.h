/*
 *  lazy2_internal_CollectionImplementation_lazy2_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 17/01/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_TypedBridge.h"
#include "lazy2_internal_CollectionCallback.h"
#include "lazy2_internal_AssociateCollectionCallback.h"
#include "lazy2_internal_CollectionImplementation.h"
#include "lazy2_internal_InstanceCallback.h"
#include <vector>


namespace lazy2 {

	template <typename ValueTemplate, typename AssociateTemplate, typename ContainerTemplate, bool __ForInternalUseOnly_AssociateInheritanceTemplate__>
	class Collection;
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate, 
		          typename AnyValueTemplate, typename AnyAssociateTemplate, typename AnyContainerTemplate, bool __AnyAssociateInheritanceTemplate__>
		class CollectionImplementation<ValueTemplate, AssociateTemplate, Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, __AnyAssociateInheritanceTemplate__> > :
		public CollectionCallback<ValueTemplate>,
		public AssociateCollectionCallback<AssociateTemplate>,
		public virtual Callback,
		public Implementation
		{
			typedef Collection<AnyValueTemplate, AnyAssociateTemplate, AnyContainerTemplate, __AnyAssociateInheritanceTemplate__> InstanceTemplate;
		public:
			TypedBridge<InstanceCallback<InstanceTemplate> > _instanceBridge;
		public:
			CollectionImplementation(const TypedBridge<InstanceCallback<InstanceTemplate> >& instanceBridge) : _instanceBridge(instanceBridge) {}
			// Implementation Interface
			virtual Implementation* duplicate() const { return new CollectionImplementation(*this); }			
		public:
			// Callback Interface
			virtual const Implementation* getImplementation() const { return _instanceBridge.getImplementation(); }
			virtual Implementation* getduplicateImplementation() const { return _instanceBridge.getduplicateImplementation(); }
			virtual Implementation* getUniqueImplementation() { return _instanceBridge.getUniqueImplementation(); }			
		};
		
	} // namespace internal
	
} // namespace lazy2