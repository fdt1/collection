/*
 *  lazy_internal_IModifier.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_IGeneric.h"
#include "lazy_internal_IIterator.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IModifier : 
		public virtual IIterator<ValueTemplate, AssociateTemplate>
		{
		public:
			virtual IGeneric& getModified() = 0;			
			virtual const IGeneric& getModified() const = 0;			
			virtual void setModified(const IGeneric& modified) = 0;			
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IModifier&> (generic);
			}
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy