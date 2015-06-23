/*
 *  vector_mutable_container_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "mutable_random_interface.h"
#include "vector_container_interface.h"
#include "iterator.h"
#include "collection.h"
#include <vector>


namespace variety {
	
	template <typename T, typename A>
	class container_interface<std::vector<T, A> > : 
	virtual public container_interface<const std::vector<T, A> >, 
	virtual public mutable_random_interface<T>
	{
	public:
		typedef T value_type;
		typedef T key_type;
		typedef std::vector<T, A> container_type;
	public:
		virtual container_type& container() = 0;
	public:
		virtual value_type& at(int index) { return container().at(index); }
	};

} // namespace variety