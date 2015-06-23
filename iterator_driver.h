/*
 *  iterator_driver.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "iterator_wrapper.h"

template <typename T>
struct IteratorDriver {
	virtual IteratorDriver* clone() const = 0;
	
//	virtual const T& operator*() const = 0;
	virtual bool is_mutable() const = 0;
};

template <typename T, typename I>
struct ContainerIteratorDriver : public IteratorDriver<T> {
	I _iterator;
	
	ContainerIteratorDriver(const I& iterator) : _iterator(iterator) {}
	virtual ContainerIteratorDriver* clone() const { return new ContainerIteratorDriver(_iterator); }
	
//	virtual const T& operator*() const { return IteratorWrapper<I>::value(_iterator); }
	virtual bool is_mutable() const { return IteratorWrapper<I>::is_mutable; }
};
	
