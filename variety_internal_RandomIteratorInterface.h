/*
 *  variety_internal_RandomIteratorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 27/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_BasicIteratorInterface.h"
#include "variety_internal_ForwardIteratorInterface.h"
#include "variety_internal_BackwardIteratorInterface.h"
#include "variety_internal_PtrDiffIteratorInterface.h"
#include "variety_internal_InputIteratorInterface.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class RandomIteratorInterface :
		public virtual InputIteratorInterface<ValueTemplate>,
		public virtual BasicIteratorInterface,
		public virtual ForwardIteratorInterface,
		public virtual BackwardIteratorInterface,
		public virtual PtrDiffIteratorInterface				
		{
		public:
			static bool is_compatible(const Implementation* implementation) {
				return dynamic_cast<const InputIteratorInterface<ValueTemplate>*> (implementation) != NULL
				&& dynamic_cast<const BasicIteratorInterface*> (implementation) != NULL
				&& dynamic_cast<const ForwardIteratorInterface*> (implementation) != NULL
				&& dynamic_cast<const BackwardIteratorInterface*> (implementation) != NULL
				&& dynamic_cast<const PtrDiffIteratorInterface*> (implementation) != NULL;
			}
		
		};
		
	} // namespace internal
	
	
} // namespace variety