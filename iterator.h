/*
 *  iterator.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "iterator_driver.h"

template <typename T, typename K = bool>
class Iterator {
	IteratorDriver<T>* _driver;
	
protected:
public:
	template <typename I>
	Iterator(const I& iterator) : _driver(new ContainerIteratorDriver<T, I>(iterator)) {}
	
public:
	
	const K& key() const;
	const T& operator*() const;
};


template <typename T, typename K = bool>
class MutableIterator : public Iterator<T, K> {
public:
	template <typename I>
	MutableIterator(const I&) {}
	T& operator*() const;
};
