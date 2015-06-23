/*
 *  container_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "interface.h"

namespace variety {
	
	
	template <typename C>
	class container_interface : public interface {
	public:
		typedef C container_type;
		virtual const container_type& container() const = 0;
	};
	
	
} // namespace variety