/*
 *  lazy3_internal_GenericAbstractBridge.h
 *  collection
 *
 *  Created by Francois et Fabienne on 23/09/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy3_internal_IGeneric.h"
#include "lazy3_internal_IBridge.h"

namespace lazy3 {
	
	namespace internal {
		
		//--------------------------------------------------------------------------------
		//! @class GenericAbstractBridge base for all lazy objects.
		//--------------------------------------------------------------------------------
		class GenericAbstractBridge :
		public virtual IGeneric, 
		public virtual IBridge
		{
		public:
			//! @return the current implementation nested in the Bridge
			const IGeneric* getIGeneric() const { return dynamic_cast<IGeneric*> (getImplementation()); } 
			//! @return the current implementation nested in the Bridge
			IGeneric* getUniqueIGeneric() { return dynamic_cast<IGeneric*> (getUniqueImplementation()); } 
			
		public: // IGeneric
			//! @href lazy3::internal::IGeneric::isValid
			virtual bool isValid() const { const IGeneric* generic = getIGeneric(); return generic && generic->isValid(); }
			
		public: // IImplementation
			//! @return duplicate of the nested implementation
			virtual IImplementation* duplicate() const { return duplicateImplementation(); }
			
		public:
			template <typename internal_type, typename user_type>
			static internal_type staticCast(user_type& value) { return value; }
		};
		
		
	} // namespace internal
	
	
} // namespace lazy3
