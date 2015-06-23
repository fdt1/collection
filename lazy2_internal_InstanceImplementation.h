/*
 *  lazy2_internal_InstanceImplementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 06/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_Implementation.h"
#include "lazy2_internal_ValueTraits.h"


namespace lazy2 {
	
	namespace internal {
		
		template <typename InstanceTemplate>
		class InstanceImplementation :
		public Implementation,
		public virtual InstanceInterface<typename ValueTraits<InstanceTemplate>::PrimeType>
		{
			// InstanceReferenceType keeps the const if any
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::ConstRefType InstanceConstReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
		public:
			InstanceTemplate _instance;
		public:
			explicit InstanceImplementation(InstanceReferenceType instance) : _instance(instance) {}
			explicit InstanceImplementation(InstanceConstReferenceType instance) : _instance(instance) {}
			explicit InstanceImplementation() : _instance() {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new InstanceImplementation(*this); }
		public:
			// Instance interface
			virtual InstancePrimeType& getInstance() { return _instance; }
			virtual const InstancePrimeType& getInstance() const { return _instance; }
		};
		
		template <typename InstanceTemplate>
		class InstanceImplementation<InstanceTemplate&> :
		public Implementation,
		public virtual InstanceInterface<typename ValueTraits<InstanceTemplate>::PrimeType>
		{
			// InstanceReferenceType keeps the const if any
			typedef typename ValueTraits<InstanceTemplate>::ReferenceType InstanceReferenceType;
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
		public:
			InstanceTemplate& _instance;
		public:
			explicit InstanceImplementation(InstanceReferenceType instance) : _instance(instance) {}
			explicit InstanceImplementation() : _instance() {}
		public:
			// Implementation interface
			virtual Implementation* duplicate() const { return new InstanceImplementation(*this); }
		public:
			// Instance interface
			virtual InstancePrimeType& getInstance() { return (InstancePrimeType&) _instance; }
			virtual const InstancePrimeType& getInstance() const { return _instance; }
		};
		
	} // namespace internal
	
} // namespace lazy2