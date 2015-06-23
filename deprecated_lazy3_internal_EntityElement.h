/*
 *  lazy3_internal_EntityElement.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IEntity.h"
#include "lazy3_internal_EntityAdapter.h"

namespace lazy3 {
	
	namespace internal {
		
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityElement is an implementation of IEntity 
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class EntityElement : 
		//public virtual IEntity<first_type, second_type, container_type>,
		public EntityAdapter<first_type, second_type, container_type>
		{
			typedef IEntity<first_type, second_type, container_type> IEntity;
			typedef EntityAdapter<first_type, second_type, container_type> EntityAdapter;
			typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
		public:
			EntityElement() : EntityAdapter() {}
			EntityElement(parameter_container_type container) { setContent(container); }
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual IEntity* change(parameter_container_type container) { EntityElement* newElement = new EntityElement(*this); newElement->setContent(container); return newElement; }
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new EntityElement(*this); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
