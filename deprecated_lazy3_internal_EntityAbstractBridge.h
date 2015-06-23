/*
 *  lazy3_internal_EntityAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "lazy3_internal_PairAbstractBridge.h"
#include "lazy3_internal_ContentAbstractBridge.h"
#include "lazy3_internal_IEntity.h"
#include "lazy3_internal_IBridge.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_ModifierAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityAbstractBridge wraps an implementation of a Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class EntityAbstractBridge :
		public virtual IEntity<first_type, second_type, container_type>,
		public virtual PairAbstractBridge<first_type, second_type>,
		public virtual ContentAbstractBridge<container_type>,
		public virtual GenericAbstractBridge,
		public virtual ModifierAbstractBridge<container_type, IEntity<first_type, second_type, container_type>*>
		{
		public:
			typedef IEntity<first_type, second_type, container_type> IEmbeddedEntity;
		public:
			//! @return the current implementation nested in the Bridge
			const IEmbeddedEntity* getIEntity() const { return dynamic_cast<IEmbeddedEntity*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IEmbeddedEntity* getUniqueIEntity() { return dynamic_cast<IEmbeddedEntity*> (getUniqueImplementation()); } 
			//! @return the current implementation nested in the Bridge
			const IEntityOnBase* getIEntityOnBase() const { return dynamic_cast<IEntityOnBase*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IEntityOnBase* getUniqueIEntityOnBase() { return dynamic_cast<IEntityOnBase*> (getUniqueImplementation()); } 
			
		public: // IEntity
			//! @href lazy3::internal::IFlowOnBase::forward
			virtual size_t forward(size_t steps) { if (IEntityOnBase* Entity = this->getUniqueIEntityOnBase()) return Entity->forward(steps); else return 0; }
			//! @href lazy3::internal::IFlowOnBase::flush
			virtual void flush() { if (IEntityOnBase* Entity = this->getUniqueIEntityOnBase()) Entity->flush(); }	
			//! @href lazy3::internal::IFlowOnBase::distance
			virtual size_t distance() const { if (const IEntityOnBase* Entity = this->getIEntityOnBase()) return Entity->distance(); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::pop
			virtual size_t backward(size_t steps) { if (IEntityOnBase* Entity = this->getUniqueIEntityOnBase()) return Entity->backward(steps); else return 0; }
			//! @href lazy3::internal::IIteratorOnBase::flush
			virtual void rewind() { if (IEntityOnBase* Entity = this->getUniqueIEntityOnBase()) Entity->rewind(); }	
			//! @href lazy3::internal::IIteratorOnBase::remains
			virtual size_t remains() const { if (const IEntityOnBase* Entity = this->getIEntityOnBase()) return Entity->remains(); else return 0; }
			//! @href lazy3::internal::IEntity::relatives
			virtual IEntity* relatives() const { if (const IEmbeddedEntity* Entity = this->getIEntity()) return Entity->relatives(); else return NULL; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
