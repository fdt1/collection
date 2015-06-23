/*
 *  lazy3_internal_Adapter.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IFlow.h"
#include "lazy3_internal_ContentElement.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter wraps all methods of the container to match 
		//! a given interface.
		//! Only specializations on container_type sets the behavior.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class FlowAdapter 
		{
		};

		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class FlowAdapter<first_type, void, first_type> : 
		public virtual IFlow<first_type, void, first_type>
		{
			typedef void second_type;
			typedef first_type container_type;
			typedef container_type content_type;
			typedef typename internal::Value<first_type>::template_type template_first_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
			typedef typename internal::Value<container_type>::parameter_type parameter_content_type;
			typedef typename internal::Value<second_type>::template_type template_second_type;
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef ContentElement<container_type*> IteratorBridge;
			typedef ContentElement<container_type> VectorBridge;
		public:
			VectorBridge _vectorBridge;
			IteratorBridge _iteratorBridge;
		public:
			FlowAdapter() {}
			FlowAdapter(const FlowAdapter& flow) : _vectorBridge(flow._vectorBridge), _iteratorBridge(&_vectorBridge.getContent()) { forward(flow.distance()); }
		public:
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual template_first_type getFirst() { return *(_iteratorBridge.getContent()); }
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return *(_iteratorBridge.getConstContent()); }
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual template_second_type getSecond() { return template_second_type(); }
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_second_type getConstSecond() const { return template_second_type(); }
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _vectorBridge.isValid() && _iteratorBridge.isValid() && _iteratorBridge.getConstContent() == &_vectorBridge.getContent(); }
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (steps && isValid()) { 
					++_iteratorBridge.getUniqueContent(); 
					return 1; 
				} else { 
					return 0; 
				} 
			}
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { forward(1); }
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { return this->isValid() == false; }
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getUniqueContent() { return _vectorBridge.getUniqueContent(); }
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual ref_content_type getContent() const { return _vectorBridge.getContent(); }
			//! @href lazy3::internal::IContent::refContent implementation.
			virtual const_ref_content_type getConstContent() const { return _vectorBridge.getConstContent(); }
		public:
			//! @href lazy3::internal::IContent::setContent implementation.
			virtual const_ref_content_type setContent(parameter_content_type content) {
				_vectorBridge.setContent(content); 
				_iteratorBridge.setContent(&_vectorBridge.getContent()); 
				return _vectorBridge.getConstContent();
			}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
