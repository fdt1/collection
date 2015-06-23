/*
 *  lazy_internal_IBidirCollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 15/06/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "lazy_internal_IBidirIterator.h"
#include "lazy_internal_ICollection.h"
#include "lazy_internal_IGeneric.h"


namespace lazy {
	
	namespace internal {
		
		template<typename ValueTemplate, typename AssociateTemplate>
		class IBidirCollection :
		public virtual IBidirIterator<ValueTemplate, AssociateTemplate>,
		public virtual ICollection<ValueTemplate, AssociateTemplate>
		{
		protected:
			typedef typename ICollection<ValueTemplate, AssociateTemplate> ICollection;
			typedef typename IBidirIterator<ValueTemplate, AssociateTemplate> IBidirIterator;
		public:
		public:
			static boolean isCompatible(const IGeneric& generic) {
				return dynamic_cast<const ICollection&> (generic)
				    && dynamic_cast<const IBidirIterator&> (generic);
			}
		};
		
		
	} // namespace internal
	
	
} // namespace lazy