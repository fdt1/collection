/*
 *  lazy2_internal_InstanceCallback.h
 *  collection
 *
 *  Created by Francois et Fabienne on 09/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "lazy2_internal_ValueTraits.h"
#include "lazy2_internal_InstanceInterface.h"
#include "lazy2_internal_Callback.h"



namespace lazy2 {
	
	namespace internal {
		
		template <typename InstanceTemplate>
		class InstanceCallback:
		public virtual Callback,
		public virtual InstanceInterface<typename ValueTraits<InstanceTemplate>::PrimeType>
		{
			typedef typename ValueTraits<InstanceTemplate>::PrimeType InstancePrimeType;
			typedef InstanceInterface<InstancePrimeType> InstanceInterface;
		public:
			typedef InstanceInterface Interface;
		public:
			const InstanceInterface* getInstanceInterface() const { return dynamic_cast<const InstanceInterface*> (getImplementation()); }
			// don't duplicate the implementation in Collection
			InstanceInterface* getInstanceInterface() { return const_cast<InstanceInterface*> (dynamic_cast<const InstanceInterface*> (getImplementation())); }
		public:
			virtual InstancePrimeType& getInstance() { return getInstanceInterface()->getInstance(); }
			virtual const InstancePrimeType& getInstance() const { return getInstanceInterface()->getInstance(); }
		};
		
	} // namespace internal
	
} // namespace lazy2