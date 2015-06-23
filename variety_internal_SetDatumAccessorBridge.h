/*
 *  variety_internal_SetDatumAccessorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 19/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_GenericTraits.h"
#include "variety_internal_SetDatumAccessorInterface.h"

namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate>
		class SetDatumAccessorBridge :
		public virtual Bridge,
		public virtual SetDatumAccessorInterface<ValueTemplate>
		{
		public:
			typedef ValueTemplate ValueType;
		public:
			typedef SetDatumAccessorInterface<ValueType> InterfaceType;
			typedef typename GenericTraits<ValueTemplate>::ValueType RawValueType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
			
		public:
			virtual void set_datum(const RawValueType& value) const { get_interface().set_datum(value); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety