/*
 *  variety_transform.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_IGeneric.h"

namespace variety {
	
	template <typename InputInterfaceTemplate, typename OutputInterfaceTemplate>
	class ITransform : 
	public virtual OutputInterfaceTemplate {
		OutputInterfaceTemplate operator>> (const InputInterfaceTemplate& inter) const { return 
	};
	
	
} // namespace variety