/*
 *  lazy3_internal_EntityAdapter_std_map_vector.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_EntityAdapter.h"
#include <map>

namespace lazy3 {
	
	namespace internal {
		
		
		//FIXME faire aussi un constAdapter et constContent ?
		
		//--------------------------------------------------------------------------------
		//! @class EntityAdapterOnStdMapVector factorize behavior for all map implementation
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type, typename Entity_type>
		class EntityAdapterOnStdMapVector : 
		public virtual IEntity<first_type, void, container_type>
		{
			typedef container_type content_type;
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef typename internal::Value<content_type>::ref_type ref_content_type;
			typedef typename internal::Value<content_type>::const_ref_type const_ref_content_type;
			typedef typename internal::Value<content_type>::parameter_type parameter_content_type;
			typedef ContentElement<Entity_type> IteratorBridge;
			typedef ContentElement<container_type> MapBridge;
		public:
			MapBridge _mapBridge;
			IteratorBridge _iteratorBridge;
		public:
			//! @href lazy3::internal::IPairOnFirst::getFirst implementation.
			virtual first_type getFirst() { return (_iteratorBridge.getConstContent())->first; }
			//! @href lazy3::internal::IPairOnFirst::getConstFirst implementation.
			virtual const_first_type getConstFirst() const { return (_iteratorBridge.getConstContent())->first; }
			//! @href lazy3::internal::IGeneric::isValid implementation.
			virtual bool isValid() const { return _mapBridge.isValid() && _iteratorBridge.isValid() && _iteratorBridge.getConstContent() != _mapBridge.getConstContent().end(); }
			//! @href lazy3::internal::IFlowOnBase::forward implementation.
			virtual size_t forward(size_t steps) { 
				if (_mapBridge.isValid() && _iteratorBridge.isValid()) { 
						size_t i = 0;
						for (; i != steps; ++i) {
							if (_iteratorBridge.getContent() == getContent().end()) break;
							++_iteratorBridge.getContent(); 
						}
						return i;
					}
				} else { 
					return 0; 
				} 
			}
			//! @href lazy3::internal::IFlowOnBase::flush implementation.
			virtual void flush() { 
				if (_mapBridge.isValid()) { 
					_iteratorBridge.setContent(getContent().end()); 
				}
			}
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const  { 
				if (this->_mapBridge.isValid() && this->_iteratorBridge.isValid()) { 
					return std::distance(this->_mapBridge.getConstContent().begin(), this->_iteratorBridge.getConstContent()); 
				} else {
					return 0;
				}
			}
			//! @href lazy3::internal::IContent::getContent implementation.
			virtual ref_content_type getContent() { return _mapBridge.getContent(); }
			//! @href lazy3::internal::IContent::getConstContent implementation.
			virtual const_ref_content_type getConstContent() const { return _mapBridge.getConstContent(); }
			//! @href lazy3::internal::IContent::setContent implementation.
			virtual const_ref_content_type setContent(parameter_content_type content) {
				_mapBridge.setContent(content); 
				_iteratorBridge.setContent(getContent().begin()); 
				return _mapBridge.getConstContent();
			}
		public:
			//! @href lazy3::internal::IEntityOnBase::backward implementation.
			virtual size_t backward(size_t steps) { 
				if (this->_mapBridge.isValid() && this->_iteratorBridge.isValid()) { 
					size_t i = 0;
					for (; i != steps; ++i) {
						if (_iteratorBridge.getContent() == getContent().begin()) break;
						--_iteratorBridge.getContent(); 
					}
					return i;
				} else { 
					return 0; 
				} 
			}
			//! @href lazy3::internal::IEntityOnBase::rewind implementation.
			virtual void rewind() { 
				if (this->_mapBridge.isValid()) { 
					this->_iteratorBridge.setContent(this->getContent().begin()); 
				}
			}
			//! @href lazy3::internal::IEntityOnBase::remains
			virtual size_t remains() const  { 
				if (this->_mapBridge.isValid() && this->_iteratorBridge.isValid()) { 
					return std::distance(this->_iteratorBridge.getConstContent(), this->_mapBridge.getConstContent().end()); 
				} else {
					return 0;
				}
			}
	public:
			//! @href lazy3::internal::IEntity::relatives
			virtual IEntity* relatives() const { if (const IEmbeddedEntity* Entity = this->getIEntity()) return Entity->relatives(); else return NULL; }
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityAdapter specialization. It wraps here std::map and its Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename map_allocator_type, typename vector_allocator_type>
		class EntityAdapter<first_type, void, const std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>& > : 
		public EntityAdapterOnStdMapVector<first_type, const std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>&, typename std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>::const_Entity> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class EntityAdapter specialization. It wraps here std::map and its Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename map_allocator_type, typename vector_allocator_type>
		class EntityAdapter<first_type, void, std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>& >  : 
		public EntityAdapterOnStdMapVector<first_type, const std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>&, typename std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>::Entity>
		{};
		
		//--------------------------------------------------------------------------------
		//! @class EntityAdapter specialization. It wraps here std::map and its Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename map_allocator_type, typename vector_allocator_type>
		class EntityAdapter<first_type, void, std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type> > : 
		public EntityAdapterOnStdMapVector<first_type, std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>, typename std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>::Entity> 
		{};
		
		//--------------------------------------------------------------------------------
		//! @class EntityAdapter specialization. It wraps here std::map and its Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename map_allocator_type, typename vector_allocator_type>
		class EntityAdapter<first_type, void, const std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type> > : 
		public EntityAdapterOnStdMapVector<first_type, const std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>, typename std::map<first_type, std::vector<first_type, vector_allocator_type>, map_allocator_type>::const_Entity> 
		{};
		
	} // namespace internal
	
	
} // namespace lazy3
