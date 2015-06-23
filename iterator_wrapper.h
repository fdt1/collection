/*
 *  iterator_wrapper.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

template <typename T, typename K> 
class Iterator;

template <typename I>
struct IteratorWrapper {
};


template <typename T, typename K>
struct IteratorWrapper<Iterator<T, K> > {
	typedef Iterator<T, K> I;
	
	static const bool is_mutable = true;
	
	static const T& value(const I& i) { return *i; }
	static T& value(I& i) { return *i; }
};
