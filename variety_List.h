/*
 *  variety_List.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once

#include "variety_IList.h"
#include "variety_ICollection.h"
#include "variety_internal_Implementation.h"


namespace variety {
	
	template <typename PrimeTemplate, typename AssociateTemplate = PrimeTemplate>
	class List : IList<PrimeTemplate, AssociateTemplate>, Implementation {
	public:
		typedef PrimeTemplate PrimeType;
		typedef AssociateTemplate AssociateType;
		typedef IList<PrimeTemplate, AssociateTemplate> InterfaceType;
		typedef List<PrimeTemplate, AssociateTemplate> SelfType;
	public:
		//template <typename Container>
		//List(const Container& container) : InterfaceType(NULL) { /*FIXME*/ }
		List(const InterfaceType& ilist) : InterfaceType(ilist.IGeneric::get_implementation().copy()) {}
		List(const ICollection<PrimeType, AssociateType>& collection) : InterfaceType(NULL) { /*FIXME*/ }
		List() : InterfaceType(NULL) { /*FIXME*/ }
		List(const SelfType& self) : InterfaceType(self.IGeneric::get_implementation().copy()) {}
		SelfType& operator=(const SelfType& self) { set_implementation(self.get_implementation().copy()); }
	public:
		List(Implementation* implement) : InterfaceType(implement), IGeneric(implement) {}
		virtual SelfType* duplicate() const { return new SelfType(IGeneric::get_implementation().duplicate()); }
	public:
	};
	
} // namespace variety