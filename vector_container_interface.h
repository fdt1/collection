/*
 *  vector_container_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "collection_interface.h"
#include "container_interface.h"
#include "iterator.h"
#include "collection.h"
#include <vector>


namespace variety {
	
	
	template <typename T, typename A>
	class container_interface<std::vector<T, A> > : 
		virtual public collection_interface<T, T>
	{
	public:
		typedef T value_type;
		typedef T key_type;
		typedef const std::vector<T, A> container_type;
	public:
		virtual const container_type& container() const = 0;
	public:
		virtual bool exist(const key_type& key) const { return std::find(key, container().begin(), container().end()) != container().end(); };
	public:
		virtual const value_type& at(int index) const { return container().at(index); }
	};
	
	

	
} // namespace variety