/*
 *  mutable_container_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "container_interface.h"

namespace variety {
	
	
	template <typename C>
	class mutable_container_interface : public container_interface<C> {
	public:
		typedef C container_type;
		virtual container_type& container() = 0;
	};
	
	
} // namespace variety