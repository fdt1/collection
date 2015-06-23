/*
 *  set_collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "container_wrapper.h"
#include "iterator_wrapper.h"
#include <set>


template <typename T, typename X>
struct ContainerWrapper<std::set<T, X> > {
	typedef std::set<T, X> C;
	typedef typename std::set<T, X>::const_iterator I;

	static const bool is_mutable = false;
	
	static size_t size(const C& c) { return c.size(); }
	static const T& at(const C& c, typename C::size_type i) { return *c.begin(); /* FIXME */ }
	static T& at(C& c, typename C::size_type i) { /*assert();*/ exit(1); }
	static I begin(const C& c) { return c.begin(); }
//	static I begin(const C& c) { return c.begin(); }
	static bool is_exist(const C& c, const T& elem) { return c.find(elem) != c.end(); }
	static void insert(C& c, const T& key, const T& elem) { c.insert(elem); }
};


template <typename T>
struct IteratorWrapper<typename std::_Rb_tree_const_iterator<T> > {
	//typedef std::set<T, X> C;
	typedef typename std::_Rb_tree_const_iterator<T> I;

	static const bool is_mutable = false;
	
	static const T& value(const I& i) { return *i; }
	static T& value(I& i) { return *i; }
};

