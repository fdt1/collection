/*
 *  lazy3_internal_EntityWithModifierOnFirst.h
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
		//! @class EntityWithModifierOnPrime is an implementation of a Entity to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename new_first_type, typename second_type, typename container_type>
		class EntityWithModifierOnFirst : 
		public virtual IEntity<new_first_type, second_type, container_type>,
		public EntityBridge<void, second_type, container_type>
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef ModifierBridge<old_first_type, new_first_type> ModifierBridge;
			typedef ModifierAbstractBridge<old_first_type, new_first_type> ModifierAbstractBridge;
			typedef EntityBridge<void, second_type, container_type> EntityBridge;
			typedef IPairOnFirst<old_first_type> ICurrentPairOnFirst;
			typedef EntityAbstractBridge<old_first_type, second_type, container_type> OldEntityAbstractBridge;
		public:
			ModifierBridge _modifier;
		public:
			EntityWithModifierOnFirst(const OldEntityAbstractBridge& Entity, const ModifierAbstractBridge& modifier) 
			: EntityBridge(Entity), _modifier(modifier) {}
		public:
			//! @return the current implementation nested in the Bridge
			const ICurrentPairOnFirst* getICurrentPairOnFirst() const { return dynamic_cast<ICurrentPairOnFirst*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			ICurrentPairOnFirst* getUniqueICurrentPairOnFirst() { return dynamic_cast<ICurrentPairOnFirst*> (this->getUniqueImplementation()); } 
			//! @href lazy3::internal::IEntityOnFirst::getFirst
			virtual new_first_type getFirst()  { return _modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
			//! @href lazy3::internal::IEntityOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return const_cast<EntityWithModifierOnFirst*> (this)->_modifier.change(getICurrentPairOnFirst()->getConstFirst()); }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
