/*
 *  lazy3_internal_INode.h
 *  collection
 *
 *  Created by Francois et Fabienne on 11/03/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_IPair.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_IFlow.h"

namespace lazy3 {
	
	namespace internal {
		
		// TODO: entity <-> relation and node <-> graph 
		
		//--------------------------------------------------------------------------------
		//! @class INodeOnBase is a subdivision interface of INode.
		//--------------------------------------------------------------------------------
		class INodeOnBase :
		public virtual IIteratorOnBase
		{
		public:
		};
		
		//--------------------------------------------------------------------------------
		//! @class INode is the interface for an Node.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class INode :
		public virtual IContent<container_type>,
		public virtual IPair<first_type, second_type>,
		public virtual INodeOnBase,
		public virtual IModifier<container_type, INode<first_type, second_type, container_type>*>
		{
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual INode* parents() const = 0;
			//! count the remaining steps until the end.
			//! @return the distance.
			virtual INode* children() const = 0;
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
