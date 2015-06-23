/*
 *  lazy_Iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy_Generic.h"
#include "lazy_internal_IIterator.h"
#include "lazy_internal_IteratorImplementation.h"

namespace lazy {
	
	template <typename ValueTemplate, typename AssociateTemplate = bool>
	class Iterator : 
	public virtual Generic
	{
	protected:
		typedef typename internal::IIterator<ValueTemplate, AssociateTemplate> IteratorInterfaceType;
	public:
		Iterator() {}
		
		explicit Iterator(const Generic& generic) { 
			if (IteratorInterfaceType::is_compatible(generic)) {
				Bridge::setImplementation(generic);
			}
		}
		
		template <typename IteratorTemplate>
		Iterator(const IteratorTemplate& iterator) {
			typedef internal::IteratorImplementation<IteratorInterfaceType, const IteratorTemplate&> IteratorImplementationType;
			Generic::setImplementation(new IteratorImplementationType(iterator));
		}
		
	};
	
} // namespace lazy
