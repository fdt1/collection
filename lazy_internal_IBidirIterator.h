/*
 *  lazy_internal_IBidirIterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 14/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once


#include "lazy_internal_IIterator.h"
#include "lazy_internal_IGeneric.h"


namespace lazy {
	
	namespace internal {
		
		template <typename ValueTemplate, typename AssociateTemplate>
		class IBidirIterator : 
		public virtual IIterator<ValueTemplate, AssociateTemplate>
		{
		public:
			virtual size_t decrementAt(size_t index) = 0;
			virtual Bridge getReverse() const = 0;
		public:
			static boolean isCompatible(const IGeneric& generic) {
				return dynamic_cast<const IBidirIterator&> (generic);
			}
		};		
		
	} // namespace internal
	
	
	
} // namespace lazy