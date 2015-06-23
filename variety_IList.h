/*
 *  variety_IList.h
 *  collection
 *
 *  Created by Francois et Fabienne on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#pragma once

#include "variety_internal_IList.h"
#include "variety_IGeneric.h"
#include "variety_generic_traits.h"


namespace variety {
		
	template <typename PrimeTemplate, typename AssociateTemplate = PrimeTemplate>
	class IList : 
	public virtual internal::IList<PrimeTemplate, AssociateTemplate>,
	public virtual IGeneric {
	public:
		typedef typename internal::IList<PrimeTemplate, AssociateTemplate>::InheritedType InheritedType;
	public:
		typedef typename GenericTraits<PrimeTemplate>::BaseType PrimeType;
		typedef typename GenericTraits<AssociateTemplate>::BaseType AssociateType;
		typedef Iterator<PrimeTemplate, AssociateTemplate> IteratorType;
		typedef internal::IList<PrimeTemplate, AssociateTemplate> InterfaceType;
		typedef IList<PrimeTemplate, AssociateTemplate> SelfType;
	public:
		// cast
		//template <typename OtherPrimeTemplate, typename OtherAssociateTemplate>
		//IList(const IList<OtherPrimeTemplate, OtherAssociateTemplate>& ilist) : IGeneric(NULL) { /* FIXME: cast */ }
		template <typename OtherPrimeTemplate, typename OtherAssociateTemplate>
		SelfType& operator= (const IList<OtherPrimeTemplate, OtherAssociateTemplate>& ilist) { /* FIXME: cast */ }
		// ref copy
		//IList(const SelfType& ilist) : IGeneric(ilist) {}
		SelfType& operator= (const SelfType& ilist) { IGeneric::set_implementation(ilist.get_implementation()); return *this; }
	protected:
		InterfaceType& get_implementation() { return dynamic_cast<InterfaceType&> (IGeneric::get_implementation()); }
		const InterfaceType& get_implementation() const { return dynamic_cast<const InterfaceType&> (IGeneric::get_implementation()); }
		IList(Implementation* implementation) : IGeneric(implementation) {}
	public:
		virtual IteratorType insert(const IteratorType& before_iter, const PrimeType& prime, const AssociateType& associate) { return get_implementation().insert(before_iter, prime, associate); }
		virtual IteratorType insert(const IteratorType& before_iter, const PrimeType& prime) { return get_implementation().insert(before_iter, prime); }
		virtual IteratorType insert_first(const PrimeType& prime, const AssociateType& associate) { return get_implementation().insert_first(prime, associate); }
		virtual IteratorType insert_first(const PrimeType& prime) { return get_implementation().insert_first(prime); }
		virtual IteratorType insert_last(const PrimeType& prime, const AssociateType& associate) { return get_implementation().insert_last(prime, associate); }
		virtual IteratorType insert_last(const PrimeType& prime) { return get_implementation().insert_last(prime); }
		virtual void erase(IteratorType& iter) { return get_implementation().erase(iter); }
		virtual void erase_first() { return get_implementation().erase_first(); }
		virtual void erase_last() { return get_implementation().erase_last(); }
	};
		
	
} // namespace variety