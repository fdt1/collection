/*
 *  iterator_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_forward_interface.h"
#include "variety_input_interface.h"
#include "variety_iterator.h"


namespace variety {
	
	
	template <typename I>
	class iterator_interface : virtual public internal_forward_interface<I>, virtual input_iterator<I> {
	public:
		typedef I iterator_type;
	};
	
	
} // namespace variety