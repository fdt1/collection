/*
 *  collection.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *

 
 */

#pragma once

#include "collection_driver.h"
#include "iterator.h"

template <typename T>
class Collection {
protected:	
	
	collection_driver::DataBase<T>* _driver;
public:	
	
	template <typename C>
	Collection<T>(const C& c) { _driver = collection_driver::ConstReferenceContainer<T, C>::create(c); }
	Collection<T>() { _driver = collection_driver::InstanceContainer<T, std::vector<T> >::create(); }
	size_t size() const { return _driver->size(); }
	const T& at(int i) const { return _driver->at(i); }
	Iterator<T> begin() const { return _driver->begin(); }
};

template <typename T>
class MutableCollection : public Collection<T> {
public:	
	template <typename C>
	MutableCollection<T>(C& c) { 
		if (ContainerWrapper<C>::is_mutable()) {
			Collection<T>::_driver = collection_driver::ReferenceContainer<T, C>::create(c); 
		} else {
			Collection<T>::_driver = collection_driver::InstanceContainer<T, C>::create(c);
			/*FIXME: fill */
		}
	}
	template <typename C>
	MutableCollection<T>(const C& c) { 
		Collection<T>::_driver = collection_driver::InstanceContainer<T, C>::create(c);
	}	
	MutableCollection<T>() { Collection<T>::_driver = collection_driver::InstanceContainer<T, std::vector<T> >::create(); }
	T& at(int i) { return reinterpret_cast<collection_driver::MutableData<T>*>(Collection<T>::_driver)->at(i); }
	template<typename K>
	void insert(const K& key, const T& elem) { 
		collection_driver::MutableKey<T, K>* key_base = dynamic_cast<collection_driver::MutableKey<T, K>*> (Collection<T>::_driver);
		//assert(key_base != NULL);
		key_base->insert(key, elem);
	}
};

