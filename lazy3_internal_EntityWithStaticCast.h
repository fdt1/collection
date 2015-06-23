/*
 *  lazy3_internal_EntityWithStaticCast.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_EntityAbstractBridge.h"
#include "lazy3_internal_EntityBridge.h"
#include "lazy3_internal_IEntity.h"

namespace lazy3 {
	
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnFirst is an implementation of a Entity to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class EntityWithStaticCastOnFirst : 
		public virtual IEntity<new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_first_type>::const_type const_new_first_type;
			typedef IEntity<old_first_type, old_second_type, old_content_type> IOldEntity;
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldEntity* getIOldEntity() const = 0;
			//! @return the current implementation nested in the Bridge
			virtual IOldEntity* getUniqueIOldEntity() = 0; 
			//! @href lazy3::internal::IEntityOnFirst::getFirst
			virtual new_first_type getFirst()  { return static_cast<new_first_type> (getUniqueIOldEntity()->getFirst()); }
			//! @href lazy3::internal::IEntityOnFirst::getConstFirst
			virtual const_new_first_type getConstFirst() const { return static_cast<const_new_first_type> (getIOldEntity()->getConstFirst()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnFirst is a dummy specialization 
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_second_type, typename new_content_type>
		class EntityWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, void, new_second_type, new_content_type> : 
		public virtual IEntity<void, new_second_type, new_content_type>,
		public EntityBridge<old_first_type, old_second_type, old_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnSecond is an implementation of a Entity to overwrite 
		//! the second type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class EntityWithStaticCastOnSecond : 
		public EntityWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_second_type>::const_type const_new_second_type;
		public:
			//! @href lazy3::internal::IEntityOnFirst::getSecond
			virtual new_second_type getSecond()  { return static_cast<new_second_type> (this->getUniqueIOldEntity()->getSecond()); }
			//! @href lazy3::internal::IEntityOnFirst::getConstSecond
			virtual const_new_second_type getConstSecond() const { return static_cast<const_new_second_type> (this->getIOldEntity()->getConstSecond()); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnSecond is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_content_type>
		class EntityWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type> : 
		public EntityWithStaticCastOnFirst<old_first_type, old_second_type, old_content_type, new_first_type, void, new_content_type>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnContent is an implementation of a Entity to overwrite 
		//! the content type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class EntityWithStaticCastOnContent : 
		public EntityWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>
		{
			typedef typename internal::Value<new_content_type>::ref_type ref_new_content_type;
			typedef typename internal::Value<new_content_type>::const_ref_type const_ref_new_content_type;
			typedef typename internal::Value<new_content_type>::parameter_type parameter_new_content_type;
			typedef typename internal::Value<old_content_type>::parameter_type parameter_content_type;
		public:
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getContent() const { return static_cast<ref_new_content_type> (this->getIOldEntity()->getContent()); }
			//! @href lazy3::internal::IContent::getContent
			virtual ref_new_content_type getUniqueContent()  { return static_cast<ref_new_content_type> (this->getUniqueIOldEntity()->getUniqueContent()); }
			//! @href lazy3::internal::IContent::getConstContent
			virtual const_ref_new_content_type getConstContent() const { return static_cast<const_ref_new_content_type> (this->getIOldEntity()->getConstContent()); }
			//! @href lazy3::internal::IContent::setContent
			virtual const_ref_new_content_type setContent(parameter_new_content_type content) { return static_cast<const_ref_new_content_type> (this->getUniqueIOldEntity()->setContent(static_cast<parameter_content_type> (content))); }
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCastOnContent is a dummy specialization
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type>
		class EntityWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void> : 
		public EntityWithStaticCastOnSecond<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, void>
		{
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityWithStaticCast is an implementation of a Entity to overwrite 
		//! the first type accessor.
		//--------------------------------------------------------------------------------
		template<typename old_first_type, typename old_second_type, typename old_content_type, typename new_first_type, typename new_second_type, typename new_content_type>
		class EntityWithStaticCast : 
		public EntityWithStaticCastOnContent<old_first_type, old_second_type, old_content_type, new_first_type, new_second_type, new_content_type>,
		public EntityBridge<void, void, void>
		{
			typedef EntityBridge<void, void, void> EntityBridge;
			typedef IEntity<old_first_type, old_second_type, old_content_type> IOldEntity;
			typedef EntityAbstractBridge<old_first_type, old_second_type, old_content_type> OldEntityAbstractBridge;
		public:
			EntityWithStaticCast(const OldEntityAbstractBridge& Entity) 
			: EntityBridge(Entity) {}
		public:
			//! @return the current implementation nested in the Bridge
			virtual const IOldEntity* getIOldEntity() const { return dynamic_cast<IOldEntity*> (this->getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			virtual IOldEntity* getUniqueIOldEntity() { return dynamic_cast<IOldEntity*> (this->getUniqueImplementation()); } 
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
