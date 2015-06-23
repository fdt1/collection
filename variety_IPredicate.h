/*
 *  variety_IPredicate.h
 *  collection
 *
 *  Created by Francois et Fabienne on 10/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_ITransform.h"

namespace variety {
	
	template <typename InputInterfaceTemplate, typename OutputInterfaceTemplate>
	class IPredicate : ITransform<InputInterfaceTemplate, OutputInterfaceTemplate> {
	};
	
	
} // namespace variety