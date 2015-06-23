/*
 *  lazy3_internal_IteratorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_Bridge.h"
#include "lazy3_internal_IteratorAbstractBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class IteratorBridge :
		public Bridge,
		public virtual IteratorAbstractBridge<first_type, second_type, container_type>
		{
		public:
			IteratorBridge() {}
			IteratorBridge(const IteratorAbstractBridge<first_type, second_type, container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class IteratorBridge<first_type, second_type, void> :
		public Bridge,
		public virtual IIterator<first_type, second_type, void>,
		public virtual IteratorAbstractBridge<first_type, second_type, void>
		{
		public:
			IteratorBridge() {}
			template <typename any_container_type>
			IteratorBridge(const IteratorAbstractBridge<first_type, second_type, any_container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type>
		class IteratorBridge<first_type, void, container_type> :
		public virtual Bridge,
		public virtual IIterator<first_type, void, container_type>,
		public virtual IteratorAbstractBridge<first_type, void, container_type>
		{
		public:
			IteratorBridge() {}
			template <typename any_second_type>
			IteratorBridge(const IteratorAbstractBridge<first_type, any_second_type, container_type>& Iterator) : Bridge(Iterator) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename second_type, typename container_type>
		class IteratorBridge<void, second_type, container_type> :
		public virtual Bridge,
		public virtual IIterator<void, second_type, container_type>,
		public virtual IteratorAbstractBridge<void, second_type, container_type>
		{
		public:
			IteratorBridge() {}
			template <typename any_first_type>
			IteratorBridge(const IteratorAbstractBridge<any_first_type, second_type, container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class IteratorBridge<first_type, void, void> :
		public virtual Bridge,
		public virtual IIterator<first_type, void, void>,
		public virtual IteratorAbstractBridge<first_type, void, void>
		{
		public:
			IteratorBridge() {}
			template <typename any_second_type, typename any_container_type>
			IteratorBridge(const IteratorAbstractBridge<first_type, any_second_type, any_container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class IteratorBridge<void, second_type, void> :
		public virtual Bridge,
		public virtual IIterator<void, second_type, void>,
		public virtual IteratorAbstractBridge<void, second_type, void>
		{
		public:
			IteratorBridge() {}
			template <typename any_first_type, typename any_container_type>
			IteratorBridge(const IteratorAbstractBridge<any_first_type, second_type, any_container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename container_type>
		class IteratorBridge<void, void, container_type> :
		public virtual Bridge,
		public virtual IIterator<void, void, container_type>,
		public virtual IteratorAbstractBridge<void, void, container_type>
		{
		public:
			IteratorBridge() {}
			template <typename any_first_type, typename any_second_type>
			IteratorBridge(const IteratorAbstractBridge<any_first_type, any_second_type, container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class IteratorBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<>
		class IteratorBridge<void, void, void> :
		public virtual Bridge,
		public virtual IIterator<void, void, void>,
		public virtual IteratorAbstractBridge<void, void, void>
		{
		public:
			IteratorBridge() {}
			template <typename any_first_type, typename any_second_type, typename any_container_type>
			IteratorBridge(const IteratorAbstractBridge<any_first_type, any_second_type, any_container_type>& Iterator) : Bridge(Iterator) {}	
		};
		
		
	} // namespace internal
	
	
} // namespace lazy2
