/*
 *  lazy3_internal_ICollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 16/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IContent.h"
#include "lazy3_internal_IPair.h"
#include "lazy3_internal_Value.h"
#include "lazy3_internal_IModifier.h"
#include "lazy3_internal_IIterator.h"

namespace lazy3 {
	
	namespace internal {
		

		//--------------------------------------------------------------------------------
		//! @class ICollectionOnBase is a subdivision interface of ICollection.
		//--------------------------------------------------------------------------------
		class ICollectionOnBase :
		public virtual IIteratorOnBase
		{
		};
		
		
		//--------------------------------------------------------------------------------
		//! @class ICollection is the interface for a collection.
		//--------------------------------------------------------------------------------
		template<typename first_type, typename second_type, typename container_type>
		class ICollection :
		public virtual IContent<container_type>,
		public virtual IPair<first_type, second_type>,
		public virtual ICollectionOnBase,
		public virtual IModifier<container_type, ICollection<first_type, second_type, container_type>*>
		{
		};
		
		
		
	} // namespace internal
	
	
} // namespace lazy2
