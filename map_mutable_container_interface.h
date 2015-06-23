/*
 *  map_mutable_container_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 07/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "mutable_associative_interface.h"
#include "map_container_interface.h"
#include "iterator.h"
#include "collection.h"
#include <map>


namespace variety {
	
	
	template <typename T, typename K, typename A>
	class container_interface<std::map<T, K, A> > : 
	virtual public container_interface<std::map<T, K, A> >, 
	virtual public mutable_associative_interface<T, K>
	{
	public:
		typedef T value_type;
		typedef K key_type;
		typedef std::map<T, K, A> container_type;
	public:
		virtual container_type& container() = 0;
	public:
		virtual void insert(const key_type& key, const value_type& value) { container()[key] = value; }
		virtual void insert(const key_type& key) { container()[key] = value_type(); }
	};
	
	
} // namespace variety