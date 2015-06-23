/*
 *  variety_internal_DatumAccessorBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 20/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "variety_internal_InputAccessorBridge.h"
#include "variety_internal_SetDatumAccessorBridge.h"
#include "variety_internal_InputIteratorBridge.h"
#include "variety_internal_DatumAccessorInterface.h"


namespace variety {
	
	namespace internal {
		
		template <typename ValueTemplate, typename PrevValueTemplate, typename DatumTemplate>
		class DatumAccessorBridge :
		public virtual InputAccessorBridge<ValueTemplate, PrevValueTemplate>,
		public virtual SetDatumAccessorBridge<typename GenericTraits<DatumTemplate>::ValueType>,
		public virtual InputIteratorBridge<typename GenericTraits<DatumTemplate>::ValueType>,
		public virtual Bridge
		{
		public:
			typedef DatumAccessorInterface<ValueTemplate, PrevValueTemplate, DatumTemplate> InterfaceType;
		public:
			const InterfaceType& get_interface() const { return dynamic_cast<const InterfaceType&> (*get_implementation()); }
			InterfaceType& get_interface() { return dynamic_cast<InterfaceType&> (*get_implementation()); }
		};
		
		
	} // namespace internal
	
	
} // namespace variety