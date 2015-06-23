/*
 *  lazy_internal_IteratorImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/05/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once


#include "lazy_internal_ValueTraits.h"
#include "lazy_internal_Implementation.h"


namespace lazy {
	
	
	namespace internal {

		template <typename InterfaceTemplate, typename IteratorTemplate>
		class IteratorImplementation : 
		public virtual InterfaceTemplate,
		public virtual Implementation
		{
		protected:
			typedef typename ValueTraits<IteratorTemplate>::PrimeType IteratorPrimeType;
		private:		
			IteratorPrimeType _iterator;
		public:
			IteratorImplementation(const IteratorPrimeType& iter) : _iterator(iter)  {}
		public:
			// Implementation
			virtual IteratorImplementation* duplicate() const { return new IteratorImplementation(*this); }
		public:
			// --- interface of Generic ---
			virtual const IGeneric& getBridgeToGeneric() const = 0;
			virtual IGeneric& getBridgeToGeneric() = 0;
			virtual void setBridgeToGeneric(const IGeneric& generic) = 0;
		};	
		
	} // namespace internal
	
	
	
} // namespace lazy