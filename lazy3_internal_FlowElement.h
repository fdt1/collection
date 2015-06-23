/*
 *  lazy3_internal_FlowElement.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IFlow.h"
#include "lazy3_internal_FlowAdapter.h"

namespace lazy3 {
	
	namespace internal {
		
		

		//--------------------------------------------------------------------------------
		//! @class FlowElement is an implementation of IFlow 
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class FlowElement : 
		//public virtual IFlow<first_type, second_type, container_type>,
		public FlowAdapter<first_type, second_type, container_type>
		{
			typedef IFlow<first_type, second_type, container_type> IFlow;
			typedef FlowAdapter<first_type, second_type, container_type> FlowAdapter;
			typedef typename internal::Value<container_type>::parameter_type parameter_container_type;
		public:
			FlowElement() : FlowAdapter() {}
			FlowElement(parameter_container_type container) { setContent(container); }
		public:
			//! @href lazy3::internal::IModifierOnBase::change
			virtual IFlow* change(parameter_container_type container) { FlowElement* newElement = new FlowElement(*this); newElement->setContent(container); return newElement; }
			//! @href lazy3::internal::IImplementation::duplicate
			virtual IImplementation* duplicate() const { return new FlowElement(*this); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
