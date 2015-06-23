/*
 *  lazy_Collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 30/04/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_Generic.h"
#include "lazy_internal_ICollection.h"
#include "lazy_internal_ContainerImplementation.h"

namespace lazy {
	
	template <typename ValueTemplate, typename AssociateTemplate = bool>
	class Collection : 
	public virtual Generic
	{
	protected:
		typedef typename internal::ICollection<ValueTemplate, AssociateTemplate> CollectionInterfaceType;
	public:
		Collection() {}
		
		explicit Collection(const Generic& generic) { 
			if (CollectionInterfaceType::is_compatible(generic)) {
				Bridge::setImplementation(generic);
			}
		}
		
		template <typename ContainerTemplate>
		Collection(const ContainerTemplate& container) {
			typedef internal::ContainerImplementation<CollectionInterfaceType, const ContainerTemplate&> ContainerImplementationType;
			Generic::setImplementation(new ContainerImplementationType(container));
		}
		
	};

} // namespace lazy
