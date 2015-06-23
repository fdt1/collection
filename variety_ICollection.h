/*
 *  variety_ICollection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_ICollection.h"


namespace variety {
	
	template <typename PrimeTemplate, typename AssociateTemplate = PrimeTemplate>
	class ICollection : 
	public virtual internal::ICollection<PrimeTemplate, AssociateTemplate>,
	public virtual IUnknown {
	};
		
} // namespace variety