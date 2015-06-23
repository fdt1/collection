/*
 *  lazy3_internal_IteratorAdapter_std_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IteratorAdapter.h"
#include "lazy3_internal_FlowAdapter_std_vector.h"
#include <vector>

namespace lazy3 {
	
	namespace internal {
		
		
		//FIXME faire aussi un constAdapter et constContent ?
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapterOnStdVector factorize behavior for all vector implementation
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type, typename iterator_type>
		class IteratorAdapterOnStdVector : 
		public virtual IIterator<first_type, void, container_type>
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
			IteratorAdapterOnStdVector() {}
			IteratorAdapterOnStdVector(const IteratorAdapterOnStdVector& flow) : _vectorBridge(flow._vectorBridge), _iteratorBridge(_vectorBridge.getContent().begin()) { forward(flow.distance()); }
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
					size_t left = remains();
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
			virtual ref_content_type getUniqueContent() { return _vectorBridge.getUniqueContent(); }
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return _vectorBridge.getConstContent(); }
			//! @href lazy3::internal::IContent::setContent implementation.
			virtual const_ref_content_type setContent(parameter_content_type content) {
				_vectorBridge.setContent(content); 
				_iteratorBridge.setContent(_vectorBridge.getContent().begin()); 
				return _vectorBridge.getConstContent();
			}
		public:
			//! @href lazy3::internal::IIteratorOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (this->_vectorBridge.isValid() && this->_iteratorBridge.isValid()) { 
					size_t left = distance();
					if (left < steps) {
						this->_iteratorBridge.getUniqueContent() -= left;
						return left;
					} else {
						this->_iteratorBridge.getUniqueContent() -= steps; 
						return steps;
					}
				} else { 
					return 0; 
				} 
			}
			//! @href lazy3::internal::IIteratorOnBase::rewind implementation.
			virtual void rewind() { 
				if (this->_vectorBridge.isValid()) { 
					this->_iteratorBridge.setContent(this->_vectorBridge.getContent().begin()); 
				}
			}
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const  { 
				if (this->_vectorBridge.isValid() && this->_iteratorBridge.isValid()) { 
					return std::distance(this->_iteratorBridge.getConstContent(), this->_vectorBridge.getContent().end()); 
				} else {
					return 0;
				}
			}
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class IteratorAdapter<first_type, void, const std::vector<element_type, allocator_type>& > : 
		public IteratorAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>&, typename std::vector<element_type, allocator_type>::const_iterator> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class IteratorAdapter<first_type, void, std::vector<element_type, allocator_type>& >  : 
		public IteratorAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>&, typename std::vector<element_type, allocator_type>::iterator>
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class IteratorAdapter<first_type, void, std::vector<element_type, allocator_type> > : 
		public IteratorAdapterOnStdVector<first_type, std::vector<element_type, allocator_type>, typename std::vector<element_type, allocator_type>::iterator> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorAdapter specialization. It wraps here std::vector and its iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename element_type, typename allocator_type>
		class IteratorAdapter<first_type, void, const std::vector<element_type, allocator_type> > : 
		public IteratorAdapterOnStdVector<first_type, const std::vector<element_type, allocator_type>, typename std::vector<element_type, allocator_type>::const_iterator> 
		{};
		
	} // namespace internal
	
	
} // namespace lazy3
