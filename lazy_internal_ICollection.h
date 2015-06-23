/*
 *  lazy_internal_ICollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy_internal_IIterator.h"
#include "lazy_internal_Bridge.h"
#include "lazy_internal_IGeneric.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class ICollection :
		public virtual IIterator<ValueTemplate, AssociateTemplate>
		{
		public:
			virtual Bridge getBegin() const = 0;			
		public:
			static bool isCompatible(const IGeneric& generic) {
				return dynamic_cast<const ICollection&> (generic);
			}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy