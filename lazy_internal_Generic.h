/*
 *  lazy_internal_Generic.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy_internal_IGeneric.h"


namespace lazy {
	
	namespace internal {
		
		// base for adapters
		class Generic : 
		public virtual IGeneric
		{
		public:
			virtual const IGeneric& getBridgeToGeneric() const = 0;
			virtual IGeneric& getBridgeToGeneric() = 0;
			virtual void setBridgeToGeneric(const IGeneric& generic) = 0;
		public:
			// --- interface of IGeneric ---
			virtual bool isValid() const { return getBridgeToGeneric().isValid(); }
		};		
				
	} // namespace internal
	
	
	
} // namespace lazy