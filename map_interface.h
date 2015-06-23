/*
 *  map_interface.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "mutable_associative_interface.h"
#include "collection_interface.h"
#include "container_interface.h"
#include "iterator.h"
#include "collection.h"
#include <map>


namespace variety {
	
	
	template <typename T, typename K, typename A>
	class container_interface<const std::map<T, K, A> > : 
		virtual public interface<const std::map<T, K, A> >,
		virtual public collection_interface<T, K>
	{
	public:
		typedef T value_type;
		typedef K key_type;
		typedef const std::map<T, K, A> container_type;
		typedef std::map<T, K, A>::const_iterator iterator_type;
	public:
		virtual const container_type& container() const = 0;
	public:
		virtual bool exist(const key_type& key) const { return container().find(key) != container().end(); };
	public:
		virtual const value_type& at(int index) const { iterator_type it = container().begin(); std::advance(it, index); return *it; }
	};
	

	
} // namespace variety