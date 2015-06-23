/*
 *  lazy3_internal_FlowBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "lazy3_internal_Bridge.h"
#include "lazy3_internal_FlowAbstractBridge.h"

namespace lazy3 {
		
	namespace internal {
	
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class FlowBridge :
		public Bridge,
		public virtual FlowAbstractBridge<first_type, second_type, container_type>
		{
		public:
			FlowBridge() {}
			FlowBridge(const FlowAbstractBridge<first_type, second_type, container_type>& flow) : Bridge(flow) {}	
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type>
		class FlowBridge<first_type, second_type, void> :
		public Bridge,
		public virtual IFlow<first_type, second_type, void>,
		public virtual FlowAbstractBridge<first_type, second_type, void>
		{
		public:
			FlowBridge() {}
			template <typename any_container_type>
			FlowBridge(const FlowAbstractBridge<first_type, second_type, any_container_type>& flow) : Bridge(flow) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename container_type>
		class FlowBridge<first_type, void, container_type> :
		public virtual Bridge,
		public virtual IFlow<first_type, void, container_type>,
		public virtual FlowAbstractBridge<first_type, void, container_type>
		{
		public:
			FlowBridge() {}
			template <typename any_second_type>
			FlowBridge(const FlowAbstractBridge<first_type, any_second_type, container_type>& flow) : Bridge(flow) {}
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename second_type, typename container_type>
		class FlowBridge<void, second_type, container_type> :
		public virtual Bridge,
		public virtual IFlow<void, second_type, container_type>,
		public virtual FlowAbstractBridge<void, second_type, container_type>
		{
		public:
			FlowBridge() {}
			template <typename any_first_type>
			FlowBridge(const FlowAbstractBridge<any_first_type, second_type, container_type>& flow) : Bridge(flow) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename first_type>
		class FlowBridge<first_type, void, void> :
		public virtual Bridge,
		public virtual IFlow<first_type, void, void>,
		public virtual FlowAbstractBridge<first_type, void, void>
		{
		public:
			FlowBridge() {}
			template <typename any_second_type, typename any_container_type>
			FlowBridge(const FlowAbstractBridge<first_type, any_second_type, any_container_type>& flow) : Bridge(flow) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename second_type>
		class FlowBridge<void, second_type, void> :
		public virtual Bridge,
		public virtual IFlow<void, second_type, void>,
		public virtual FlowAbstractBridge<void, second_type, void>
		{
		public:
			FlowBridge() {}
			template <typename any_first_type, typename any_container_type>
			FlowBridge(const FlowAbstractBridge<any_first_type, second_type, any_container_type>& flow) : Bridge(flow) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<typename container_type>
		class FlowBridge<void, void, container_type> :
		public virtual Bridge,
		public virtual IFlow<void, void, container_type>,
		public virtual FlowAbstractBridge<void, void, container_type>
		{
		public:
			FlowBridge() {}
			template <typename any_first_type, typename any_second_type>
			FlowBridge(const FlowAbstractBridge<any_first_type, any_second_type, container_type>& flow) : Bridge(flow) {}	
		};
		
		//--------------------------------------------------------------------------------
		//! @class FlowBridge wraps an implementation of a forward iterator.
		//--------------------------------------------------------------------------------
		template<>
		class FlowBridge<void, void, void> :
		public virtual Bridge,
		public virtual IFlow<void, void, void>,
		public virtual FlowAbstractBridge<void, void, void>
		{
		public:
			FlowBridge() {}
			template <typename any_first_type, typename any_second_type, typename any_container_type>
			FlowBridge(const FlowAbstractBridge<any_first_type, any_second_type, any_container_type>& flow) : Bridge(flow) {}	
		};

		
	} // namespace internal
	
	
} // namespace lazy2
