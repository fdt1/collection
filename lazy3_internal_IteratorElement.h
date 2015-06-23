/*
 *  lazy3_internal_IteratorElement.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IIterator.h"
#include "lazy3_internal_IteratorAdapter.h"

namespace lazy3 {
	
	namespace internal {
		
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorElement is an implementation of IIterator 
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IteratorElement : 
		//public virtual IIterator<first_type, second_type, container_type>,
		public IteratorAdapter<first_type, second_type, container_type>
		{
			typedef IIterator<first_type, second_type, container_type> IIterator;
			typedef IteratorAdapter<first_type, second_type, container_type> IteratorAdapter;
			typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
		public:
			IteratorElement() : IteratorAdapter() {}
			IteratorElement(parameter_container_type container) { setContent(container); }
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual IIterator* change(parameter_container_type container) { IteratorElement* newElement = new IteratorElement(*this); newElement->setContent(container); return newElement; }
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new IteratorElement(*this); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
