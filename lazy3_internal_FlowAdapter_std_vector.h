/*
 *  lazy3_internal_Adapter_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_FlowAdapter.h"
#include "lazy3_internal_ContentElement.h"
#include <vector>

namespace lazy3 {
	
	namespace internal {
		
		
		//FIXME faire aussi un constAdapter et constContent ?
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type, typename iterator_type>
		class FlowAdapterOnStdVector : 
		public virtual IFlow<first_type, void, container_type>
		{
			typedef container_type content_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
			typedef ContentElement<iterator_type> IteratorBridge;
			typedef ContentElement<container_type> VectorBridge;
		public:
			VectorBridge _vectorBridge;
			IteratorBridge _iteratorBridge;
		public:
			FlowAdapterOnStdVector() {}
			FlowAdapterOnStdVector(const FlowAdapterOnStdVector& flow) : _vectorBridge(flow._vectorBridge), _iteratorBridge(_vectorBridge.getContent().begin()) { forward(flow.distance()); }
		public:
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return *(_iteratorBridge.getContent()); }
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return *(_iteratorBridge.getConstContent()); }
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _vectorBridge.isValid() && _iteratorBridge.isValid() && _iteratorBridge.getConstContent() != _vectorBridge.getConstContent().end(); }
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (_vectorBridge.isValid() && _iteratorBridge.isValid()) { 
					size_t left = std::distance(_iteratorBridge.getConstContent(), _vectorBridge.getContent().end());
					if (left < steps) {
						_iteratorBridge.getUniqueContent() += left;
						return left;
					} else {
						_iteratorBridge.getUniqueContent() += steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { 
				if (_vectorBridge.isValid()) { 
					_iteratorBridge.setContent(_vectorBridge.getContent().end()); 
				}
			}
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (this->_vectorBridge.isValid() && this->_iteratorBridge.isValid()) { 
					return std::distance(this->_vectorBridge.getContent().begin(), this->_iteratorBridge.getConstContent()); 
				} else {
					return 0;
				}
			}
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() const { return _vectorBridge.getContent(); }
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getUniqueContent() { return _vectorBridge.getContent(); }
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return _vectorBridge.getConstContent(); }
			//! @href lazy3::internal::IContent::setContent implementation.
			virtual const_ref_content_type setContent(parameter_content_type content) {
				_vectorBridge.setContent(content); 
				_iteratorBridge.setContent(_vectorBridge.getContent().begin()); 
				return _vectorBridge.getConstContent();
			}
		};

		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class FlowAdapter<first_type, void, const std::vector<element_type, allocator_type>& > : 
		public FlowAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>&, typename std::vector<element_type, allocator_type>::const_iterator> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class FlowAdapter<first_type, void, std::vector<element_type, allocator_type>& >  : 
		public FlowAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>&, typename std::vector<element_type, allocator_type>::iterator>
		{};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class FlowAdapter<first_type, void, std::vector<element_type, allocator_type> > : 
		public FlowAdapterOnStdVector<first_type, std::vector<element_type, allocator_type>, typename std::vector<element_type, allocator_type>::iterator> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class FlowAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class FlowAdapter<first_type, void, const std::vector<element_type, allocator_type> > : 
		public FlowAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>, typename std::vector<element_type, allocator_type>::const_iterator> 
		{};
		
	} // namespace internal
	
	
} // namespace lazy3
