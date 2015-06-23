/*
 *  instance_container_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "container_interface.h"
#include "implementation.h"

namespace variety {
	
	
	template <typename C>
	class instance_container_implementation : 
		virtual public implementation, 
		virtual public container_interface<C>
	{
	public:
		typedef C container_type;	
	private:
		const container_type _container;
	public:
		virtual const container_type& container() { return _container; }
		virtual const char* name() const { return "instance_container_implementation"; }
	};
	
	
} // namespace variety