/*
 *  vector_wrapper.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "container_wrapper.h"
#include "iterator_wrapper.h"
#include <vector>


template <typename T, typename X>
struct ContainerWrapper<std::vector<T, X> > {
	typedef std::vector<T, X> C;
	typedef typename std::vector<T, X>::const_iterator I;
	
	static const bool is_mutable = true;
	
	static size_t size(const C& c) { return c.size(); }
	static const T& at(const C& c, typename C::size_type i) { return c.at(i); }
	static T& at(C& c, typename C::size_type i) { return c.at(i); }
//	static I begin(C& c) { return c.begin(); }
	static I begin(const C& c) { return c.begin(); }
	static bool is_exist(const C& c, const T& elem) { return std::find(c.begin(), c.end(), elem) != c.end(); }
	static void insert(C& c, const T& key, const T& elem) { if (!is_exist(c, elem)) c.push_back(elem); }
};

template <typename _Category, typename _Tp, typename _Distance, typename _Pointer, typename _Reference>
struct IteratorWrapper<std::iterator< _Category,  _Tp,  _Distance,  _Pointer,  _Reference> > {
	static const bool is_mutable = true;
};


template <typename T, typename X>
struct IteratorWrapper<__gnu_cxx::__normal_iterator<const T*, std::vector<T, X > > > {
	typedef std::vector<T, X> C;
	typedef typename std::vector<T, X>::const_iterator I;
	
	static const bool is_mutable = true;
	
	static const T& value(const I& i) { return *i; }
	static T& value(I& i) { return *i; }
};

