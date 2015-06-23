/*
 *  variety_internal_IList.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "variety_internal_ICollection.h"
#include "variety_generic_traits.h"


namespace variety {
	
	namespace internal {
		
		template <typename PrimeTemplate, typename AssociateTemplate>
		class IList : 
		public virtual internal::ICollection<PrimeTemplate, AssociateTemplate> {
		public:
			typedef ICollection<PrimeTemplate, AssociateTemplate> InheritedType;
		public:
			typedef typename GenericTraits<PrimeTemplate>::BaseType PrimeType;
			typedef typename GenericTraits<AssociateTemplate>::BaseType AssociateType;
			typedef Iterator<PrimeTemplate, AssociateTemplate> IteratorType;
		public:
			virtual IteratorType insert(const IteratorType& before_iter, const PrimeType& prime, const AssociateType& associate) = 0;
			virtual IteratorType insert(const IteratorType& before_iter, const PrimeType& prime) = 0;
			virtual IteratorType insert_first(const PrimeType& prime, const AssociateType& associate) = 0;
			virtual IteratorType insert_first(const PrimeType& prime) = 0;
			virtual IteratorType insert_last(const PrimeType& prime, const AssociateType& associate) = 0;
			virtual IteratorType insert_last(const PrimeType& prime) = 0;
			virtual void erase(IteratorType& iter) = 0;
			virtual void erase_first() = 0;
			virtual void erase_last() = 0;
	};
		
	} // namespace internal
		
	
} // namespace variety