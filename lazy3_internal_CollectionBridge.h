/*
 *  lazy3_internal_CollectionBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_Generic.h"
#include "lazy3_internal_CollectionAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class CollectionBridge :
		public Bridge,
		public virtual CollectionAbstractBridge<first_type, second_type, container_type>
		{
		public:
			CollectionBridge() {}
			CollectionBridge(const CollectionAbstractBridge<first_type, second_type, container_type>& Collection) : Bridge(Collection) {}	
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class CollectionBridge<first_type, second_type, void> :
		public Bridge,
		public virtual ICollection<first_type, second_type, void>,
		public virtual CollectionAbstractBridge<first_type, second_type, void>
		{
		public:
			CollectionBridge() {}
			template <typename any_container_type>
			CollectionBridge(const CollectionAbstractBridge<first_type, second_type, any_container_type>& Collection) : Bridge(Collection) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type>
		class CollectionBridge<first_type, void, container_type> :
		public virtual Bridge,
		public virtual ICollection<first_type, void, container_type>,
		public virtual CollectionAbstractBridge<first_type, void, container_type>
		{
		public:
			CollectionBridge() {}
			template <typename any_second_type>
			CollectionBridge(const CollectionAbstractBridge<first_type, any_second_type, container_type>& Collection) : Bridge(Collection) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename second_type, typename container_type>
		class CollectionBridge<void, second_type, container_type> :
		public virtual Bridge,
		public virtual ICollection<void, second_type, container_type>,
		public virtual CollectionAbstractBridge<void, second_type, container_type>
		{
		public:
			CollectionBridge() {}
			template <typename any_first_type>
			CollectionBridge(const CollectionAbstractBridge<any_first_type, second_type, container_type>& Collection) : Bridge(Collection) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class CollectionBridge<first_type, void, void> :
		public virtual Bridge,
		public virtual ICollection<first_type, void, void>,
		public virtual CollectionAbstractBridge<first_type, void, void>
		{
		public:
			CollectionBridge() {}
			template <typename any_second_type, typename any_container_type>
			CollectionBridge(const CollectionAbstractBridge<first_type, any_second_type, any_container_type>& Collection) : Bridge(Collection) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class CollectionBridge<void, second_type, void> :
		public virtual Bridge,
		public virtual ICollection<void, second_type, void>,
		public virtual CollectionAbstractBridge<void, second_type, void>
		{
		public:
			CollectionBridge() {}
			template <typename any_first_type, typename any_container_type>
			CollectionBridge(const CollectionAbstractBridge<any_first_type, second_type, any_container_type>& Collection) : Bridge(Collection) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<typename container_type>
		class CollectionBridge<void, void, container_type> :
		public virtual Bridge,
		public virtual ICollection<void, void, container_type>,
		public virtual CollectionAbstractBridge<void, void, container_type>
		{
		public:
			CollectionBridge() {}
			template <typename any_first_type, typename any_second_type>
			CollectionBridge(const CollectionAbstractBridge<any_first_type, any_second_type, container_type>& Collection) : Bridge(Collection) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class CollectionBridge wraps an implementation of a forward Collection.
		//--------------------------------------------------------------------------------
		template<>
		class CollectionBridge<void, void, void> :
		public virtual Bridge,
		public virtual ICollection<void, void, void>,
		public virtual CollectionAbstractBridge<void, void, void>
		{
		public:
			CollectionBridge() {}
			template <typename any_first_type, typename any_second_type, typename any_container_type>
			CollectionBridge(const CollectionAbstractBridge<any_first_type, any_second_type, any_container_type>& Collection) : Bridge(Collection) {}	
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
