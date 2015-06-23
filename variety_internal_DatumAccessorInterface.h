/*
 *  variety_internal_DatumAccessorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_InputAccessorInterface.h"
#include "variety_internal_SetDatumAccessorInterface.h"
#include "variety_internal_InputIteratorInterface.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate>
		class DatumAccessorInterface :
		public virtual InputAccessorInterface<ValueTemplate, PrevValueTemplate>,
		public virtual SetDatumAccessorInterface<typename GenericTraits<DatumTemplate>::ValueType>,
		public virtual InputIteratorInterface<typename GenericTraits<DatumTemplate>::ValueType>
		{
		public:
			static bool is_compatible(const Implementation* implementation) {
				return dynamic_cast<const InputAccessorInterface<ValueTemplate, PrevValueTemplate>*> (implementation) != NULL
				&& dynamic_cast<const SetDatumAccessorInterface<typename GenericTraits<DatumTemplate>::ValueType>*> (implementation) != NULL
				&& dynamic_cast<const InputIteratorInterface<typename GenericTraits<DatumTemplate>::ValueType>*> (implementation) != NULL;
			}
			
		};
		
	} // namespace internal
	
	
} // namespace variety