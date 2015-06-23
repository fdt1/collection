/*
 *  mutable_instance_container_implementation.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "instance_container_implementation.h"
#include "mutable_container_interface.h"

namespace variety {
	
	
	template <typename C>
	class mutable_instance_container_implementation : 
		virtual public instance_container_interface<C>,
		virtual public mutable_container_interface<C> 
	{
	public:
		typedef C container_type;	
	private:
		container_type _container;
	public:
		virtual container_type& container() { return _container; }
		virtual const char* name() const { return "mutable_instance_container_implementation"; }
	};
	
	
} // namespace variety