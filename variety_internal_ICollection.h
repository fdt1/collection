/*
 *  variety_internal_ICollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_IUnknown.h"

namespace variety {
	
	namespace internal {

		template <typename PrimeTemplate, typename AssociateTemplate = PrimeTemplate>
		class ICollection : public virtual IUnknown {
		};
		
		
	} // namespace internal
	
	
} // namespace variety