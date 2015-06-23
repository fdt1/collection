/*
 *  lazy3_internal_EntityWithFilterOnFirst.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_EntityAbstractBridge.h"
#include "lazy3_internal_EntityBridge.h"
#include "lazy3_internal_ModifierBridge.h"
#include "lazy3_internal_IEntity.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithFilterOnFirst is an implementation of IEntity to filter 
		//! first typed values.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class EntityWithFilterOnFirstOnBase : 
		public EntityBridge<first_type, second_type, container_type>
		{
		public:
			typedef typename internal::Value<first_type>::const_type const_first_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef EntityBridge<first_type, second_type, container_type> EntityBridge;
			typedef EntityAbstractBridge<first_type, second_type, container_type> EntityAbstractBridge;
			typedef IEntity<first_type, second_type, container_type> IEntity;
		public:
			ModifierBridge _modifier;
			size_t _distance;
		public:
			EntityWithFilterOnFirstOnBase(const EntityAbstractBridge& Entity, const ModifierAbstractBridge& modifier) 
			: EntityBridge(Entity), _modifier(modifier), _distance(Entity.distance()) {}
		public:
			//! @href lazy3::internal::IEntityOnBase::forward
			virtual size_t forward(size_t steps)  { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getUniqueIEntity(); 
				size_t count = 0;
				while (steps != count && EntityBase->isValid()) {
					if (_modifier.change(EntityBase->getConstFirst())) ++count; 
					EntityBase->forward(1);
				} 
				_distance += count;
				return count;
			}
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { 
				/* search the first element that match the predicate */
				IEntity* EntityBase = const_cast<EntityWithFilterOnFirstOnBase*> (this)->getUniqueIEntity(); 
				while (EntityBase->isValid()) {
					if (const_cast<EntityWithFilterOnFirstOnBase*> (this)->_modifier.change(EntityBase->getConstFirst())) return true;
					EntityBase->forward(1); 
				} 
				return false;
			}
			//! @href lazy3::internal::IPairOnFirst::getFirst
			virtual first_type getFirst() { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getUniqueIEntity(); 
				while (EntityBase->isValid()) {
					if (const_cast<EntityWithFilterOnFirstOnBase*> (this)->_modifier.change(EntityBase->getConstFirst())) break;
					EntityBase->forward(1); 
				} 
				return EntityBase->getFirst();
			}
			//! @href lazy3::internal::IPairOnFirst::getConstFirst
			virtual const_first_type getConstFirst() const { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = const_cast<EntityWithFilterOnFirstOnBase*> (this)->getUniqueIEntity(); 
				while (EntityBase->isValid()) {
					if (const_cast<EntityWithFilterOnFirstOnBase*> (this)->_modifier.change(EntityBase->getConstFirst())) break;
					EntityBase->forward(1); 
				} 
				return EntityBase->getConstFirst();
			}
			
			//! @href lazy3::internal::IEntityOnBase::distance
			virtual size_t distance() const { return _distance; }
			//! @href lazy3::internal::IEntityOnBase::backward
			virtual size_t backward(size_t steps)  { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getUniqueIEntity(); 
				size_t count = 0;
				while (steps != count && EntityBase->backward(1)) {
					if (_modifier.change(EntityBase->getConstFirst())) ++count; 
				} 
				this->_distance -= count;
				return count;
			}
			//! @href lazy3::internal::IEntityOnBase::remains
			virtual size_t remains() const { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getIEntity(); 
				size_t count = 0;
				size_t steps = 0;
				while (EntityBase->isValid()) {
					++steps;
					if (_modifier.change(EntityBase->getConstFirst())) ++count; 
					EntityBase->forward(1);
				} 
				// rewind to the previous point
				EntityBase->backward(steps);
				return count;
			}
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithFilterOnFirst is an implementation of IEntity to filter 
		//! first typed values.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename second_type, typename container_type>
		class EntityWithFilterOnFirst :
		public EntityWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type>
		{
			typedef typename internal::Value<second_type>::const_type const_second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef EntityBridge<first_type, second_type, container_type> EntityBridge;
			typedef EntityAbstractBridge<first_type, second_type, container_type> EntityAbstractBridge;
			typedef EntityWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> EntityWithFilterOnFirstOnBase;
			typedef IEntity<first_type, second_type, container_type> IEntity;
		public:
			EntityWithFilterOnFirst(const EntityAbstractBridge& Entity, const ModifierAbstractBridge& modifier) 
			: EntityWithFilterOnFirstOnBase(Entity, modifier) {}
		public:
			//! @href lazy3::internal::IPairOnSecond::getSecond
			virtual second_type getSecond(size_t steps) { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getUniqueIEntity(); 
				while (EntityBase->isValid()) {
					if (const_cast<EntityWithFilterOnFirstOnBase*> (this)->_modifier.change(EntityBase->getConstFirst())) break;
					EntityBase->forward(1); 
				} 
				return EntityBase->getSecond();
			}
			//! @href lazy3::internal::IPairOnSecond::getConstSecond
			virtual const_second_type getConstSecond() const  { 
				/* search the next element that match the predicate */
				IEntity* EntityBase = this->getUniqueIEntity(); 
				while (EntityBase->isValid()) {
					if (const_cast<EntityWithFilterOnFirstOnBase*> (this)->_modifier.change(EntityBase->getConstFirst())) break;
					EntityBase->forward(1); 
				} 
				return EntityBase->getConstSecond();
			}
			
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithFilterOnFirst<void> dummy specialization interface
		//--------------------------------------------------------------------------------
		template<typename first_type, typename test_type, typename container_type>
		class EntityWithFilterOnFirst<first_type, test_type, void, container_type> :
		public EntityWithFilterOnFirstOnBase<first_type, test_type, void, container_type>
		{
			typedef void second_type;
			typedef ModifierBridge<first_type, test_type> ModifierBridge;
			typedef ModifierAbstractBridge<first_type, test_type> ModifierAbstractBridge;
			typedef EntityBridge<first_type, second_type, container_type> EntityBridge;
			typedef EntityAbstractBridge<first_type, second_type, container_type> EntityAbstractBridge;
			typedef EntityWithFilterOnFirstOnBase<first_type, test_type, second_type, container_type> EntityWithFilterOnFirstOnBase;
		public:
			EntityWithFilterOnFirst(const EntityAbstractBridge& Entity, const ModifierAbstractBridge& modifier) 
			: EntityWithFilterOnFirstOnBase(Entity, modifier) {}
		};
		
		
		
		
		
	} // namespace internal
	
	
} // namespace lazy3
