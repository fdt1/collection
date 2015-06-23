/*
 *  variety_internal_IteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_InputIteratorInterface.h"


namespace variety {
	
	namespace internal {
				
		template <typename ValueTemplate>
		class IteratorInterface :
		public virtual InputIteratorInterface<ValueTemplate>,
		public virtual BasicIteratorInterface,
		public virtual ForwardIteratorInterface
		{
		public:
			static bool is_compatible(const Implementation* implementation) {
				return dynamic_cast<const InputIteratorInterface<ValueTemplate>*> (implementation) != NULL
				&& dynamic_cast<const BasicIteratorInterface*> (implementation) != NULL
				&& dynamic_cast<const ForwardIteratorInterface*> (implementation) != NULL;
			}
		};
		
		
	} // namespace internal
	
	
} // namespace variety