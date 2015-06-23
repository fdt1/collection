/*
 *  lazy3_internal_EntityBridge.h
 *  Entity
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_Generic.h"
#include "lazy3_internal_EntityAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class EntityBridge :
		public Bridge,
		public virtual EntityAbstractBridge<first_type, second_type, container_type>
		{
		public:
			EntityBridge() {}
			EntityBridge(const EntityAbstractBridge<first_type, second_type, container_type>& Entity) : Bridge(Entity) {}	
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class EntityBridge<first_type, second_type, void> :
		public Bridge,
		public virtual IEntity<first_type, second_type, void>,
		public virtual EntityAbstractBridge<first_type, second_type, void>
		{
		public:
			EntityBridge() {}
			template <typename any_container_type>
			EntityBridge(const EntityAbstractBridge<first_type, second_type, any_container_type>& Entity) : Bridge(Entity) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type>
		class EntityBridge<first_type, void, container_type> :
		public virtual Bridge,
		public virtual IEntity<first_type, void, container_type>,
		public virtual EntityAbstractBridge<first_type, void, container_type>
		{
		public:
			EntityBridge() {}
			template <typename any_second_type>
			EntityBridge(const EntityAbstractBridge<first_type, any_second_type, container_type>& Entity) : Bridge(Entity) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename second_type, typename container_type>
		class EntityBridge<void, second_type, container_type> :
		public virtual Bridge,
		public virtual IEntity<void, second_type, container_type>,
		public virtual EntityAbstractBridge<void, second_type, container_type>
		{
		public:
			EntityBridge() {}
			template <typename any_first_type>
			EntityBridge(const EntityAbstractBridge<any_first_type, second_type, container_type>& Entity) : Bridge(Entity) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class EntityBridge<first_type, void, void> :
		public virtual Bridge,
		public virtual IEntity<first_type, void, void>,
		public virtual EntityAbstractBridge<first_type, void, void>
		{
		public:
			EntityBridge() {}
			template <typename any_second_type, typename any_container_type>
			EntityBridge(const EntityAbstractBridge<first_type, any_second_type, any_container_type>& Entity) : Bridge(Entity) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class EntityBridge<void, second_type, void> :
		public virtual Bridge,
		public virtual IEntity<void, second_type, void>,
		public virtual EntityAbstractBridge<void, second_type, void>
		{
		public:
			EntityBridge() {}
			template <typename any_first_type, typename any_container_type>
			EntityBridge(const EntityAbstractBridge<any_first_type, second_type, any_container_type>& Entity) : Bridge(Entity) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<typename container_type>
		class EntityBridge<void, void, container_type> :
		public virtual Bridge,
		public virtual IEntity<void, void, container_type>,
		public virtual EntityAbstractBridge<void, void, container_type>
		{
		public:
			EntityBridge() {}
			template <typename any_first_type, typename any_second_type>
			EntityBridge(const EntityAbstractBridge<any_first_type, any_second_type, container_type>& Entity) : Bridge(Entity) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class EntityBridge wraps an implementation of a forward Entity.
		//--------------------------------------------------------------------------------
		template<>
		class EntityBridge<void, void, void> :
		public virtual Bridge,
		public virtual IEntity<void, void, void>,
		public virtual EntityAbstractBridge<void, void, void>
		{
		public:
			EntityBridge() {}
			template <typename any_first_type, typename any_second_type, typename any_container_type>
			EntityBridge(const EntityAbstractBridge<any_first_type, any_second_type, any_container_type>& Entity) : Bridge(Entity) {}	
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
