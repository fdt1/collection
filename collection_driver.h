/*
 *  collection_driver.h
 *  collection
 *
 *  Created by Francois et Fabienne on 21/10/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "container_wrapper.h"
#include "iterator.h"

namespace collection_driver {

template <typename T>
struct Base {
	virtual Base* clone() const = 0;
	virtual size_t size() const = 0;
	virtual const T& at(int i) const = 0;
	virtual bool is_mutable() const = 0;
	virtual Iterator<T> begin() const = 0;
	
};

template <typename T>
struct DataBase : virtual public Base<T> {	
};
	
template <typename T>
struct MutableData : public DataBase<T> {	
	virtual T& at(int i) = 0;
};

template <typename T>
struct NonMutableData : public DataBase<T> {	
};

template <typename T, typename K>	
struct KeyBase : virtual public Base<T> {	
	virtual bool is_exist(const K&) const = 0;
};
	
template <typename T, typename K>	
struct NonMutableKey : public KeyBase<T, K> {	
};

template <typename T, typename K>	
struct MutableKey : public KeyBase<T, K> {	
	virtual void insert(const K&, const T&) = 0;
};
	
template <typename T, typename C, typename K = T>
struct ReferenceContainer : public MutableData<T>, public MutableKey<T, K> {
	typedef typename ContainerWrapper<C>::I I;
	C& _container;
	
	ReferenceContainer<T, C, K>(C& c) : _container(c) { std::cout << __LINE__ << std::endl; }
	
	virtual ReferenceContainer<T, C, K>* clone() const { return new ReferenceContainer(_container); }
	static ReferenceContainer<T, C, K>* create(const C& c) { return new ReferenceContainer<T, C, K>(c); }
	
	virtual size_t size() const { return ContainerWrapper<C>::size(_container); }
	virtual const T& at(int i) const { return ContainerWrapper<C>::at(_container, i); }
	virtual T& at(int i) { return ContainerWrapper<C>::at(_container, i); }
	/*FIXME : factorize is_mutable */
	virtual bool is_mutable() const { return ContainerWrapper<C>::is_mutable; }
	virtual Iterator<T> begin() const { return Iterator<T>(ContainerWrapper<C>::begin(_container)); }	
	virtual void insert(const K& key, const T& elem) { ContainerWrapper<C>::insert(_container, key, elem); }
	virtual bool is_exist(const K& k) const { return ContainerWrapper<C>::is_exist(_container, k); };
};

template <typename T, typename C, typename K = T>
struct ConstReferenceContainer : public NonMutableData<T>, public NonMutableKey<T, K> {
	typedef typename ContainerWrapper<C>::I I;
	const C& _container;
	
	ConstReferenceContainer<T, C, K>(const C& c) : _container(c) { std::cout << __LINE__ << std::endl; }
	virtual ConstReferenceContainer<T, C, K>* clone() const { return new ConstReferenceContainer<T, C, K>(_container); }
	static ConstReferenceContainer<T, C, K>* create(const C& c) { return new ConstReferenceContainer<T, C, K>(c); }
	
	virtual size_t size() const { return ContainerWrapper<C>::size(_container); }
	virtual const T& at(int i) const { return ContainerWrapper<C>::at(_container, i); }
	virtual bool is_mutable() const { return false; }
	virtual Iterator<T> begin() const { return Iterator<T>(ContainerWrapper<C>::begin(_container)); }	
	virtual bool is_exist(const K& k) const { return ContainerWrapper<C>::is_exist(_container, k); };
};

template <typename T, typename C, typename K = T>
struct InstanceContainer : public MutableData<T>, public MutableKey<T, K> {
	typedef typename ContainerWrapper<C>::I I;
	C _container;
	
	InstanceContainer<T, C, K>(const C& c) : _container(c) { std::cout << __LINE__ << std::endl; }
	InstanceContainer<T, C, K>() : _container() { std::cout << __LINE__ << std::endl; }	
	virtual InstanceContainer<T, C, K>* clone() const { return new InstanceContainer(_container); }
	static InstanceContainer<T, C, K>* create(const C& c) { return new InstanceContainer<T, C, K>(c); }
	static InstanceContainer<T, C, K>* create() { return new InstanceContainer<T, C, K>(); }
	
	virtual size_t size() const { return ContainerWrapper<C>::size(_container); }
	virtual const T& at(int i) const { return ContainerWrapper<C>::at(_container, i); }
	virtual T& at(int i) { return ContainerWrapper<C>::at(_container, i); }
	virtual bool is_mutable() const { return ContainerWrapper<C>::is_mutable; }
	virtual Iterator<T> begin() const { return Iterator<T, I>((I) ContainerWrapper<C>::begin(_container)); }	
	virtual void insert(const K& key, const T& elem) { ContainerWrapper<C>::insert(_container, key, elem); }
	virtual bool is_exist(const K& k) const { return ContainerWrapper<C>::is_exist(_container, k); };
};

} // namespace collection_driver