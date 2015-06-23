/*
 *  variety_internal_SetDatumAccessorInterface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_GenericTraits.h"
#include "variety_internal_Implementation.h"

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class SetDatumAccessorInterface :
		public virtual Implementation 
		{
		public:
			typedef typename GenericTraits<ValueTemplate>::ValueType RawValueType;
		public:
			virtual void set_datum(const RawValueType& value) const = 0;
			virtual const RawValueType& get_datum() const = 0;
		};

		
	} // namespace internal
	
	
} // namespace variety